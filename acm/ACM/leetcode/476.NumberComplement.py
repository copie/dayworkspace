num = 5
x=bin(num)[2:]
x1=''
for i in x:
    if i == '0':
        x1+='1'
    else:
        x1+='0'
# print(x1)
print(int(x1,2))
