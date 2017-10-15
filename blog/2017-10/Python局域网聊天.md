# Python局域网聊天

上一次我写了一个 全双工的聊天程序 但是需要搭建一个服务器才可以。这样弄起来就不是很方便了。所以我就把以前的代码整理了一下。添加了一些功能。还有实验一下关于进程通信的一些想法。


## localechat.py

    import os
    import queue
    import socket
    import sys
    import threading
    import time

    from TCP_client import TCP_client
    from TCP_server import TCP_server

    rlock = threading.RLock()
    kill_queue = queue.Queue()
    local_host = ''


    def j_kill(kill_queue, name):
        # 判断是否有 kill 父线程信号, 如果有就结束当前线程，如果没有就转发该信号
        while True:
            key = kill_queue.get()
            if key == name:
                return 'kill'
            else:
                kill_queue.put(key)


    def tishi(rlock, name):
        # 新建一个线程用于提示用户正在等待，查找可用的服务端
        with rlock:
            print("正在查找可用的服务端请稍等", end='')
        t = threading.Thread(target=j_kill, args=(kill_queue, name))
        # 这个线程 提供结束当前线程的方法
        t.start()
        while True:
            if t.is_alive():
                with rlock:
                    print('...', end='')
                    sys.stdout.flush()
                time.sleep(1)
            else:
                return 0


    def xy(udp):
        while True:
            data, addr = udp.recvfrom(1024)
            udp.sendto('{},55556'.format(local_host).encode('utf-8'), addr)


    def create_UDP_server(rlock):
        HOST = ''
        PORT = 55555
        ADDR = (HOST, PORT)
        udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp.bind(ADDR)
        t = threading.Thread(target=xy, args=(udp,))
        t.start()


    def find_server(rlock):
        global local_host
        HOST = '255.255.255.255'
        PORT = 55555
        ADDR = (HOST, PORT)
        if_find = False    # 标记是否找到

        udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST,
                    1)  # 让socket发送的数据具有广播特性
        try:
            udp.sendto(b'c find s', ADDR)
        except OSError as e:
            print("没有连接到局域网，请将此电脑连接到局域网")
            exit(1)
        udp.settimeout(5)
        try:
            t = threading.Thread(target=tishi, args=(rlock, 'tishi'), name="tishi")
            t.start()
            data, addr = udp.recvfrom(1024)
            host, port = data.decode().split(',')
            time.sleep(0.5)
            print("\n找到了服务器 -->{}:{}".format(host, port))
            local_host = host
            if_find = True
        except socket.timeout as e:
            print('\n没有在本局域网内找到可用回来server，接下来本客户端会自动创建一个服务端等待其他用户的连接')
        finally:
            kill_queue.put('tishi')
            time.sleep(0.5)
            udp.close()
            return if_find


    def get_local_host():
        # 获取本机的 IP 地址
        hostname = socket.gethostname()
        host = socket.gethostbyname(hostname)
        # 获取本机IP的时候还是有一些问题的
        # 比如 hosts 文件被 修改了很有可能获取的就不是局域网的 IP 地址
        return host


    def main():
        global local_host
        if find_server(rlock) is True:  # 如果该局域网下有服务器
            client = TCP_client(local_host, 55556, rlock)
            client.run()
        else:
            server = TCP_server(rlock)
            threading.Thread(target=server.run, args=()).start()
            print("新建一个UDP的监控")
            create_UDP_server(rlock)
            local_host = get_local_host()
            client = TCP_client(local_host, 55556, rlock)
            client.run()


    if __name__ == "__main__":
        main()

## [TCP_client]()
