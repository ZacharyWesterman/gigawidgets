from ..logging import warn
from . import Datatype
from .size import Size


class Padding(Datatype):
    def __init__(self, data: str):
        pad = [Size(i).text for i in data.split(' ')]

        if len(pad) not in [1, 2, 4]:
            warn(f'Padding expected 1, 2 or 4 values, but found {len(pad)}.')

        if len(pad) in [2, 3]:
            self.text = f'{{{pad[0]}, {pad[1]}}}'
            return

        if len(pad) >= 4:
            self.text = '{' + ', '.join([pad[i] for i in range(4)]) + '}'
            return

        self.text = pad[0] if len(pad) > 0 else '0'
