from flask import Flask
from flask import request
from flask import send_from_directory, abort
import getpass
import os
import time

humidity = "0"      # 湿度
temperature = "0"   # 温度
mada_rate = "0"     # 空占比

app = Flask(__name__)


@app.route('/')
def root():
    '''访问 http://0.0.0.0:5000/ 返回湿度和温度 中间有一个空格'''
    return humidity + " " + temperature


@app.route('/update', methods=['POST', 'GET'])
def postht():
    '''由于不了解 Flask 如何传参所以这里这样处理'''
    global humidity, temperature
    if request.method == "GET":
        humidity = request.args.get('h', '')
        temperature = request.args.get('t', '')
        print(humidity, temperature)
        # 获取温度和湿度并返回
        return humidity + " " + temperature


@app.route('/madarate', methods=['POST', 'GET'])
def postmdrate():
    '''获取马达的空占比 访问的URL 是 http://0.0.0.0:5000/mada_rate 返回当前空占比
    http://0.0.0.0:5000/mada_rate?rate=30 这里是修改空占比'''
    global mada_rate
    if request.method == "GET":
        print(request.args)
        if request.args.get('rate', '') != "":
            mada_rate = request.args.get('rate', '')
        print(mada_rate)
        return mada_rate

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0')
