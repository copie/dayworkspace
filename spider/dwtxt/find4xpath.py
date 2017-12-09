from lxml import etree

def find4xpath(html,xpath):
    selector = etree.HTML(html)
    content = selector.xpath(xpath)
    return content
