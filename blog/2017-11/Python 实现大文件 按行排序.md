# Python 实现对大文件的按行排序

前几天看到别人的面试题中有一个是对一个几个G大小的文本文件进行按行排序, 并且不可以使用数据库进行排序。

## 思路

其实有了思路代码写起来也是比较快的.

1.  将一个大文件进行分割。因为文件比较大所以不可能把所有的数据都加载到内存中(如果你是神豪的话, 你还写什么代码,回家老婆孩子热炕头吧)
2. 如果我们把大文件分割的合适的话, 这个时候就可以把每一个文件进行排序了。排序以后将排序好的文件保存起来。开始下一步
3. 这个时候我们就会得到 N 个 内部排序好的文件。我们要做的就是把这些文件进行合并成为一个文件，这里就要使用一点归并排序的知识了。这里的归并排序，首先会把每一个文件都提取一个值。找出最小的然后, 将这个值写入结果文件。再从最小值对应的文件中重新读一个数。一直到所有的文件结束。我们保存的结果文件就是我们想要的。

## big_file_sort.py

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

因为不知道我的程序要排序什么文件如果你想用上面的代码去排序自己的文件的话需要向下面这样做就可以了

## test.py

    '''
        这里的例子是对于一个文件里面的 IP 地址进行排序 生成测试数据的 代码 是 1.py

    '''
    from big_file_sort import big_file_sort


    class mysort(big_file_sort):
        def __init__(self):
            super(mysort, self).__init__()
            # 输入文件的路径
            self.big_file_name = 'xx.txt'
            # 可排序对象 比最大还大的一个对象 便于排序
            self.max_class = [257, 257, 257, 257]
            # 每个文件最大的行数
            self.max_line_cont = 6000
            # 目标文件名称
            self.result_file_name = "result.txt"

        def deal_input_line(self, line):
            # 文本内的一行文本 字符串类型 ---> 可排序的对象
            # '123:123:123:123\n'  ---> '[123,123,123,123]'
            # 将 其转化为列表 就是 方便排序 毕竟 '011:011:011:011' 和 '11:11:11:11' 是同一个IP
            return list(map(int, line[:-1].split(":")))

        def deal_output_line(self, line):
            # 可排序的对象   ---> 文本内的一行文本 字符串类型
            # '[123,123,123,123]' ---> '123:123:123:123\n'
            return f'{line[0]}:{line[1]}:{line[2]}:{line[3]}\n'


    def main():
        # 创建大文本排序对象
        x = mysort()
        # 分割文本文件方便排序 分割的时候要考虑 max_line_cont 的大小 适当的大小更能提高排序能力
        x.split_file()
        # 对每一个单一文件排序这里是把一个文件都加载到了内存中 不可 太大
        x.one_file_sort()
        # 使用归并排序 进行排序 在这里影响排序速度的是 分割的文本的多少 内存消耗很少
        x.sort()


    if __name__ == '__main__':
        main()

## 生成测试数据

    import random
    file = open('xx.txt', 'w')
    x = (f'{i}:{j}:{x}:{y}\n'
        for i in random.choices(range(256), k=20)
        for j in random.choices(range(256), k=10)
        for x in random.choices(range(256), k=50)
        for y in random.choices(range(256), k=10)
        )
    file.writelines(x)
