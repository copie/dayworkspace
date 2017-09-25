# 命令行下发送文件给Kindle

我们知道， 给Kindle 发送文件 只要给自己的 亚马逊邮箱发送 一个邮件就可以了 邮件的附件就是我们要发的文件。简单来说我的这个程序就是实现在命令行下发送邮件。我对原有的模块进行了新的包装。让自己的程序专注与发邮件。不去考虑具体是怎么发送的就可以了。Python下发送电子邮件。

## sendmail.py

    from email import encoders
    from email.header import Header
    from email.mime.text import MIMEText
    from email.utils import parseaddr, formataddr
    from email.mime.multipart import MIMEMultipart
    import smtplib
    import random


    class sendmail:
        def __init__(self, from_addr, password, to_addr, smtp_server, head='', message='', filepath='', name='copie'):
            self.from_addr = from_addr
            self.password = password
            self.to_addr = to_addr
            self.smtp_server = smtp_server
            self.filepath = filepath
            self.message = message
            self.name = name
            self.head = head

        def _format_addr(self, s):
            name, addr = parseaddr(s)
            return formataddr((Header(name, 'utf-8').encode(), addr))

        def send(self):
            msg = MIMEMultipart()
            msg.attach(MIMEText(self.message, 'html', 'utf-8'))
            msg['From'] = self._format_addr(self.name + ' <%s>' % self.from_addr)
            msg['To'] = self._format_addr('管理员 <%s>' % self.to_addr)
            msg['Subject'] = Header(self.head, 'utf-8').encode()

            if self.filepath != '':
                try:
                    with open(self.filepath, 'rb') as f:
                        att1 = MIMEText(f.read(), 'base64', 'utf-8')
                        att1["Content-Type"] = 'application/octet-stream'
                        filename = str(random.randint(10000000, 99999999)) + \
                            '.' + self.filepath.split('/')[-1].split('.')[1]
                        # 这里的filename可以任意写，写什么名字，邮件中显示什么名字
                        att1["Content-Disposition"] = 'attachment; filename=' + filename
                        msg.attach(att1)
                except FileNotFoundError:
                    print('文件打开失败...可能文件不存在...')
                    exit(1)

            server = smtplib.SMTP_SSL(self.smtp_server)
            server.set_debuglevel(1)
            server.login(self.from_addr, self.password)
            server.sendmail(self.from_addr, [self.to_addr], msg.as_string())
            server.quit()


    if __name__ == "__main__":

        s = sendmail('kindle@copie.cn', 'woshimima', 'admin@copie.cn',
                    smtp_server='smtp.exmail.qq.com', head='这是一个测试',
                    message='我是正文呢', filepath='/home/copie/Downloads/很纯很暧昧.txt')
        s.send()

## send2kindle.py

    import sendmail as sm
    import getopt
    import sys
    import configparser
    import getpass


    def Usage():
        print('''
        send2kindle.pyusage:
        -h, --help: print help message
        -v, --version: print script version
        --file: input file path
        --message: message
        --head： the email head
        ''')


    def Version():
        print('    version = 0.1')


    def get_args(argv):
        try:
            opts, args = getopt.getopt(
                argv[1:], 'hfmv', ['file=', 'message=', 'head=', 'version'])
        except getopt.GetoptError as e:
            print(e)
            Usage()
            exit(1)

        filepath = ''
        message = ''
        head = ''

        for o, a in opts:
            if o in ('-h', '--help'):
                Usage()
            if o in ('-v', '--version'):
                Version()
            if o in ('--file'):
                filepath = a
                print(filepath)
            if o in ('--message'):
                message = a
                print(message)
            if o in ('--head'):
                head = a
                print(head)
        return [filepath, message, head]


    if __name__ == "__main__":
        config = configparser.ConfigParser()
        config.read('.send2kindlerc')
        x = config.sections()
        if x == ['info']:
            from_addr = config.get('info', 'from_addr')
            password = config.get('info', 'password')
            to_addr = config.get('info', 'to_addr')
            smtp_server = config.get('info', 'smtp_server')
        else:
            print('你也许是第一次用本程序现在开始设置配置文件')
            from_addr = input('from_addr: ')
            password = getpass.getpass("passwd: ")
            to_addr = input('to_addr: ')
            smtp_server = input('smtp_server: ')
            config.add_section("info")
            config.set('info', 'from_addr', from_addr)
            config.set('info', 'password', password)
            config.set('info', 'to_addr', to_addr)
            config.set('info', 'smtp_server', smtp_server)
        filepath, message, head = get_args(sys.argv)
        print(from_addr, password, to_addr, smtp_server,filepath,message,head)
        if filepath == '' and message == '':
            Usage()
            exit(1)
        try:
            email = sm.sendmail(from_addr, password, to_addr, smtp_server,
                        head=head, message=message, filepath=filepath)
            email.send()
            config.write(open(".send2kindlerc", "w"))
        except Exception:
            print("发送失败！！！！")

## 总结

具体使用方法就是

    python3 send2kindle.py --message="这是一个最终的测试" --head="真不容易" --file='/home/copie/Downloads/很纯很暧昧.txt'

类似这个样子，第一次会被要求填写配置文件，以后就不用了。