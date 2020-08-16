# Image/Animation generation
The gen_img.py script accepts an input of either one or multiple files. These files are then interpeted and
output as an `.h` file to be inserted into the program. All image types supported by OpenCV2 `imread` function
are supported.

## Usage

To generate an animation:
```console
user@linux:~$ python gen_img.py image0 image1 image2 ...
```


To generate a single image:
```console
user@linux:~$ python gen_img.py image
```

Options:
```
usage: gen_img.py [-h] [-i] [-o OUTPUT] input [input ...]
gen_img.py: error: the following arguments are required: input
```