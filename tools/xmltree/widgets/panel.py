from typing import Optional

from . import Widget, register
from ..datatypes import (
    Pair,
    Size,
    Color,
    Position,
    Alignment,
)


@register
class Panel(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Alignment] = Alignment("left top")

    color: Optional[Color] = Color('black')
    size: Optional[Pair(Size)] = Pair(Size)("0 0")
    radius: Optional[Size] = Size('0')

    child_count = 1

    def __str__(self) -> str:
        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Panel(' +
            f'{self.children[0].var}, {self.color}, {self.size}, ' +
            f'{self.radius}, {self.pos}, {self.align}' +
            ');',
        ]

        return '\n'.join(text)
