import requests
from PIL import Image
import pytesseract


def binarizing(img, threshold):
    # threshold表示阀值
    pixdata = img.load()
    w, h = img.size
    for y in range(h):
        for x in range(w):
            if pixdata[x, y] < threshold:
                pixdata[x, y] = 0
            else:
                pixdata[x, y] = 255
    return img


def depoint(img):
    # input: gray image
    pixdata = img.load()
    w, h = img.size
    for y in range(1, h - 1):
        for x in range(1, w - 1):
            count = 0
            if pixdata[x, y - 1] > 245:
                count = count + 1
            if pixdata[x, y + 1] > 245:
                count = count + 1
            if pixdata[x - 1, y] > 245:
                count = count + 1
            if pixdata[x + 1, y] > 245:
                count = count + 1
            if count > 2:
                pixdata[x, y] = 255
    return img


# image = binarizing(image, 140)
# image = depoint(image)
# print(image.getbbox())
# print(pytesseract.image_to_string(image))
# print('chen')
# image.show()


response = requests.get('http://acm.pdsu.edu.cn/vcode.php?0.12122042425090229')
with open('tmp.gif', 'wb') as tmp:
    for i in response:
        tmp.write(i)
    tmp.close()
with Image.open('tmp.gif') as image:
    image.show()
    image = image.convert('L')
    image = binarizing(image, 140)
    image = depoint(image)
    print(pytesseract.image_to_string(image))
    image.show()
