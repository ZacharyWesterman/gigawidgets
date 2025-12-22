#!/usr/bin/env python3

import re
from pathlib import Path
from argparse import ArgumentParser, ArgumentTypeError
from PIL import Image
import cairosvg
from sys import stderr


def color565(r, g, b) -> int:
    return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xff) >> 3)


def color_hex(s: str) -> int:
    if re.match(r'^[0-9a-fA-F]+$', s):
        r, g, b = int(s[0:2], 16), int(s[2:4], 16), int(s[4:6], 16)
        return color565(r, g, b)

    raise ArgumentTypeError(
        f'not a valid hex color of the format "abcdef": {s!r}')


parser = ArgumentParser(
    prog='image_to_cpp',
    description='Convert an image into the C++ code for a GigaWidget image.',
)
parser.add_argument('filename', help='The input image.')
parser.add_argument('width', type=int, help='The width of the output image.')
parser.add_argument('height', type=int, help='The height of the output image.')
parser.add_argument('name', help='The variable name of the output image.')
parser.add_argument(
    '-t',
    '--transparency',
    type=int,
    help=(
        'The transparency threshold. ' +
        'any alpha below this is treated as fully transparent. ' +
        'If not set, the alpha channel is ignored.'
    )
)
parser.add_argument(
    '-m',
    '--monochrome',
    type=color_hex,
    help='Replace all non-transparent pixels with a single color.',
)
parser.add_argument(
    '-c',
    '--compress',
    action='store_true',
    help='Attempt to compress image data to save space.',
)

args = parser.parse_args()
filename = args.filename
tempfile = False

if filename.lower().endswith('.svg'):
    filename = '.temp.image_to_cpp.png'
    tempfile = True
    cairosvg.svg2png(
        url=args.filename,
        write_to=filename,
        output_width=args.width,
        output_height=args.height,
    )

image = Image.open(filename)

if image.size[0] != args.width or image.size[1] != args.height:
    image = image.resize((args.width, args.height))

if tempfile:
    Path(filename).unlink(missing_ok=True)


class Bitmap:
    def header(self):
        class_name = self.__class__.__name__
        include_name = re.sub(r'(?<!^)(?=[A-Z])', '_', class_name).lower()

        print('// clang-format off')
        print('#pragma once')
        print(f'#include "../core/renderable/{include_name}.hpp"')
        print('namespace ui { namespace icon {')
        print(
            f'const auto {args.name} = ' +
            f'ui::{class_name}({{{image.width},{image.height}}}',
            end=''
        )

    def body(self):
        print(', (ui::color_t[]){', end='')
        for y in range(image.height):
            for x in range(image.width):
                r, g, b, _ = image.getpixel((x, y))
                print(f'{color565(r, g, b)},', end='')
        print('}', end='')

    def footer(self):
        print(');')
        print('}}')
        print('// clang-format on')

    def print(self):
        self.header()
        self.body()
        self.footer()


class TransparentBitmap(Bitmap):
    def body(self):
        super().body()
        self.mask()

    def mask(self):
        print(', (uint8_t[]){', end='')
        for i in self.bytes():
            print(f'{i},', end='')
        print('}', end='')

    def bytes(self):
        byte = 0
        shift = 0
        for y in range(image.height):
            for x in range(image.width):
                _, _, _, a = image.getpixel((x, y))
                byte = byte * 2 + int(a >= args.transparency)
                shift += 1
                if shift >= 8:
                    yield byte
                    shift = 0
                    byte = 0
            # Renderer always moves to the next byte when it hits the end of the line
            if shift > 0:
                for _ in range(shift, 8):
                    byte *= 2
                yield byte
                shift = 0
                byte = 0

        # Adjust the last byte and spit it out.
        if shift > 0:
            for _ in range(shift, 8):
                byte *= 2
            yield byte


class TransparencyMap(TransparentBitmap):
    def print(self):
        self.header()
        print(f', {args.monochrome}', end='')
        self.mask()
        self.footer()


class CompressedTransparencyMap(TransparencyMap):
    def mask(self):
        print(', (uint8_t[]){', end='')

        init = False
        ct = 0
        last_byte = 0
        for byte in self.bytes():
            if not init:
                init = True
            elif ct >= 255 or last_byte != byte:
                print(f'{ct},{last_byte},', end='')
                ct = 0

            last_byte = byte
            ct += 1

        print(f'{ct},{last_byte},', end='')
        print('}', end='')


if args.monochrome and not args.transparency:
    print('ERROR: Monochrome without transparency?!', file=stderr)
    exit(1)

if args.monochrome is not None:
    if args.compress:
        render = CompressedTransparencyMap()
    else:
        render = TransparencyMap()
elif args.transparency is not None:
    render = TransparentBitmap()
else:
    render = Bitmap()

render.print()
