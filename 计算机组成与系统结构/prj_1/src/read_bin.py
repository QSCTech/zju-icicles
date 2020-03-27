import sys
from PIL import Image
import struct

if len(sys.argv)!=2:
  print("Usage: python read_bin.py in_bin_file")

infile = open(sys.argv[1],'rb')
# infile = open('y.bin','rb')
w = int(struct.unpack("i",infile.read(4))[0])
h = int(struct.unpack("i",infile.read(4))[0])
print("The picture\'s size is:")
print(w,h)

# short
str = 'h'
num = 2

pixel_r = (struct.unpack(str*h*w,infile.read(num*h*w)))
pixel_g = (struct.unpack(str*h*w,infile.read(num*h*w)))
pixel_b = (struct.unpack(str*h*w,infile.read(num*h*w)))
pixel_a = (struct.unpack(str*h*w,infile.read(num*h*w)))

infile.close()

print("Putting pixels to new images...")
cnt = 0
new_img_r = Image.new('L',(w,h))
new_img_g = Image.new('L',(w,h))
new_img_b = Image.new('L',(w,h))
new_img_a = Image.new('L',(w,h))
new_img_rgb = Image.new('RGB',(w,h))
new_img_0 = Image.new('RGBA',(w,h))

img_r = new_img_r.load()
img_g = new_img_g.load()
img_b = new_img_b.load()
img_a = new_img_a.load()
img_0 = new_img_0.load()
img_rgb = new_img_rgb.load()

for i in range(h):
  for j in range(w):
    temp_r = int(pixel_r[cnt])
    temp_g = int(pixel_g[cnt])
    temp_b = int(pixel_b[cnt])
    temp_a = int(pixel_a[cnt])

    img_r[j,i] = (temp_r)
    img_g[j,i] = (temp_g)
    img_b[j,i] = (temp_b)
    img_a[j,i] = (temp_a)    
    img_rgb[j,i] = (temp_r,temp_g,temp_b)
    img_0[j,i] = (temp_r,temp_g,temp_b,temp_a)
    cnt+=1


print("Creating png files...")
new_img_r.save("output/out_image_r.png","png")
new_img_g.save("output/out_image_g.png","png")
new_img_b.save("output/out_image_b.png","png")
new_img_a.save("output/out_image_a.png","png")
new_img_rgb.save("output/out_image_rgb.png","png")
new_img_0.save("output/out_im_rgba.png","png")
