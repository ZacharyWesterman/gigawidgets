from pathlib import Path
import re


class Datatype:
    def __init__(self, data: str):
        raise NotImplementedError(
            f'Constructor not implemented for `{self.__class__.__name__}`')

    def __str__(self) -> str:
        return getattr(self, 'text')

    def includes(self) -> list[str]:
        return getattr(self, 'icl', [])


# pylint: disable=wrong-import-order
# pylint: disable=wrong-import-position

from .color import Color  # nopep8
from .font import Font  # nopep8
from .horizontal_alignment import HorizontalAlignment  # nopep8
from .image_source import ImageSource  # nopep8
from .options import Options  # nopep8
from .pair import Pair  # nopep8
from .position import Position  # nopep8
from .shader import Shader  # nopep8
from .vertical_alignment import VerticalAlignment  # nopep8
from .size import Size  # nopep8
from .alignment import Alignment  # nopep8
from .vertical_ordering import VerticalOrdering  # nopep8
from .horizontal_ordering import HorizontalOrdering  # nopep8

# pylint: enable=wrong-import-position
# pylint: enable=wrong-import-order
