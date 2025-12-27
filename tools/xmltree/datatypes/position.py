import re
from ..logging import warn
from . import Datatype


class Position(Datatype):
    def __init__(self, data: str):
        if not re.match(r'^(\.\d+|\d+(\.\d*)?)$', data):
            warn(f'Non-numeric position "{data}" found, zero used.')
            self.text = '0'
            return

        value = float(data)
        if value > 1.0 or value < 0.0:
            warn(
                'Position outside of bounds of parent. Expected range is from 0.0 to 1.0.'
            )

        self.text = str(value)
