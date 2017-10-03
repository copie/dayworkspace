import threading
import time
from socket import AF_INET, SOCK_STREAM, socket
from threading import Thread


class TCP_server:

    def __init__(self, rlock):
        self.USERS = []

        self.HOST = ''
        self.PORT = 55556

        self.ADDR = (self.HOST, self.PORT)
        self.rlock = rlock

    def link_send(self, user, massage):
        # 给指定用户发送 massage
        client, addr = user
        client.sendall(massage.encode('utf-8'))

    def send_mg_2_all(self, massage):
        # send massage to all users
        for user in self.USERS:
            x = Thread(target=self.link_send, args=(user, massage))
            x.setDaemon(True)
            x.start()

    def send_mg_2_all_nse(self, massage, bl_users):
        # send massage to all users not someone
        for user in self.USERS:
            if user not in bl_users:
                x = Thread(target=self.link_send, args=(user, massage))
                x.setDaemon(True)
                x.start()

    def link_recv(self, client, addr):
        # 接收来自客户端的 massage

        buff = 102400
        while True:
            data = client.recv(buff)
            # 等待获取 addr 客户端的上传 massage
            if not data:
                # 如果没有接受到 data客户端下线
                with self.rlock:
                    self.USERS.remove((client, addr))

                massage = "%s:%d离开了聊天室" % (addr)
                self.send_mg_2_all(massage)
                client.close()
                # 关闭连接
                break

            massage = "来自于%s:%d的消息:\n" % (addr) + data.decode('utf-8')

            self.send_mg_2_all_nse(massage, [(client, addr)])
            # 给所有的人发送消息 不包括发送信息的人

    def run(self):
        server = socket(AF_INET, SOCK_STREAM)
        server.bind(self.ADDR)
        server.listen()
        print("新建服务器成功")
        print("等待第一个连接")
        while True:
            try:
                client, addr = server.accept()
                time.sleep(1)
                with self.rlock:
                    self.USERS.append((client, addr))
                t = Thread(target=self.link_recv, args=(client, addr))
                t.setDaemon(True)
                t.start()
                massage = "欢迎%s:%d来到聊天室" % (addr)
                self.send_mg_2_all(massage)
            except Exception as e:
                print(e)
                client.close()
                break
        server.close()


if __name__ == "__main__":
    rlock = threading.RLock()
    server = TCP_server(rlock)
    server.run()
