n,m,a = map(int,input().split(" "))

sum=0
sum+=int(n/a)
if n%a!=0:
    sum+=1
sum1=0
sum1+=int(m/a)

if m%a!=0:
    sum1+=1
print(int(sum*sum1))
