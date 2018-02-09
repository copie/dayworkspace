from pypinyin import lazy_pinyin, Style
''' 分辨一副对联那一句是上联,那一句是下联
    上联最后一个字为三声或四声
    下联最后一个字为一声或二声
    上联一般贴在右面
    下联一般贴在左面
'''

def get_pitch(hans):
    '''获取音调
        参数:  汉字,语句或词组
        返回: 一个声调元祖.  包括  1,2, 3, 4, 0.  分别表示 一到四声和轻声
    '''
    pitch_list = list()
    pinyin = lazy_pinyin(hans, style=Style.FINALS_TONE3)
    # ['en2', 'uei3'] 或  ['uo1', 'i']
    for py in pinyin:
        
        if py[-1].isdigit():
            pitch_list.append(int(py[-1]))
        else:
            pitch_list.append(0)
    return tuple(pitch_list)


def fen_bian(shang_lian, xia_lian):
    shang_lian = shang_lian.replace(' ', '') 
    xia_lian = xia_lian.replace(' ', '') 
    if get_pitch(shang_lian)[-1] < get_pitch(xia_lian)[-1]:
        shang_lian, xia_lian = xia_lian, shang_lian
    return {"上联": shang_lian, "下联": xia_lian}


def main(shang_lian, xia_lian):
    print(fen_bian(shang_lian, xia_lian))


if __name__ == '__main__':
    shang_lian = "旭日东升江山万里春意闹"
    xia_lian = "东风劲吹神州一片百花鲜"
    main(shang_lian, xia_lian)
