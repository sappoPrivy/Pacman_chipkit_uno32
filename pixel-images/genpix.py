
#genpix.py
# Created by Tenzin Sangpo Choedon

import sys
from PIL import Image

empty        = 0xff3bff         # Pink
wall         = 0xffffff         # White
portal       = 0xff7003         # Orange
food         = 0x4dff3d         # Green
inaccessible = 0x000000         # Black
ghost        = 0x9e54ff         # Purple
origin       = 0xfff200         # Yellow
spawn        = 0xff0022         # Red

# get the correct data on the pixel depending on the color
def get_data_on_pixel(hex):
    map_color = {
        origin: 'O',
        spawn: 'S',
        food: 'F',
        empty: 'E',
        ghost: 'G',
        wall: 'W',
        portal: 'P',
        inaccessible: 'I'
    }

    return map_color.get(hex, 'I')

# generate a file that writes a bitmap
def generate_bitmap(imageName):
        img  = Image.open(imageName, "r")
        bitmap = open(imageName + ".txt", "wb")
        w, h = img.size
        data = list(img.getdata())
                
        for i in range(0, 32):
                for j in range(0, 128):
                        redComponent = (data[w*i + j][0] << 16)
                        greenComponent = (data[i*w + j][1] << 8)
                        blueComponent = (data[i*w + j][2])
                        # Combine the red, green and blue component of the RGB value into hexdec value
                        hex =  redComponent | greenComponent | blueComponent
                        data_on_pixel = get_data_on_pixel(hex)
                        bitmap.write((data_on_pixel + ',').encode())
                
                bitmap.write(('\n').encode())
                
        img.close()
        bitmap.close()
        print(imageName + ".txt has finished generating")
        

def main(argc, argv):
        for i in range(1, argc):
                print
                generate_bitmap(argv[i])

main(len(sys.argv), sys.argv)
