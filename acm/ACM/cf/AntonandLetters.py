str1=set(list(''.join(input()[1:-1].split(',')).split(' ')))
if '' in str1:
    print(len(str1)-1)
else:
    print(len(str1))