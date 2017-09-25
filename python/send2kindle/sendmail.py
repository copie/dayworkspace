import random
import smtplib
from email import encoders
from email.header import Header
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import formataddr, parseaddr


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
