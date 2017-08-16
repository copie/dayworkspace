from django.db import models

# Create your models here.


class codeserver(models.Model):
    code=models.CharField(max_length=5000,null=False)
    date=models.DateTimeField()
    key=models.CharField(max_length=20,primary_key=True,db_index =True)
    usr=models.CharField(max_length=20)
