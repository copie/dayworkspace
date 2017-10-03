from socket import AF_INET, SOCK_STREAM, socket
from threading import RLock, Thread


class TCP_client:

    def __init__(self, HOST, PORT, rlock):
        self.HOST = HOST
        self.PORT = PORT
        self.rlock = rlock
        self.ADDR = (self.HOST, self.PORT)

    def _link_recv(self, client):
        while True:
            buff = 102400
            massage = client.recv(buff)
            print(massage.decode('utf-8'))

    def run(self):
        client = socket(AF_INET, SOCK_STREAM)
        client.connect(self.ADDR)
        t = Thread(target=self._link_recv, args=(client,))
        t.start()
        while True:
            try:
                data = input().encode('utf-8')
                client.sendall(data)

            except Exception as e:
                print(e)
                client.close()
                client.shutdown()
                print("成功关闭了连接")


if __name__ == "__main__":
    rlock = RLock()
    c = TCP_client('192.168.43.113', 55556, rlock)
    c.run()
