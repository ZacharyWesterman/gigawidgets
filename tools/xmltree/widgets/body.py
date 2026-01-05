from typing import Optional

from . import Widget, register
from ..datatypes import Color, Rotation, Padding


@register
class Body(Widget):
    color: Optional[Color] = Color('black')
    rotation: Optional[Rotation]
    padding: Optional[Padding] = Padding('0')

    child_count = 1

    def includes(self) -> list[str]:
        return self.children[0].includes()

    def __str__(self) -> str:
        args = [
            self.children[0].var,
            self.color,
            self.padding,
        ]
        args = [str(i) for i in args]

        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Body({",".join(args)});'
        ]

        if self.rotation:
            text += [f'ui::setRotation({self.rotation});']

        return '\n'.join(text)
