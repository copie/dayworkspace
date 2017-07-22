# import tkinter as tk

# class Application(tk.Frame):
#     def __init__(self, master=None):
#         super().__init__(master)
#         self.pack()
#         self.create_widgets()

#     def create_widgets(self):

#         self.hi_there = tk.Button(self)
#         self.hi_there["text"] = "提交"
#         self.hi_there["command"] = self.uploder
#         self.hi_there.pack(side="bottom")
#     def uploder(self):
#         print("提交成功!")
# root = tk.Tk()
# app = Application(master=root)
# app.mainloop()
#-*- coding:utf-8 -*-

"""
Text    文本框样例
实现功能有：Ctrl+a全选文本， 竖向滚动条，横向滚动条（不自动换行） 自动缩放

有谁知道全选文本的方法为会要 return 'break' 吗？
"""


import tkinter
import requests
import base64

class MainFrame(tkinter.Frame):
    def __init__(self, master=None):
        tkinter.Frame.__init__(self, master)
        self.grid(row=0, column=0, sticky="nsew")
        self.createFrame()

    def createFrame(self):
        label_frame_top = tkinter.LabelFrame(self)


        label_frame_center = tkinter.LabelFrame(self)
        label_frame_center.pack(fill="x")

        lfc_field_1 = tkinter.LabelFrame(label_frame_center)
        lfc_field_1.pack(fill="x")

        self.lfc_field_1_l = tkinter.Button(lfc_field_1, text="下载更新最新代码", width=10,command=self.downloder)
        self.lfc_field_1_l.pack(fill="y", expand=0, side=tkinter.LEFT)

        self.lfc_field_1_b = tkinter.Button(lfc_field_1, text="上传我的代码", width=10, height=1, command=self.uploder)
        self.lfc_field_1_b.pack(fill="y", expand=0, side=tkinter.RIGHT)

        ##########文本框与滚动条
        self.lfc_field_1_t_sv = tkinter.Scrollbar(lfc_field_1, orient=tkinter.VERTICAL)  #文本框-竖向滚动条
        self.lfc_field_1_t_sh = tkinter.Scrollbar(lfc_field_1, orient=tkinter.HORIZONTAL)  #文本框-横向滚动条

        self.lfc_field_1_t = tkinter.Text(lfc_field_1, height=25, yscrollcommand=self.lfc_field_1_t_sv.set,
                                          xscrollcommand=self.lfc_field_1_t_sh.set, wrap='none')  #设置滚动条-不换行
        #滚动事件
        self.lfc_field_1_t_sv.config(command=self.lfc_field_1_t.yview)
        self.lfc_field_1_t_sh.config(command=self.lfc_field_1_t.xview)

        #布局
        self.lfc_field_1_t_sv.pack(fill="y", expand=0, side=tkinter.RIGHT, anchor=tkinter.N)
        self.lfc_field_1_t_sh.pack(fill="x", expand=0, side=tkinter.BOTTOM, anchor=tkinter.N)
        self.lfc_field_1_t.pack(fill="x", expand=0, side=tkinter.LEFT)

        #绑定事件
        self.lfc_field_1_t.bind("<Control-Key-a>", self.selectText)
        self.lfc_field_1_t.bind("<Control-Key-A>", self.selectText)


        ##########文本框与滚动条end



        label_frame_bottom = tkinter.LabelFrame(self)
        #label_frame_bottom.pack()

        pass

    #文本全选
    def selectText(self, event):
        self.lfc_field_1_t.tag_add(tkinter.SEL, "1.0", tkinter.END)
        #self.lfc_field_1_t.mark_set(tkinter.INSERT, "1.0")
        #self.lfc_field_1_t.see(tkinter.INSERT)
        return 'break'  #为什么要return 'break'

    
    def uploder(self):
        str1=self.lfc_field_1_t.get('0.0','end')
        str1=str1.encode(encoding="utf-8")
        str1= base64.urlsafe_b64encode(str1)
        print(str(str1))
        str1 = "http://copie.cn:5000/postcode?code="+str(str1)
        # print(str1)
        req = requests.get(str1)
        print("上传了")
        # print(str1)
        # print(req)
        

    def downloder(self):
        req = requests.get("http://copie.cn:5000/")
        
        print("下载成功")
        print(req.text)
        str1 = req.text[2:-1].encode(encoding="utf-8")
        print(str1)
        str1 = base64.urlsafe_b64decode(str1)
        print(str1.decode())
        self.lfc_field_1_t.delete('0.0', 'end')
        self.lfc_field_1_t.insert('0.0', str1.decode())


def main():
    root = tkinter.Tk()
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.geometry('640x360')  #设置了主窗口的初始大小960x540 800x450 640x360

    main_frame = MainFrame(root)
    main_frame.mainloop()


if __name__ == "__main__":
    main()
    pass
