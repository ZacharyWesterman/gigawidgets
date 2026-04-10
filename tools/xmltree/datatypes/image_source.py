from ..logging import error
from . import Datatype
from pathlib import Path


class ImageSource(Datatype):
    def __init__(self, data: str):
        builtin_icons = [
            'skrunk',
            'firefox',
        ]

        filename = f'src/ui/icons/{data}.hpp'
        if Path(filename).exists():
            self.icl = [f'"{filename}"']
            self.text = f'ui::icon::{data}'
        else:
            error(f'Unknown image source `{data}`')
            exit(1)
