from flask import Flask
from flask import request
from flask import send_from_directory, abort
import getpass
import os
import time

app = Flask(__name__)
code = ''
myfiletype = ''
filepath = "/home/" + getpass.getuser() + "/codeguiup/"
myfilename = ""
if os.path.isdir(filepath) == False:
    os.mkdir(filepath)

UPLOAD_FOLDER = '/home/copie/'
ALLOWED_EXTENSIONS = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])

# 限制上传格式 我们这里不需要


def allowed_file(filename):
    return '.' in filename and \
        filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS


@app.route('/')
def hello_world():
    return code


@app.route('/postcode', methods=['POST', 'GET'])
def postcode():
    global code
    if request.method == "GET":
        code = request.args.get('code', '')
        return '200'


@app.route('/upfile', methods=['POST'])
def upfile():
    if request.method == 'POST':
        global filepath
        global myfilename
        global myfiletype
        file = request.files['file']
        if file:
            print(file.filename)
            myfiletype = file.filename.split('.')[-1]
            myfilename = str(abs(hash(file.filename)))
            file.save(os.path.join(
                app.config['UPLOAD_FOLDER'], filepath + myfilename))
            return "yes"
        return "200"


@app.route('/downfile', methods=['GET'])
def downfile():
    request.method == 'GET'
    # print(myfilename)
    
    if os.path.isfile("/home/copie/codeguiup/"+myfilename):
        print(myfilename)
        return send_from_directory('/home/copie/codeguiup/', myfilename, as_attachment=True)
    else:
        return '404'
@app.route('/downfiletype',methods=['GET'])
def downfiletype():
    print(myfiletype)
    return myfiletype
if __name__ == '__main__':
    app.debug = True
    app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
    app.run(host='0.0.0.0')
