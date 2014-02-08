#!/usr/bin/env python2.7
# coding: utf-8
import sys
from PIL import Image, ImageDraw, ImageFont

img=Image.new('RGB',(800,600))

draw = ImageDraw.Draw(img)
font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMono.ttf', 20)

[draw.text((0, i[0]*20), i[1].rstrip('\n'), (255,255,255), font=font) for i in enumerate(sys.stdin)]
img.show()
