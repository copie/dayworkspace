from django.shortcuts import render
from django.http import HttpResponse
from .models import codeserver
import hashlib
import time

# Create your views here.

def codeserverIndex(request,key):
    
    print(key)
    codedata = codeserver.objects.get(key=key)
    print(codedata)
    print(codedata.code)
    return render(request,"codeserverindex.html",{'code':codedata.code,'usr':codedata.usr,'date':codedata.date})

def codeup(request):

    return render(request,'codeupdate.html')

def codeupdate(request):

    # return HttpResponse("hello world")
    key = ""
    if 'codetext' in request.GET and 'name' in request.GET:

        if request.GET['codetext'] != '' and request.GET['name'] != '':
            
            key = hashlib.md5(request.GET['codetext'].encode('utf-8'))
            key = key.hexdigest()[:8]
     
            codedata = codeserver.objects.create(key=key)
            codedata.usr = request.GET['name']
            codedata.code = request.GET['codetext']
            codedata.save()

    return HttpResponse('<h1>http://127.0.0.1:8000/code/'+key+'</h1>')
