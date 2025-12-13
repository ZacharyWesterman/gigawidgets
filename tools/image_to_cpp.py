#!/usr/bin/env python3

from sys import argv, stderr
from PIL import Image

if len(argv) < 5:
    print('Usage: ./image_to_cpp.py <image_file> <output_width> <output_height> <name> <transparency_threshold,0-255>', file=stderr)
    print(file=stderr)
    print('Examples:', file=stderr)
    print('  ./image_to_cpp.py image.png 100 100', file=stderr)
    print('  ./image_to_cpp.py image.png 100 100 200', file=stderr)
    print(file=stderr)
    print('The first example gives a smaller file size by removing transparency.', file=stderr)
    print('The second example keeps 1-bit of transparency per pixel whose alpha is >= 200.', file=stderr)
    exit(0)

transparent = len(argv) > 5
transparency_threshold = int(argv[5])

image = Image.open(argv[1])
image = image.resize((int(argv[2]), int(argv[3])))

width, height = image.size

print('// clang-format off')
print('#pragma once')
print('#include "../core/bitmap.hpp"')
print('namespace ui { namespace icon {')
print(
    f"const auto {argv[4]} = ui::{'TransparentBitmap' if transparent else 'Bitmap'}({{{width},{height}}},(ui::color_t[]){{", end='')


def color565(r, g, b) -> int:
    return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xff) >> 3)


for y in range(height):
    for x in range(width):
        r, g, b, a = image.getpixel((x, y))
        print(f'{color565(r, g, b)},', end='')

if transparent:
    bits = ''
    print('},(uint8_t[]){', end='')
    for y in range(height):
        for x in range(width):
            if len(bits) >= 8:
                print(f'0b{bits},', end='')
                bits = ''
            r, g, b, a = image.getpixel((x, y))
            bits += '1' if a >= transparency_threshold else '0'

        # Renderer always moves to the next byte when it hits the end of the line
        if len(bits):
            for i in range(len(bits), 9):
                bits += '0'
            print(f'0b{bits},', end='')
            bits = ''

    if len(bits):
        for i in range(len(bits), 9):
            bits += '0'
        print(f'0b{bits},', end='')

print('});')
print('}}')
print('// clang-format on')
