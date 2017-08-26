T = int(input())

l=[]
while T != 0:
    T-=1
    a,b,c = input().split()
    c=int(c)
    l.append([a,b,c])

l.sort(key=lambda x:x[2])


print(l[-1][0] + " " + l[-1][1])
print(l[0][0] + " " + l[0][1])
