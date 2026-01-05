from typing import Optional

from . import Widget, register
from ..datatypes import Time


@register
class Blink(Widget):
    time: Optional[Time]
    child_count = 1

    def __str__(self) -> str:
        args = [
            self.children[0].var,
        ]
        if self.time:
            args += [self.time]
        args = [str(i) for i in args]

        text = [
            *(str(i) for i in self.children),
            f'auto {self.var} = new ui::Blink({",".join(args)});',
        ]

        return '\n'.join(text)
