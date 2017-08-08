import string
mystr = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
for c in mystr:
    if c == 'y':
        print('a',end='')
    elif c== 'z':
        print('b',end='')
    elif 'a'<=c<='z':
        print(chr(ord(c)+2),end='')
    else:
        print(c,end='')

print()

mystr="/pc/def/map"
table = str.maketrans('abcdefghijklmnopqrstuvwxyz','cdefghijklmnopqrstuvwxyzab')

mystr.translate(table)

print(mystr.translate(table))
