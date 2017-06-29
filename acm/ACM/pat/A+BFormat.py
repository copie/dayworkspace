a, b = map(int, input().split())
w=[]
c = str(abs(a+b))
c=c[::-1]
y=0

for x in c[0:-1:]:
    w+=x
    y+=1
    if y is 3:
        y=0
        w+=','
w+=c[-1]
if a+b < 0:
    w+='-'
print("".join(w[::-1]))