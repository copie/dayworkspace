if(len(a) != len(b)):
    return max(len(a), len(b))
flag = []
i = 0
for x, y in zip(a, b):
    if x != y:
        try:
            flag.append(flag[i - 1] + 1)
        except:
            flag.append(1)
    else:
        try:
            flag.append(flag[i - 1])
        except:
            flag.append(0)
