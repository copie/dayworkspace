from PIL import Image
import pytesseract
# image = Image.open('./破解验证码/2.jpg')
image = Image.open('./破解验证码/asd.gif')
image = image.convert('L')


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


image = binarizing(image, 140)
image = depoint(image)
print(image.getbbox())
print(pytesseract.image_to_string(image))
print('chen')
image.show()
