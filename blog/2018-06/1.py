import sys

value = 3

def g():
    frame = sys._getframe()
    print(f"函数名: {frame.f_code.co_name}")
    caller = frame.f_back
    print(f"调用的函数名是: {caller.f_code.co_name}")
    print(f"调用的函数的 local 名字空间: {caller.f_locals}")
    print(f"调用的函数的 global 名字空间: {caller.f_globals.keys()}")

def f():
    a = 1
    b = 2
    g()

def show():
    f()

show()