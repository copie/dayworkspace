result = open('result.txt', 'w')
sort_files = [open(f'sort_{i}.txt', 'r') for i in range(10)]
out = 0

tmpl = list(map(next, sort_files))
print(tmpl)
i = 0
l = 0
while True:
    if i == 10:
        print("结束了")
        for index, ip in enumerate(tmpl):
            tmp = list(map(int, ip[:-1].split(':')))
            if tmp[0] != 257:
                result.write(f'{tmp[0]}:{tmp[1]}:{tmp[2]}:{tmp[3]}\n')
        break
    min_num = [256, 256, 256, 256]
    min_index = -1
    for index, ip in enumerate(tmpl):
        tmp = list(map(int, ip[:-1].split(':')))
        if tmp < min_num:
            min_num = tmp
            min_index = index
    if min_num[0] != -1:
        result.write(f'{min_num[0]}:{min_num[1]}:{min_num[2]}:{min_num[3]}\n')
    try:
        tmpl[min_index] = next(sort_files[min_index])
        print(tmpl[min_index])
    except:
        i += 1
        print(i)
        tmpl[min_index] = "257:257:257:257\n"
    l += 1
    if l % 10000 == 0:
        print(l)
