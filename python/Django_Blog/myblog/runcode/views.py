import base64
import subprocess
import tempfile

from django.http import HttpResponse, JsonResponse
from django.shortcuts import render

# Create your views here.


def runcode(request):
    # print(request.method)
    if request.method == 'GET' and 'codetext' in request.GET and 'lang' in request.GET:
        if request.GET['codetext'] != '' and request.GET['lang'] != '':
            if request.GET['lang'] == 'python' or request.GET['lang'] == 'python3'
            codetext = base64.decodebytes(
                bytes(request.GET['codetext'], encoding='utf-8'))
            return JsonResponse({'code': '200', "代码": str(codetext)})
        else:
            return JsonResponse({'code': '404'})
    else:
        return JsonResponse({'code': '404'})


def index(request):
    # return HttpResponse("你可以在这提交你的code")
    return render(request, 'runcode.html')
    pass
