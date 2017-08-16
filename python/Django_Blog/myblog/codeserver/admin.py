from django.contrib import admin

# Register your models here.

from .models import codeserver

# 自定义codeserver的后台显示
class codeserverAdmin(admin.ModelAdmin):
    # 自定义后台数据库显示的字段及内容
    list_display = ('key','usr','date','code')

admin.site.register(codeserver,codeserverAdmin)
