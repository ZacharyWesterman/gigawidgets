from ..logging import error
from . import Datatype


class KeyboardLayout(Datatype):
    def __init__(self, data: str):
        layouts = [
            'qwerty'
        ]

        if data in layouts:
            self.text = f'ui::layout::{data}'
            self.icl = [f'"src/ui/keyboard_layout/{data}.hpp"']
        else:
            error(f'Unknown keyboard layout `{data}`')
            exit(1)
