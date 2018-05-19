# WSGI协议的原理及实现

WSGI, 是 Python Web Server Geteway Interface 的简称, 是 web 底层跟 application 解耦的协议. 我们的 web 服务器使用 WSGI 协议来调用 application 称为 WSGI server. 为了各类 web server(apache nginx, IIS) 和 web application(如 Flask django, tornado) 直接通信, 需要 WSGI server 作为桥梁. 如今 WSGI 已经成为 Python 的一种标准协议[PEP333](https://www.python.org/dev/peps/pep-0333/).

WSGI 协议分为两个部分：
+ server/gateway: 即 HTTP Server, 处理 HTTP 协议, 接受用户 HTTP 请求和提供并发. 调用 web application 处理业务逻辑,返回 application 提供的 response 给客户端.
+ web application/framework: 专注于逻辑的 Python 应用或者框架. 接收从 Server 转发的 request, 处理请求, 并将 response 返回给 Server.

![SWGI](https://copie.cn/usr/uploads/2018/05/766648353.png)

## WSGI　的工作原理

![SWGI](https://copie.cn/usr/uploads/2018/05/3130859073.png)

### Application Side

应用程序端必须定义一个满足以下条件的**可调用对象**:
+ 接收两个参数: environ(dict), start_response(回调函数,返回 HTTP status, headers 给 web server)
+ 返回一个可迭代的值

### Server Side

上面提到的 environ 和 start_response 都是服务器提供的. 服务器必须要调用 application:
+ 接收 HTTP 请求, 但是不关心 HTTP url, HTTP method 等,为 environ 提供必要的参数
+ 实现一个回调函数 start_response.
+ 调用 callable object(可调用对象) 并传递 environ 和 start_response.

### Middleware: Components thst Play Both Sides

Middleware 处于 Server 和 application 之间.
每个 Middleware 实现不同的功能, 我们通常根据需求选择相应的 Middleware 并组合起来,实现所需要的功能.

### 使用 wsgiref 模块

```Python
from wsgiref.simple_server import make_server


def application(environ, start_response):
    start_response("200 OK", [("content_type", "text/html")])
    return [b"Hello World!"]


if __name__ == '__main__':
    server = make_server('0.0.0.0', 5000, application)
    server.serve_forever()
```

```
➜  ~ curl 127.0.0.1:5000
Hello World!%
```

## SWGI Server 简单实现

```Python
[wsgi.py]
import socket
import sys
from io import StringIO
from datetime import datetime


class WSGIserver:
    def __init__(self, server_address, port):
        self.server_address = server_address
        self.server_port = port
        self.listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.listen_socket.setsockopt(
            socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.listen_socket.bind((self.server_address, self.server_port))
        self.listen_socket.listen()
        host = self.listen_socket.getsockname()[0]
        self.server_name = socket.getfqdn(host)
        self.headers_set = []

    def set_app(self, application):
        self.application = application

    def server_forever(self):
        listen_socket = self.listen_socket
        while True:
            self.client_connection, self.client_address = listen_socket.accept()
            self.handel_one_request()

    def handel_one_request(self):
        self.request_data = request_data = self.client_connection.recv(
            1024).decode("utf-8")
        self.parse_request(request_data)
        env = self.get_environ()
        result = self.application(env, self.start_response)
        self.finish_response(result)

    def parse_request(self, data):
        format_data = data.splitlines()
        if len(format_data):
            request_line = format_data[0].rstrip('\r\n')
            self.request_method, self.path, self.request_version = request_line.split()

    def get_environ(self):
        env = dict()
        env['wsgi.version'] = (1, 0)
        env['wsgi.url_scheme'] = 'http'
        env['wsgi.input'] = StringIO(self.request_data)
        env['wsgi.errors'] = sys.stderr
        env['wsgi.multithread'] = False
        env['wsgi.multiprocess'] = False
        env['wsgi.run_once'] = False
        env['REQUEST_METHOD'] = self.request_method
        env['PATH_INFO'] = self.path
        env['SERVER_NAME'] = self.server_name
        env['SERVER_PORT'] = str(self.server_port)
        return env

    def start_response(self, status, response_headrs, exc_info=None):
        server_headers = [("Date", str(datetime.now())),
                          ("Server", "COPIE_SERVER")]
        self.headers_set = [status, response_headrs+server_headers]

    def finish_response(self, result):
        try:
            status, response_headrs = self.headers_set
            response = f"HTTP/1.1 {status}\r\n".encode('utf-8')
            for header in response_headrs:
                response += f"{header[0]}: {header[1]}\r\n".encode('utf-8')
            response += "\r\n".encode('utf-8')
            for data in result:
                response += data
            self.client_connection.sendall(response)
            print(response.decode('utf-8'))
        finally:
            self.client_connection.close()


def make_server(server_address, port, application):
    server = WSGIserver(server_address, port)
    server.set_app(application)
    return server


def application(environ, start_response):
    print(environ)
    start_response("200 OK", [("content_type", "text/html")])
    return [b"Hello World!"]


if __name__ == '__main__':
    server = make_server('0.0.0.0', 5000, application)
    server.server_forever()
```

```python
[flask_test.py]
from flask import Flask
from flask import Response,Request
from wsgi import make_server
flask_app = Flask(__name__)


@flask_app.route('/hello')
def hello_world():
    return Response('hello',mimetype='text/plain')

app = flask_app.wsgi_app
server = make_server('0.0.0.0', 5000, app)
server.server_forever()
```
这里我们发现我们手动撸的简易的 http server 真正的跑了起来