class stack:

    def __init__(self):
        self.my_stack=[]
    def __len__(self):
        return len(self.my_stack)
    def size(self):
        return len(self.my_stack)
    def top(self):
        return self.my_stack[-1]
    def pop(self):
        return self.my_stack.pop()
    def push(self,x):
        return self.my_stack.append(x)
    def empty(self):
        return True if len(self.my_stack) == 0 else False
    def count(self,x):
        return self.my_stack.count(x)
    def __iter__(self):
        return iter(self.my_stack)
    def __repr__(self):
        return str(self.my_stack[::-1]) 
if __name__ =="__main__":
    my = stack()
    my.push(1)
    print(my.top())
    my.push(2)
    print(my.top())
    my.pop()
    print(my.top())
    my.top()
