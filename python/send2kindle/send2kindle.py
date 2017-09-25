import configparser
import getopt
import getpass
import sys

import sendmail as sm


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
