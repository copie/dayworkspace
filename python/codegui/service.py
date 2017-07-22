from flask import Flask
from flask import request
app = Flask(__name__)
code=''
@app.route('/')
def hello_world():
    return code
@app.route("/hello")
def haha():
    return "这是一个测s "
@app.route('/postcode', methods=['POST', 'GET'])
def postcode():
    global code
    if request.method == "GET":
        code = request.args.get('code', '')
        return '200'
    elif request.method == 'POST':
        code = request.data

if __name__ == '__main__':
    app.debug = True 
    app.run(host='0.0.0.0')