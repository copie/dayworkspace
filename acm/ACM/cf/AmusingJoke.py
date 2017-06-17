str1 = list(input())
str2 = list(input())
str3 = list(input())
str1 = str1+str2
print("YES" if sorted(str1) == sorted(str3) else "NO")
