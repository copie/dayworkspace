# 基于flask与tk的网络粘贴板升级版

自从上一次我的代码粘贴板完成基本的功能以后我就我好长时间没有动这个代码了，我们之间相互传输文件也不是很方便于是我就加入了这个功能

## 服务端实现 

### 文件上传与保存

    @app.route('/upfile', methods=['POST'])
    def upfile():
        if request.method == 'POST':
            global filepath
            global myfilename
            global myfiletype
            file = request.files['file']
            if file:
                myfiletype = file.filename.split('.')[-1]
                # 提取文件的扩展名
                myfilename = str(abs(hash(file.filename)))
                # 由于上传的文件可能文件名比较奇葩所以对文件名进行hash保存
                file.save(os.path.join(
                    app.config['UPLOAD_FOLDER'], filepath + myfilename))
                # 保存文件
                return "yes"
            return "200"

### 文件下载相应

    @app.route('/downfile', methods=['GET'])
    def downfile():
        request.method == 'GET'
        # print(myfilename)
        
        if os.path.isfile("/home/" + getpass.getuser()+"/codeguiup/"+myfilename):
            print(myfilename)
            return send_from_directory("/home/" + getpass.getuser()+'/codeguiup/', myfilename, as_attachment=True)
            # 通过 send_from_directory 发送想要的文件
        else:
            return '404'

    # 相应客户端对于文件扩展名的请求
    @app.route('/downfiletype',methods=['GET'])
    def downfiletype():
        print(myfiletype)
        return myfiletype
## 客户端实现

### 客户端上传文件

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
### 客户端下载文件

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

**代码风格糟糕  手动苦笑**


