k = int(input())
n = list(input())

n.sort()

i = 0
x = 0
mysum = sum(list(map(int, n)))
tmp = 0

while True:
    mysum+=tmp
    if mysum >= k:
        print(i)
        break
    try:
        if int(n[x]) != 9:
            tmp = 9-int(n[x])
            n[x]='9'
            i+=1
    except:
        pass
    x+=1

 
