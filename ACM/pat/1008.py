a, b = map(int,input().split())

l = input().split()

x = b%a

if x == 0:
    print(" ".join(l))
elif a == 1:
    print(l[0])
else:
    print(' '.join(l[-x:]+l[:a-x]))