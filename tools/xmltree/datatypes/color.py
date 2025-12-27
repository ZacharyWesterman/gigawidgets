import re
from ..logging import warn
from . import Datatype


def color565(r, g, b) -> int:
    return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xff) >> 3)


class Color(Datatype):
    def __init__(self, data: str):
        builtin_colors = [
            'WHITE',
            'BLACK',
            'GRAY',
            'RED',
            'ORANGE',
            'YELLOW',
            'GREEN',
            'CYAN',
            'BLUE',
            'PURPLE',
            'MAGENTA',
            'LIGHT_GRAY',
            'LIGHT_RED',
            'LIGHT_ORANGE',
            'LIGHT_YELLOW',
            'LIGHT_GREEN',
            'LIGHT_CYAN',
            'LIGHT_BLUE',
            'PINK',
        ]

        formatted = data.replace('-', '_').upper()
        if formatted in builtin_colors:
            self.text = f'ui::COLOR_{formatted}'
        elif re.match(r'#[0-9A-F]+', formatted):
            c = formatted[1:]
            if len(c) == 3:
                # 4-bit color resolution
                # e.g. f08 = fully red, none green, half blue
                r = int(c[0], 16) << 1
                g = int(c[1], 16) << 2
                b = int(c[2], 16) << 1

                color = (r << 11) + (g << 5) + b
                self.text = hex(color)
            elif len(c) == 4:
                # rgb565 color format (no conversion needed)
                self.text = f'0x{c}'
            elif len(c) == 6:
                # normal hex colors, decreased to rgb565
                r = int(c[0:2], 16)
                g = int(c[2:4], 16)
                b = int(c[4:6], 16)

                self.text = hex(color565(r, g, b))
            else:
                warn(
                    f'RGB colors must have 3, 4, or 6 chracters, but found `{data}`. Using BLACK.')
                self.text = 'ui::COLOR_BLACK'
        else:
            warn(f'Unknown color value `{data}`. Using BLACK.')
            self.text = 'ui::COLOR_BLACK'

        self.icl = ['<ui/core/color.hpp>']
