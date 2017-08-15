import base64
import tkinter
from tkinter import filedialog

import requests

from tkinter import messagebox

HOST = '115.159.219.118'
PORT = '5000'


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

        self.lfc_field_1_l = tkinter.Button(
            lfc_field_1, text="下载代码", width=10, command=self.downloder)
        self.lfc_field_1_l.pack(fill="y", expand=0, side=tkinter.LEFT)

        self.lfc_field_1_filedown = tkinter.Button(
            lfc_field_1, text="下载文件", width=10, command=self.downfile)
        self.lfc_field_1_filedown.pack(fill="y", expand=1, side=tkinter.LEFT)

        self.lfc_field_1_b = tkinter.Button(
            lfc_field_1, text="上传代码", width=10, height=1, command=self.uploder)
        self.lfc_field_1_b.pack(fill="y", expand=0, side=tkinter.RIGHT)

        self.lfc_field_1_fileup = tkinter.Button(
            lfc_field_1, text="上传文件", width=10, height=1, command=self.upfile)
        self.lfc_field_1_fileup.pack(fill="y", expand=0, side=tkinter.RIGHT)

        # 文本框与滚动条
        self.lfc_field_1_t_sv = tkinter.Scrollbar(
            lfc_field_1, orient=tkinter.VERTICAL)  # 文本框-竖向滚动条
        self.lfc_field_1_t_sh = tkinter.Scrollbar(
            lfc_field_1, orient=tkinter.HORIZONTAL)  # 文本框-横向滚动条

        self.lfc_field_1_t = tkinter.Text(lfc_field_1, height=25, yscrollcommand=self.lfc_field_1_t_sv.set,
                                          xscrollcommand=self.lfc_field_1_t_sh.set, wrap='none')  # 设置滚动条-不换行
        # 滚动事件
        self.lfc_field_1_t_sv.config(command=self.lfc_field_1_t.yview)
        self.lfc_field_1_t_sh.config(command=self.lfc_field_1_t.xview)

        # 布局
        self.lfc_field_1_t_sv.pack(
            fill="y", expand=0, side=tkinter.RIGHT, anchor=tkinter.N)
        self.lfc_field_1_t_sh.pack(
            fill="x", expand=0, side=tkinter.BOTTOM, anchor=tkinter.N)
        self.lfc_field_1_t.pack(fill="x", expand=0, side=tkinter.LEFT)

        # 绑定事件
        self.lfc_field_1_t.bind("<Control-Key-a>", self.selectText)
        self.lfc_field_1_t.bind("<Control-Key-A>", self.selectText)

        # 文本框与滚动条end

        label_frame_bottom = tkinter.LabelFrame(self)
        # label_frame_bottom.pack()

    # 文本全选
    def selectText(self, event):
        self.lfc_field_1_t.tag_add(tkinter.SEL, "1.0", tkinter.END)
        return 'break'  # 为什么要return 'break'

    # 上传代码 用base64进行加密
    def uploder(self):
        code = self.lfc_field_1_t.get('0.0', 'end')
        code = code.encode(encoding="utf-8")
        code = base64.urlsafe_b64encode(code)
        url = "http://" + HOST + ":" + PORT + "/postcode?code=" + str(code)
        
        try:
            req = requests.get(url)
            if req.text == "200":
                messagebox.showinfo("成功", "上传成功")
                # 清空文本框
                self.lfc_field_1_t.delete('0.0', 'end')
            else:
                messagebox.showinfo("失败", "管理员服务器炸了")
        except:
            messagebox.showinfo("失败", "管理员服务器炸了")

    # 下载代码 用base64进行解密
    def downloder(self):
        try:
            url = "http://" + HOST + ":" + PORT
            req = requests.get(url)
        except:
            return
        code = req.text[2:-1].encode(encoding="utf-8")
        code = base64.urlsafe_b64decode(code)
        self.lfc_field_1_t.delete('0.0', 'end')
        self.lfc_field_1_t.insert('0.0', code.decode())
    # 上传文件

    def upfile(self):

        url = "http://" + HOST + ":" + PORT + "/upfile"
        # 让用户选择文件
        filename = filedialog.askopenfilename()
        self.lfc_field_1_t.delete('0.0', 'end')
        self.lfc_field_1_t.insert('0.0', "开始上传文件......")
        try:
            files = {'file': open(str(filename), 'rb')}
            req = requests.post(url, files=files)
            if req.status_code == 200:
                messagebox.showinfo("成功", "上传成功")
            else:
                messagebox.showinfo("失败", "管理员服务器炸了")
        except:
            messagebox.showinfo("失败", "管理员服务器炸了")
        finally:
            self.lfc_field_1_t.delete('0.0', 'end')

    # 下载文件
    def downfile(self):
        try:
            # 让用户选择保存的路径和文件名_会自动添加文件的扩展名
            filename = filedialog.asksaveasfilename()
            self.lfc_field_1_t.delete('0.0', 'end')
            self.lfc_field_1_t.insert('0.0', "开始下载文件......\n")

            filename = filename + '.' + \
                requests.get("http://" + HOST + ":" +
                             PORT + "/downfiletype").text

            self.lfc_field_1_t.insert('0.0', "获取文件扩展名成功......")

            req = requests.get("http://" + HOST + ":" + PORT + "/downfile")
            if req.status_code == 200:
                with open(filename, 'wb') as savefile:
                    savefile.write(req.content)
                messagebox.showinfo("成功", "下载成功")
            else:
                messagebox.showinfo("失败", "管理员服务器炸了")
        except:
            messagebox.showinfo("失败", "管理员服务器炸了")
        finally:
            self.lfc_field_1_t.delete('0.0', 'end')



def main():
    root = tkinter.Tk()
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    root.geometry('960x360')  # 设置了主窗口的初始大小960x540 800x450 640x360

    main_frame = MainFrame(root)
    main_frame.mainloop()


if __name__ == "__main__":
    main()
