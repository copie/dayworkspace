from socket import AF_INET, SOCK_STREAM, socket
from threading import Thread

# 客户端列表
USERS = []

HOST = ''
PORT = 55557

ADDR = (HOST, PORT)

server = socket(AF_INET, SOCK_STREAM)
server.bind(ADDR)
server.listen()


def link_send(user, massage):
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
    buff = 102400
    while True:
        data = client.recv(buff)
        if not data:
            USERS.remove((client, addr))
            massage = "%s:%d离开了聊天室" % (addr)
            send_mg_2_all(massage)
            print("%s:%d离开了聊天室" % (addr))
            client.close()
            break
        massage = "来自于%s:%d的消息:\n" % (addr) + data.decode('utf-8')
        print(massage)
        send_mg_2_all_nse(massage, [(client, addr)])
        print("来自于%s:%d的消息:" % (addr))
        print(data.decode('utf-8'))


print("已经启动了聊天程序服务器等待用户连接......")

while True:
    try:
        client, addr = server.accept()
        USERS.append((client, addr))
        print("欢迎%s:%d来到聊天室" % (addr))
        t = Thread(target=link_recv, args=(client, addr))
        t.setDaemon(True)
        t.start()
        massage = "欢迎%s:%d来到聊天室" % (addr)
        send_mg_2_all(massage)

    except Exception as e:
        print(e)
        server.close()
