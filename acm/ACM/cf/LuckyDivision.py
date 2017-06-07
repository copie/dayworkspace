ll=[]
for x in range(3,1001):
    l = list(str(x))
    if len(l) == l.count('4')+l.count('7'):
        ll.append(x)
tmp = int(input())
t=0
for i in ll:
    if tmp%i==0:
        print("YES")
        t=1
        break
if t==0:
    print("NO")