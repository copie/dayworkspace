# Python数据结构之二叉搜索树

## 二叉查找树简介

它是一颗空树，或者是具有以下性质的二叉树:

(1) 若左树不为空，则左树上的所有节点的值均小于e它的根节点的值。

(2) 若右树不为空，则ou右树上的所有节点的值均大于它的根节点的值。

(3) 左,右子树也分别为二叉搜索树


## Python 代码

    class Node:
        def __init__(self, data=None, left_child=None, right_child=None):
            self.data = data
            self.left_child = left_child
            self.right_child = right_child

        def __str__(self):
            # return '<class Node data = {},left_child = {}，rigth_child = {}>'.format(self.data, self.left_child, self.right_child)
            return "<{},{},{}>".format(self.data, self.left_child, self.right_child)

        def __repr__(self):
            return self.__str__()

        def copy(self, other):
            self.data = other.data
            self.left_child = other.left_child
            self.right_child = other.right_child

    class BinarySearchTree:
        def __init__(self):
            self.root = Node(data=None, left_child=Node(),
                            right_child=Node())

        def del_node(self, num, root):
            tmp = self.find_node(num, root)
            if tmp.data is None:
                # 没有找到节点删除失败
                return False
            elif tmp.left_child.data is None and tmp.right_child.data is None:
                # 如果该节点没有左孩子和右孩子
                tmp.copy(Node())
            elif tmp.left_child.data is not None and tmp.right_child.data is None:
                # 如果有左孩之没有右孩子
                tmp.copy(tmp.left_child)
            elif tmp.left_child.data is None and tmp.right_child.data is not None:
                # 如果没有左孩子有右孩子
                tmp.copy(tmp.right_child)
            else:
                # 有左右孩子
                left = tmp.left_child
                rigth = tmp.right_child
                tmp.copy(left)
                # 左孩子替代当前节点
                while tmp.data is not None:
                    tmp = tmp.right_child
                tmp.copy(rigth)
                # 右孩子连接到左孩子的最右边
            return True

        def insert_node(self, num):
            if self.root.data is None:
                self.root.data = num
                # 插入第一个数字
                return
            tmp = self.root
            # 寻找需要插入的节点
            print(tmp)
            while tmp.data is not None:
                p = tmp
                if tmp.data > num:
                    tmp = tmp.left_child
                else:
                    tmp = tmp.right_child
            # 判断插入左孩子还是右孩子
            if p.data > num:
                p.left_child.copy(
                    Node(data=num, left_child=Node(), right_child=Node()))
            else:
                p.right_child.copy(
                    Node(data=num, left_child=Node(), right_child=Node()))

        def find_node(self, num, tmp):
            if tmp.data == None or tmp.data == num:
                return tmp
            if num < tmp.data:
                return self.find_node(num, tmp.left_child)
            else:
                return self.find_node(num, tmp.right_child)

        def min(self):
            tmp = self.root
            while tmp.data is not None:
                min = tmp.data
                tmp = tmp.left_child
            return min

        def max(self):
            tmp = self.root
            while tmp.data is not None:
                max = tmp.data
                tmp = tmp.right_child
            return max
        def del_tree(self):
            del self.root
            self.root = Node(data=None, left_child=Node(),
                            right_child=Node())

    if __name__ == "__main__":
        x = BinarySearchTree()
        x.insert_node(10)
        x.insert_node(3)
        x.insert_node(2)
        x.insert_node(6)
        x.insert_node(4)
        x.insert_node(7)
        x.insert_node(18)
        x.insert_node(12)
        x.insert_node(15)
        print(x.max())
        print(x.min())
        print(x.del_node(7, x.root))
        print(x.root)
        print(x.del_node(12, x.root))
        print(x.root)
        print(x.del_node(18, x.root))
        print(x.root)
        print(x.del_node(3, x.root))
        print(x.root)
        print(x.del_node(10, x.root))
        print(x.root)
        print(x.max())
        print(x.min())
        x.del_tree()
