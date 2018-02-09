from flask import Flask, Response
from flask import request
from fenbian import *

app = Flask(__name__, static_url_path='/')


@app.route('/', methods=['POST', 'GET'])
def hello_world():
    if request.method == "GET":
        return Response(open('index.html').read(), mimetype="text/html")
    if request.method == "POST":
        shang_lian = request.form['shang']
        xia_lian = request.form['xia']
        return str(fen_bian(shang_lian, xia_lian))


if __name__ == '__main__':
    app.run(host='0.0.0.0')
