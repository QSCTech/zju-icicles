#coding=utf-8
'''
  author: Zewen-Ye
  time: 2019-04-29
  function: this code is used to read an image and save RGB data to outfile
'''

import sys
import struct
from PIL import Image

if len(sys.argv) != 3:
  print("Usage: python read_image.py image_file outfile")
  exit()  

img = Image.open(sys.argv[1])
print("The input image mode is: ") # RGBA
print(img.mode)
print("The input image size is: ") # 2048,1024
w,h = img.size
print(w,h)

# out to file
outfile = open(sys.argv[2],'wb')
outfile.write(struct.pack('i',w))
outfile.write(struct.pack('i',h))

# new_img = Image.new(mode="RGB", size=(w, h))
temp = img.load()


str = 'h'
for i in range(h):# 1024
  for j in range(w):# 2048
    r,_,_,_ = temp[j,i]
    outfile.write(struct.pack(str,r))

for i in range(h):# 1024
  for j in range(w):# 2048
    _,g,_,_ = temp[j,i]       
    outfile.write(struct.pack(str,g))

for i in range(h):# 1024
  for j in range(w):# 2048
    _,_,b,_ = temp[j,i]    
    outfile.write(struct.pack(str,b))

img.close()
outfile.close()
