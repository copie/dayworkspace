class big_file_sort:
    def __init__(self):
        # 分割的子文件的数量
        self._ch_file_cont = None
        # 输入文件的路径
        self.big_file_name = None
        # 最大的子类
        self.max_class = None
        # 每个文件最大的行数
        self.max_line_cont = None
        self.result_file_name = None

    def split_file(self):
        with open(self.big_file_name, 'r') as file:
            cont = 0
            j = 0
            tmp_file = open(f"tmp_file_{cont}.txt", 'w')
            for line in file:
                print("hello")
                if j == self.max_line_cont:
                    cont += 1
                    j = 0
                    tmp_file.close()
                    tmp_file = open(f"tmp_file_{cont}.txt", 'w')
                tmp_file.write(line)
                j += 1
            self._ch_file_cont = cont

    def one_file_sort(self):
        for i in range(self._ch_file_cont + 1):
            print(f"正在处理第{i}个文件")
            with open(f"tmp_file_{i}.txt", 'r') as tmp_file:
                t = [self.deal_input_line(line) for line in tmp_file]
                t.sort()
            with open(f"sort_{i}.txt", 'w') as tmp_file:
                x = (self.deal_output_line(one_line)
                     for one_line in t)
                tmp_file.writelines(x)

    def sort(self):
        result = open('result.txt', 'w')
        sort_files = [open(f'sort_{i}.txt', 'r')
                      for i in range(self._ch_file_cont + 1)]
        tmpl = list(map(next, sort_files))
        i = 0
        l = 0
        while True:
            if i == self._ch_file_cont + 1:
                print("结束了")
                for tmp in tmpl:
                    if tmp != self.deal_output_line(self.max_class):
                        result.write(tmp)
                break
            min_num = self.max_class
            min_index = -1
            for index, ip in enumerate(tmpl):
                tmp = self.deal_input_line(ip)
                if tmp < min_num:
                    min_num = tmp
                    min_index = index
            try:
                result.write(tmpl[min_index])
                tmpl[min_index] = next(sort_files[min_index])
            except:
                i += 1
                print(i)
                tmpl[min_index] = self.deal_output_line(self.max_class)
            l += 1
            if l % 10000 == 0:
                print(l)

    def deal_input_line(self, line):
        pass

    def deal_output_line(self, line):
        pass
