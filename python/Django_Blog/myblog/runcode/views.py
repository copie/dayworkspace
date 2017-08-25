import base64
import os
import subprocess
import tempfile

from django.http import HttpResponse, JsonResponse
from django.shortcuts import render

# Create your views here.


def runcode(request):
    # print(request.method)
    if request.method == 'GET' and 'codetext' in request.GET and 'lang' in request.GET:
        if request.GET['codetext'] != '' and request.GET['lang'] != '':
            if request.GET['lang'] == 'python' or request.GET['lang'] == 'python3':
                codetext = base64.decodebytes(
                    bytes(request.GET['codetext'], encoding='utf-8')).decode('utf-8')
                r = dict()
                try:
                    fpath = _write2file_(codetext)
                    r['output'] = subprocess.check_output(
                        ['/usr/bin/python3', fpath], stderr=subprocess.STDOUT, timeout=5).decode('utf-8')
                except subprocess.CalledProcessError as e:
                    r = dict(error='Exception', output=e.output.decode('utf-8'))
                except subprocess.TimeoutExpired as e:
                    r = dict(error='Timeout', output='执行超时')
                except subprocess.CalledProcessError as e:
                    r = dict(error='Error', output='执行错误')
                return JsonResponse(r)
            else:
                return JsonResponse({'code': '404', 'error': "提交暂不支持语言"})
        else:
            return JsonResponse({'code': '404'})
    else:
        return JsonResponse({'code': '404'})


def _write2file_(code, code_type='py'):
    temp_path = tempfile.mkdtemp()
    fpath = os.path.join(temp_path, "main." + code_type)
    with open(fpath, 'w', encoding='utf-8') as f:
        f.write(code)
    return fpath


def index(request):
    # return HttpResponse("你可以在这提交你的code")
    return render(request, 'runcode.html')
    pass
