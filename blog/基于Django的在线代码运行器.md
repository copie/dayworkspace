# 基于 Django 的在线代码运行器

看廖雪峰的 Python 教程的时候他自己写了一个代码运行的一个网页，可以让别人直接 提交代码 查看自己的运行代码的运行结果，但是由于他的网站变成 https 的请求了导致不可以用了(我开始不知道)，把他的代码下载下来 看不懂啊看不懂 没有用过 他那个包。于是自己写了一个。ps: 虽然还是不可以兼容他的网站。:)手动尴尬

**新建项目和app就不说了 这里就 贴一些 重要的 代码**

## views_py

    import base64
    import os
    import subprocess
    import tempfile

    from django.http import HttpResponse, JsonResponse
    from django.shortcuts import render

    # Create your views here.


    def runcode(request):
        code_type = {'Python': 'py', 'Java': 'java',
                    'Python3': 'py', 'Cplusplus': 'cpp'}
        code_compiler = {'Python': '/usr/bin/python3', 'Python3': '/usr/bin/python3', 'Cplusplus':'/usr/bin/g++'}

        # 判断是否为 GET 请求 并且要包含 codetext(代码) 和 lang(语言)
        if request.method == 'GET' and 'codetext' in request.GET and 'lang' in request.GET:
            # 代码和语言都不为空
            if request.GET['codetext'] != '' and request.GET['lang'] != '':
                # 由于代码在网页端进行了 base64 的一个编码 在这里进行解码
                codetext = base64.decodebytes(
                    bytes(request.GET['codetext'], encoding='utf-8')).decode('utf-8')
                # 需要返回的字典
                r = dict()
                # 如果提交的是Python 以 Python3 进行处理
                if request.GET['lang'] == 'Python' or request.GET['lang'] == 'Python3':
                    try:
                        # 将代码写入文件
                        fpath = _write2file_(codetext)
                        # 新建一个子进程运行代码 超时为五秒 获取运行的输出结果
                        r['output'] = subprocess.check_output(
                            ['/usr/bin/python3', fpath], stderr=subprocess.STDOUT, timeout=5).decode('utf-8')
                    except subprocess.CalledProcessError as e:
                        r = dict(error='Exception',
                                output=e.output.decode('utf-8'))
                    except subprocess.TimeoutExpired as e:
                        r = dict(error='Timeout', output='执行超时')
                    except subprocess.CalledProcessError as e:
                        r = dict(error='Error', output='执行错误')
                    return JsonResponse(r)
                else:
                    return JsonResponse({'error': "提交暂不支持语言"})
            else:
                return JsonResponse({'code': '404'})
        else:
            return JsonResponse({'code': '404'})

    # 将代码写入文件 默认文件扩展名是 py
    #  返回文件的绝对路径
    # code 和 code_type 均为 str 
    def _write2file_(code, code_type='py'):
        # 新建一个临时文件夹 在/tmp文件家下
        temp_path = tempfile.mkdtemp()
        # 组合成文件的绝对路径
        fpath = os.path.join(temp_path, "main." + code_type)
        # 写入代码
        with open(fpath, 'w', encoding='utf-8') as f:
            f.write(code)
        return fpath

    # 返回提交代码的页面
    # 页面通过 js 进行 base64 编码, 和提交
    def index(request):
        return render(request, 'runcode.html')
## runcode.html

    <html lang="en">

    <head>
        <meta charset="UTF-8">
        <title>代码运行器</title>
        <style>
            body {
                text-align: center
            }

            textarea {
                width: 800px;
                height: 600px;
                resize: none;
            }
        </style>
        <!-- 引入 webtoolkit.base64.js 进行解码-->
        <script src='/static/webtoolkit.base64.js'></script>
        <link rel="icon" href="https://copie.cn/usr/uploads/2017/04/1512068142.jpg">
    </head>

    <body>
        <p>可以在这个地方上传你的代码并填写代码语言</p>
        <form action="/runcode/" id="myForm" method="get">
            <textarea id="codetext" placeholder="这里填写你的代码" name="codetext"></textarea>
            <br/>
            <label for="lang">语言:</label>
            <select name="lang">
                <option value="Python3">Python3</option>
                <option value="Cplusplus">C++</option>
                <option value="C">C</option>
                <option value="Java">Java</option>            
            </select>
            <br/>
            <br/>
            <input type="button" id="submitButton" value="上传">
        </form>
        <script>
            //此JS代码必须放到body结束之前才有效
            function $(id) { return document.getElementById(id); }
            $("submitButton").onclick = function () {
                alert("我被激活啦！");
                code = Base64.encode($("codetext").value);
                alert("代码:" + code);
                $("codetext").value = code;
                $("myForm").submit();
            }
        </script>
    </body>

    </html>