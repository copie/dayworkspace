'''
前几天看别人的面试题，看到好几次对一个特别大的文件进行处理 比如排序 还有一些别的操作
仔细思考了一下 思路就是 以下几个方面
1. 将一个大文件进行分割成为大小合适的子文本
2. 对每一个子文本进行排序操作
3. 使用归并排序对将子文件进行排序合并成为一个排序好的文件
如果想使用这个类需要重写 deal_input_line 和 deal_output_line 这两个方法以满足自己的需求
具体的使用例子看 同文件夹里面的test.py 这是一个简单的例子可以按照里面的进行写出符合自己需求的代码
'''


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
        # 结果文件的文件名 默认为 result.txt
        self.result_file_name = 'result.txt'

    def split_file(self):
        with open(self.big_file_name, 'r') as file:
            cont = 0
            j = 0
            tmp_file = open(f"tmp_file_{cont}.txt", 'w')
            for line in file:
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
            except StopIteration:
                # 到达了一个文件的结尾
                i += 1
                # 记录结束的文件数 加一
                tmpl[min_index] = self.deal_output_line(self.max_class)

    def deal_input_line(self, line):
        return line

    def deal_output_line(self, line):
        return line
