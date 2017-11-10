for i in range(10):
    print(f"正在处理第{i}个文件")
    t = []
    with open(f"tmp_file_{i}.txt",'r') as tmp_file:
        for line in tmp_file:
            z = []
            for x in line[:-1].split(":"):
                z.append(int(x))
            t.append(z)
    # print(t[:100])
    t.sort()

    with open(f"sort_{i}.txt",'w') as tmp_file:
        x = (f'{i}:{j}:{x}:{y}\n'
                for i,j,x,y in t)
        tmp_file.writelines(x)
