from typing import Optional

from . import Widget, register
from ..datatypes import (
    Color,
    Font,
    Pair,
    Size,
    Position,
    Alignment,
    Padding,
)
from ..logging import warn


@register
class Input(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Alignment] = Alignment("left top")
    padding: Optional[Padding] = Padding('0')
    size: Optional[Pair(Size)] = Pair(Size)('100px 0')
    radius: Optional[Size] = Size('0')

    font: Optional[Font]
    scale: Optional[int]
    color: Optional[Color] = Color('white')
    text_color: Optional[Color] = Color('black')
    value: Optional[str] = ''

    child_count = 0

    def __str__(self) -> str:
        if self.font and self.scale:
            warn(
                '`input` widget has both `scale` and `font` attributes; scale attribute ignored.'
            )

        args = [
            f'&{self.font}' if self.font else (
                self.scale if self.scale else 1),
            self.text_color,
            self.color,
            self.size,
            self.radius,
            self.pos,
            self.align,
            self.padding,
        ]
        args = [str(i) for i in args]

        text = [f'auto {self.var} = new ui::Input({", ".join(args)});']

        if self.value != '':
            text += [f'{self.var}->setText("{self.value}");']

        return '\n'.join(text)

    def includes(self) -> list[str]:
        return self.font.includes() if self.font else []
