from socket import AF_INET, SOCK_STREAM, socket
from threading import Thread

HOST = '127.0.0.1'
PORT = 55555

ADDR = (HOST, PORT)

server = socket(AF_INET, SOCK_STREAM)

server.connect(ADDR)
def link_recv(server):
    while True:
        buff = 102400
        massage = server.recv(buff)
        print(massage.decode('utf-8'))
t = Thread(target=link_recv,args=(server,))
t.setDaemon(True)
t.start()
while True:
    try:

        data = input().encode('utf-8')
        server.sendall(data)
        
    except:
        server.close()