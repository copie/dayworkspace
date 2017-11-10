from big_file_sort import big_file_sort


class mysort(big_file_sort):
    def __init__(self):
        super(mysort, self).__init__()
        # 输入文件的路径
        self.big_file_name = 'xx.txt'
        # 最大的子类
        self.max_class = [257, 257, 257, 257]
        # 每个文件最大的行数
        self.max_line_cont = 6000
        # 目标文件名称
        self.result_file_name = "result.txt"

    def deal_input_line(self, line):
        return list(map(int, line[:-1].split(":")))

    def deal_output_line(self, line):
        return f'{line[0]}:{line[1]}:{line[2]}:{line[3]}\n'

def main():
    x = mysort()
    x.split_file()
    x.one_file_sort()
    x.sort()

if __name__ == '__main__':
    main()