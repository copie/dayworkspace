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


def link_recv(client, addr):
    buff = 102400
    while True:
        data = client.recv(buff)
        if not data:
            USERS.remove((client, addr))
            for user in USERS:
                massage = "%s:%d离开了聊天室" % (addr)
                print(massage)
                t = Thread(target=link_send, args=(user, massage))
                t.setDaemon(True)
                t.start()
            print("%s:%d离开了聊天室" % (addr))
            client.close()
            break
        for user in USERS:
            if user[1] != addr:
                massage = "来自于%s:%d的消息:\n" % (addr) + data.decode('utf-8')
                x = Thread(target=link_send, args=(user, massage))
                x.setDaemon(True)
                x.start()
               
        print("来自于%s:%d的消息:" % (addr))
        print(data.decode('utf-8'))


print("已经启动了聊天程序服务器等待用户连接......")

while True:
    try:
        client, addr = server.accept()

        print("欢迎%s:%d来到聊天室" % (addr))
        t = Thread(target=link_recv, args=(client, addr))
        t.setDaemon(True)
        t.start()
        USERS.append((client, addr))
    except Exception as e:
        print(e)
        server.close()
