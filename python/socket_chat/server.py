from socket import AF_INET, SOCK_STREAM, socket
from threading import Thread
import threading

# 客户端列表
USERS = []

HOST = ''
PORT = 55555

ADDR = (HOST, PORT)

server = socket(AF_INET, SOCK_STREAM)
server.bind(ADDR)
server.listen()
mutex = threading.Lock()


def link_send(user, massage):
    # 给指定用户发送 massage
    client, addr = user
    client.sendall(massage.encode('utf-8'))


def send_mg_2_all(massage):
    # send massage to all users
    for user in USERS:
        x = Thread(target=link_send, args=(user, massage))
        x.setDaemon(True)
        x.start()


def send_mg_2_all_nse(massage, bl_users):
    # send massage to all users not someone
    for user in USERS:
        if user not in bl_users:
            x = Thread(target=link_send, args=(user, massage))
            x.setDaemon(True)
            x.start()


def send_mg_2_se(massage, users):
    # send massage to someone
    for user in users:
        x = Thread(target=link_send, args=(user, massage))
        x.setDaemon(True)
        x.start()


def link_recv(client, addr):
    # 接收来自客户端的 massage

    buff = 102400
    while True:
        data = client.recv(buff)
        # 等待获取 addr 客户端的上传 massage
        if not data:
            # 如果没有接受到 data客户端下线
            mutex.acquire()
            # 互斥锁 锁定
            USERS.remove((client, addr))
            mutex.release()
            # 互斥锁 释放
            massage = "%s:%d离开了聊天室" % (addr)
            send_mg_2_all(massage)
            print("%s:%d离开了聊天室" % (addr))
            client.close()
            # 关闭连接
            break
        massage = "来自于%s:%d的消息:\n" % (addr) + data.decode('utf-8')
        print(massage)
        send_mg_2_all_nse(massage, [(client, addr)])
        # 给所有的人发送消息 不包括发送信息的人
        print("来自于%s:%d的消息:" % (addr))
        print(data.decode('utf-8'))


print("已经启动了聊天程序服务器等待用户连接......")

while True:
    try:
        client, addr = server.accept()
        mutex.acquire()
        # 互斥锁 锁定
        USERS.append((client, addr))
        mutex.release()
        # 互斥锁 释放
        print("欢迎%s:%d来到聊天室" % (addr))
        t = Thread(target=link_recv, args=(client, addr))
        # 新建一个线程用来等待 addr 用户的上传
        t.setDaemon(True)
        t.start()
        massage = "欢迎%s:%d来到聊天室" % (addr)
        send_mg_2_all(massage)
        # 给所有的人发送欢迎消息

    except Exception as e:
        捕获所有的错误 然后关闭服务器
        print(e)
        server.close()
