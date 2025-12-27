import re
from ..logging import warn
from . import Datatype


class Size(Datatype):
    def __init__(self, data: str):
        if re.match(r'^(\.\d+|\d+(\.\d*)?)(in|cm|mm|px|vw|vh)$', data):
            self.text = f'{data[0:-2]}_{data[-2:]}'
        elif re.match(r'^(\.\d+|\d+(\.\d*)?)$', data):
            self.text = f'{data}_px'
        else:
            warn(f'Unknown size value `{data}`. Defaulting to 0px.')
            self.text = '0'

        self.icl = ['<ui/core/color.hpp>']
