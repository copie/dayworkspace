str1 = input().split('+')
str1.sort()
if len(str1) == 1:
    print(str1[0])
else:
    print("+".join(str1))
