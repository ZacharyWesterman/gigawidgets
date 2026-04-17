from typing import Optional

from . import Widget, register
from ..datatypes import (
    Pair,
    Size,
    Position,
    Alignment,
    VerticalOrdering,
    Padding,
)


@register
class Row(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Alignment] = Alignment("left top")
    padding: Optional[Padding] = Padding('0')

    size: Pair(Size)
    order: Optional[VerticalOrdering]
    width: Optional[Size]

    def __str__(self) -> str:
        args = [
            self.size,
            self.pos,
            self.align,
            self.padding,
        ]
        args = [str(i) for i in args]

        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Row({",".join(args)});',
            *(f'{self.var}->push({i.var});' for i in self.children),
        ]

        if self.order:
            text += [f'{self.var}->setChildAlign({self.order});']

        if self.width:
            text += [f'{self.var}->setMinWidth({self.width});']

        text += self.event_handlers

        return '\n'.join(text)
