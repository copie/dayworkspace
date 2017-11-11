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
