# Context_Locals_In_Werkzeug
在学习 Flask 的时候.为了看 Flask 上下文环境源码做准备.在上篇 blog 中我们已经看到了 threading.local 的使用.但是 Werkzeug.local.Local 类有一下优点
+ 在 Greenlet 可用的情况下优先使用 Greenlet 的 ID 而不是线程的 ID 以支持 Gvent 或者 Eventlet 的调度
+ Werkzeug 定义的协议方法 __release_local__, 可以被自己的 release_pool 函数释放掉.

## Werkzeug 实现的 Local Stack 和 Local Proxy

LocalStack 是 Local 实现的栈结构.对于这个栈结构的修改本线程可见.

LocalProxy 则是典型的代理模式的实现, 它的构造接收一个 callable 的参数,这个参数被调用的返回值本身应该是一个 Thread Local 对象,对一个 LocalProxy 对象的所有操作都会转发到,callable 返回的 Tread Local 对象上.


## Flask 中 Local Stack 和 Local Proxy 的使用

```Python
# context locals
# [3]
_request_ctx_stack = LocalStack()
current_app = LocalProxy(lambda: _request_ctx_stack.top.app)
request = LocalProxy(lambda: _request_ctx_stack.top.request)
session = LocalProxy(lambda: _request_ctx_stack.top.session)
g = LocalProxy(lambda: _request_ctx_stack.top.g)
```

```Python
def wsgi_app(self, environ, start_response):
    """The actual WSGI application.  This is not implemented in
    `__call__` so that middlewares can be applied:

        app.wsgi_app = MyMiddleware(app.wsgi_app)

    :param environ: a WSGI environment
    :param start_response: a callable accepting a status code,
                            a list of headers and an optional
                            exception context to start the response
    """
    # [1]
    with self.request_context(environ):
        # [4]
        rv = self.preprocess_request()
        if rv is None:
            # [5]
            rv = self.dispatch_request()
        # [6]
        response = self.make_response(rv)
        # [7]
        response = self.process_response(response)
        return response(environ, start_response)
```
```Python
def request_context(self, environ):
    """Creates a request context from the given environment and binds
    it to the current context.  This must be used in combination with
    the `with` statement because the request is only bound to the
    current context for the duration of the `with` block.

    Example usage::

        with app.request_context(environ):
            do_something_with(request)

    :params environ: a WSGI environment
    """
    return _RequestContext(self, environ)
```
```Python
class _RequestContext(object):
    """The request context contains all request relevant information.  It is
    created at the beginning of the request and pushed to the
    `_request_ctx_stack` and removed at the end of it.  It will create the
    URL adapter and request object for the WSGI environment provided.
    """

    def __init__(self, app, environ):
        self.app = app
        self.url_adapter = app.url_map.bind_to_environ(environ)
        self.request = app.request_class(environ)
        self.session = app.open_session(self.request)
        self.g = _RequestGlobals()
        self.flashes = None

    def __enter__(self):
        # [2]
        _request_ctx_stack.push(self)

    def __exit__(self, exc_type, exc_value, tb):
        # do not pop the request stack if we are in debug mode and an
        # exception happened.  This will allow the debugger to still
        # access the request object in the interactive shell.
        if tb is None or not self.app.debug:
            
            _request_ctx_stack.pop()
```

在这里统一解释一下上面的代码:

[1] 构建上下文环境
[2] 将构建的上下文压入栈中
[3] 给我们的栈顶的各个元素的每个部分弄一个响亮的名字(代理)
[4] 执行请求前的操作,如果请求前的操作返回值不是 None 就会不执行我们定义的 view ,执行自定义的 before_request 函数
[5] 寻找合适的 endpoint 然后执行,如果过程出错还会对错误进行捕捉,返回相应的错误页面
[6] 同过判断我们写的 view 函数的不同返回值构造不同的 Response 对象
[7] 请求完成后的相关操作 保存 session, 执行 after_request 中自定义的函数