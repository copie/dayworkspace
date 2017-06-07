k,n,w=map(int,input().split())
ll = list(i*k for i in range(1,w+1))
sum1=sum(ll)
if(sum1>n):
    print(sum1-n)
else:
    print(0)