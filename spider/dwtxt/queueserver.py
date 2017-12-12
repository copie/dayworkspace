from multiprocessing.connection import Listener, Client
import traceback
from threading import Thread
from queue import Queue

arg_queue = Queue()


def echo_client(conn):
    try:
        while True:
            msg = conn.recv()
            if msg['status'] == 'get':
                # 客户端想要请求一组数据让自己处理
                tmp_data = {'status': 'put', 'data': arg_queue.get()}
                conn.send(tmp_data)
            if msg['status'] == 'put':
                # 客户端想要上传一组数据
                arg_queue.put(msg['data'])
    except EOFError:
        print("连接关闭")


def echo_server(address, authkey):
    serv = Listener(address, authkey=authkey)
    while True:
        try:
            client = serv.accept()
            Thread(target=echo_client,args=(client,)).start()
            # echo_client(client)
        except Exception:
            traceback.print_exc()


def server(port, authkey):
    th = Thread(target=echo_server, args=((('', port), authkey)))
    th.start()


if __name__ == '__main__':
    server(8888, b'Hello World!')
