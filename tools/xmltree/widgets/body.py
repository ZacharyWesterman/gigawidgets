from typing import Optional

from . import Widget, register
from ..datatypes import Color


@register
class Body(Widget):
    color: Optional[Color] = Color('black')
    child_count = 1

    def includes(self) -> list[str]:
        return self.children[0].includes()

    def __str__(self) -> str:
        return '\n'.join(
            [
                *(str(i) for i in self.children),
                f'auto {self.var} = new ui::Body({self.children[0].var}, {self.color});'
            ]
        )
