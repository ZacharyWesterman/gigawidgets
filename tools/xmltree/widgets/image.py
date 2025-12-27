from typing import Optional

from . import Widget, register
from ..datatypes import (
    ImageSource,
    Shader,
    Pair,
    Position,
    HorizontalAlignment,
    VerticalAlignment,
)


@register
class Image(Widget):
    pos: Optional[Pair(Position)] = Pair(Position)("0 0")
    align: Optional[Pair(HorizontalAlignment, VerticalAlignment)] = Pair(
        HorizontalAlignment, VerticalAlignment
    )("left top")

    source: ImageSource
    shader: Optional[Shader]
    child_count = 0

    def includes(self) -> list[str]:
        icl = self.source.includes()
        if self.shader:
            icl += self.shader.includes()

        return icl

    def __str__(self) -> str:
        args = [
            f'&{self.source}',
            self.pos,
            self.align,
        ]

        text = f'auto {self.var} = new ui::Image({", ".join(str(i) for i in args)});'

        if self.shader:
            text += f'\n{self.var}->setShader({self.shader});'

        return text
