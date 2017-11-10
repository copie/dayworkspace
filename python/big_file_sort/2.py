with open('xx.txt', 'r') as file:
    i = 0
    j = 0
    tmp_file = open(f"tmp_file_{i}.txt", 'w')
    for line in file:
        if j == 100000:
            i += 1
            j = 0
            tmp_file.close()
            tmp_file = open(f"tmp_file_{i}.txt", 'w')
        tmp_file.write(line)
        j += 1
