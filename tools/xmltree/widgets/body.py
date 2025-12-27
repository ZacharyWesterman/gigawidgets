from typing import Optional

from . import Widget, register
from ..datatypes import Color, Rotation


@register
class Body(Widget):
    color: Optional[Color] = Color('black')
    rotation: Optional[Rotation]

    child_count = 1

    def includes(self) -> list[str]:
        return self.children[0].includes()

    def __str__(self) -> str:
        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Body({self.children[0].var}, {self.color});'
        ]

        if self.rotation:
            text += [f'ui::setRotation({self.rotation});']

        return '\n'.join(text)
