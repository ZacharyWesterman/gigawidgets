from typing import Optional

from . import Widget, register
from ..datatypes import (
    Pair,
    Size,
    Position,
    HorizontalAlignment,
    VerticalAlignment,
    VerticalOrdering,
)


@register
class Column(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Pair(HorizontalAlignment, VerticalAlignment)] = Pair(
        HorizontalAlignment, VerticalAlignment
    )("left top")

    size: Pair(Size)
    order: Optional[VerticalOrdering]
    height: Optional[Size]

    def __str__(self) -> str:
        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Column({self.size}, {self.pos}, {self.align});',
            *(f'{self.var}->push({i.var});' for i in self.children),
        ]

        if self.order:
            text += [f'{self.var}->setChildAlign({self.order});']

        if self.height:
            text += [f'{self.var}->setMinHeight({self.height});']

        return '\n'.join(text)
