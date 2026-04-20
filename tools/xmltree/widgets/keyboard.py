from typing import Optional

from . import Widget, register
from ..datatypes import (
    Color,
    Font,
)
from ..logging import warn


@register
class Keyboard(Widget):
    font: Optional[Font]
    scale: Optional[int]
    color: Optional[Color] = Color('light-gray')
    background_color: Optional[Color] = Color('gray')
    text_color: Optional[Color] = Color('black')
    child_count = 0

    def __str__(self) -> str:
        if self.font and self.scale:
            warn(
                '`keyboard` widget has both `scale` and `font` attributes; scale attribute ignored.'
            )

        args = [
            self.font if self.font else (
                self.scale if self.scale else 1),
            self.text_color,
            self.color,
            self.background_color,
        ]

        text = [
            f'auto {self.var} = new ui::Keyboard({", ".join(str(i) for i in args)});'
        ]
        text += self.shared_settings

        return '\n'.join(text)

    def includes(self) -> list[str]:
        return self.font.includes() if self.font else []
