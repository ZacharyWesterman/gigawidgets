from typing import Optional
import re

from . import Widget, register
from ..datatypes import (
    Color,
    Font,
    Pair,
    Position,
    Alignment,
    Padding,
)
from ..logging import warn


@register
class Text(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Alignment] = Alignment("left top")
    padding: Optional[Padding] = Padding('0')

    font: Optional[Font]
    scale: Optional[int]
    color: Optional[Color] = Color('white')
    child_count = 0

    def __str__(self) -> str:
        escapes = [
            ('\\', '\\\\'),
            ('\n', '\\n'),
            ('\r', '\\r'),
            ('\t', '\\t'),
            ('\"', '\\"'),
        ]

        text = f'{self.text}'.strip()
        text = re.sub(r'\n[ \t]+', '\n', text)

        for esc in escapes:
            text = text.replace(esc[0], esc[1])

        if self.font and self.scale:
            warn(
                '`text` widget has both `scale` and `font` attributes; scale attribute ignored.'
            )

        args = [
            f'"{text}"',
            f'&{self.font}' if self.font else (
                self.scale if self.scale else 1),
            self.color,
            self.pos,
            self.align,
            self.padding,
        ]
        args = [str(i) for i in args]

        return f'auto {self.var} = new ui::Text({", ".join(args)});'

    def includes(self) -> list[str]:
        return self.font.includes() if self.font else []
