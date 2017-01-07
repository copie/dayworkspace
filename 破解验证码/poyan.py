from PIL import Image
import pytesseract
image = Image.open('./破解验证码/123.png')
# 由于vscode的原因图片的路径需要这么写
vcode = pytesseract.image_to_string(image)
print(vcode)
