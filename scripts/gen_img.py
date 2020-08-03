import cv2
import sys
import math
import numpy as np
from typing import List

H_TEMPLATE = """
/*
 * Auto Generated Image H file for Heli Project
 *
 * Author: Jos Craw 2020
 */

#include <stdint.h>

const char {iname}[] = {lbrace}
{data}{rbrace};

uint16_t {iname}_width = {width};
uint16_t {iname}_height = {height};
"""

def gen_h_file(char_array: List, width: int, height: int, image_name: str):
    data = ""
    for line in char_array:
        data_line = ', '.join(hex_char for hex_char in line)
        print(data_line)
        data += "    {},\n".format(data_line)
    data = data[:-2]

    file_data = H_TEMPLATE.format(iname=image_name,
        lbrace='{',
        rbrace='}',
        data=data,
        width=width,
        height=height)
    
    with open('{}.h'.format(image_name), "w+") as h_file:
        _ = h_file.write(file_data)


def get_char_array(black_white_img):
    height = len(black_white_img)
    width = len(black_white_img[0])

    char_height = int(math.ceil(height/8.0))
    char_width = int(math.ceil(width/8.0))

    split_list = [ black_white_img[i*8:(i+1)*8] for i in range((len(black_white_img) + 7) // 8)]

    img_transpose = [np.matrix.transpose(array) for array in split_list]

    hex_img = []

    for char_line in img_transpose:
        hex_line = []
        for byte in char_line:
            binary_string = ''.join(str(char) for char in byte)
            hex_line.append('0x{:02x}'.format(int(binary_string, 2)))
        hex_img.append(hex_line)

    return hex_img


def main():
    if len(sys.argv) != 2:
        print("Usage: python gen_img.py $FILENAME")
        exit(1)
    
    file_name = sys.argv[1]
    image_name = file_name.split('.')[0]

    image = cv2.imread(file_name)
    grey_img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    (_, black_white_img) = cv2.threshold(grey_img, 127, 255, cv2.THRESH_BINARY)

    print(len(black_white_img))

    height = len(black_white_img)
    width = len(black_white_img[0])

    black_white_img = black_white_img / 255 
    black_white_img = black_white_img.astype('int8')

    hex_img = get_char_array(black_white_img)

    gen_h_file(hex_img, width, height, image_name)

    
    
        




if __name__ == "__main__":
    main()