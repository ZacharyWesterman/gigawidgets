from ..logging import error
from . import Datatype


class ImageSource(Datatype):
    def __init__(self, data: str):
        builtin_icons = [
            'skrunk',
            'firefox',
        ]

        if data in builtin_icons:
            self.icl = [f'<ui/icons/{data}.hpp>']
            self.text = f'ui::icon::{data}'
        else:
            error(f'Unknown image source `{data}`')
            exit(1)
