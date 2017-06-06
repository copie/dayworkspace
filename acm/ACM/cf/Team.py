n = int(input())
sum = 0
for _ in range(n):
    if list(input()).count("1") > 1:
        sum+=1
print(sum)