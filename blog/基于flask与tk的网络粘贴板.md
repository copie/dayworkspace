# 基于flask与tk的网络粘贴板

由于本人一直用 linux 所以平时和我的队友们交流代码 十分的不方便 没有办法 我就自己写一个功能简单但是特别适合我自己用的一个网络粘贴板
只有两个按钮 下载 和 上传 。

我的这个应用分成两个部分 一个是服务端 和一个 客户端 服务端接收到客户端发送的请求以后会保存你上传的代码如果有其他人请求下载代码的话会
返回这个代码

我们知道C++代码里面有很多的#{};?等标点符号有些符号在URL里面会有一些转义的问题为了保证我们上传和下载的代码相同 所以我用到了base64进
行加密，普通的base64加密会出现URL不安全的符号，所以我选择了python3 base64 里有一个叫做urlsafe的一个加密和解密的方法保证我们的数
据的正确性

服务端 我用的是 flask 搭建的一个简单的 API 来完成我们服务端的一些收发数据

由于我的 flask 在 Apache 上面运行失败了 队友又催着写代码没办发 我就简单的让啊我的服务端程序在后台运行在DEBUG模式
以后我再写什么 flask 的问题再解决咯。

客户端我用的是TK PS:(因为这个安装的快而且队友windows电脑上面只要装一个python就可以了) PSS:(我在由于我没有Windows电脑所以没有去折腾如何生成EXE文件，这样就不用安装Python环境了)

由于的对TK学习的不是太多所以呢，我就找了一个别人写的DOME我简单的修改了一下就可以用了(尴尬)

## 服务器端代码

    from flask import Flask
    from flask import request
    app = Flask(__name__)
    code=''
    @app.route('/')
    def hello_world():
        return code
    @app.route("/hello")
    def haha():
        return "这是一个测s "
    @app.route('/postcode', methods=['POST', 'GET'])
    def postcode():
        global code
        if request.method == "GET":
            code = request.args.get('code', '')
            return '200'
        elif request.method == 'POST':
            code = request.data

    if __name__ == '__main__':
        app.debug = True
        app.run(host='0.0.0.0')

## 桌面端的代码

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
            str1= base64.urlsafe_b64encode(str1) # 加密
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
            str1 = base64.urlsafe_b64decode(str1) # 解密
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
