# -------------------------------
# Tiva Image/Animation Generator
# -------------------------------
# 
# Generates image/animation header files for use
# with the Tiva TM4c123 and the OrbitBooster Pack
#
# Author: Jos Craw 2020
#
import cv2
import math
import argparse
import numpy as np
from typing import List

IMG_DEFN = """
const char {frame}[] = {lbrace}
{data}
{rbrace};
"""

FRAMES_LIST = """
const char* {iname}_frames[{num}] = {lbrace}
{data}
{rbrace};
"""

H_TEMPLATE = """
/*
 * Auto Generated Image H file for Heli Project
 *
 * Author: Jos Craw 2020
 */

#include <stdint.h>

{data}

uint16_t {iname}_width = {width};
uint16_t {iname}_height = {height};
"""

def gen_h_file(char_array: List, width: int, height: int, image_name: str):
    frames = []
    frame_num = 0
    frame_list = []
    for frame in char_array:
        frame_data = ""
        for line in frame:
            data_line = ', '.join(hex_char for hex_char in line)
            frame_data += "    {},\n".format(data_line)
        frame_data = frame_data[:-2]

        if len(char_array) == 1:
            frame_name = image_name
        else:
            frame_name = "{}_frame_{}".format(image_name, frame_num)
            frame_list.append("    "+frame_name)
        
        frames.append(IMG_DEFN.format(frame=frame_name,
                    lbrace='{',
                    rbrace='}',
                    data=frame_data))
        frame_num += 1

    h_data = '\n'.join(frame for frame in frames)

    if len(char_array) > 1:
        frame_list = ",\n".join(frame_name for frame_name in frame_list)
        frame_list_h = FRAMES_LIST.format(iname=image_name,
                                          lbrace='{',
                                          rbrace='}',
                                          num=frame_num,
                                          data=frame_list)
        h_data += "\n{}".format(frame_list_h)
        h_data += "\nuint8_t {}_frame_count = {};".format(image_name, frame_num)

    file_data = H_TEMPLATE.format(iname=image_name,
                lbrace='{',
                rbrace='}',
                data=h_data,
                width=width,
                height=height)
    with open('{}.h'.format(image_name), "w+") as h_file:
        _ = h_file.write(file_data)


def get_char_array(black_white_img):
    height = len(black_white_img)
    width = len(black_white_img[0])

    char_height = int(math.ceil(height/8.0))
    char_width = int(math.ceil(width/8.0))

    # print(black_white_img)
    split_list = [ black_white_img[i*8:(i+1)*8] for i in range((len(black_white_img) + 7) // 8)]
    # print(split_list)

    img_transpose = [np.matrix.transpose(array) for array in split_list]
    # print(img_transpose)

    hex_img = []

    for char_line in img_transpose:
        hex_line = []
        for byte in char_line:
            byte = byte[::-1]
            binary_string = ''.join(str(char) for char in byte)
            hex_line.append('0x{:02x}'.format(int(binary_string, 2)))
        hex_img.append(hex_line)

    return hex_img


def main():
    parser = argparse.ArgumentParser(description='Converts Images to headerfiles to be used to show images and animations on the Tiva Orbit OLED.')


    parser.add_argument('-i',
                       '--invert',
                       action='store_true',
                       help='Invert the image colours',
                       required=False
                       )

    parser.add_argument('-o',
                        '--output',
                        action="store",
                        type=str,
                        help='Defines the image name',
                        required=False
    )

    parser.add_argument('--width',
                        action="store",
                        type=int,
                        help='Define the output image width',
                        required=False
    )

    parser.add_argument('--height',
                        action="store",
                        type=int,
                        help='Define the output image height',
                        required=False
    )

    parser.add_argument('input', nargs="+", help="List of images to store in output .h file")

    args = parser.parse_args()
    
    file_names = args.input
    if len(file_names) == 0:
        parser.print_help()
        exit(1)

    if args.output == None:
        image_name = file_names[0].split('.')[0].lower() + "_image"
    else:
        image_name = args.output

    hex_files = []

    
    for file_name in file_names:
        image = cv2.imread(file_name)

        width = 0
        height = 0
        if args.width != None:
            width = args.width
        else:
            width = image.shape[1]

        if args.height != None:
            height = args.height
        else:
            height = image.shape[0]

        dim = (width, height)

        image = cv2.resize(image, dim, interpolation = cv2.INTER_AREA)

        grey_img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        (_, black_white_img) = cv2.threshold(grey_img, 127, 255, cv2.THRESH_BINARY)

        if args.invert == True:
            black_white_img = ~black_white_img

        # print(len(black_white_img))

        height = len(black_white_img)
        width = len(black_white_img[0])

        black_white_img = black_white_img / 255 
        black_white_img = black_white_img.astype('int8')

        hex_img = get_char_array(black_white_img)
        hex_files.append(hex_img)

    gen_h_file(hex_files, width, height, image_name)


if __name__ == "__main__":
    main()