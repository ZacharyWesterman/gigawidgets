from .horizontal_alignment import HorizontalAlignment
from .vertical_alignment import VerticalAlignment
from .pair import Pair


class Alignment(Pair(HorizontalAlignment, VerticalAlignment)):
    ...
