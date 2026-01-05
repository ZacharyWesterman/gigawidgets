import re
from ..logging import warn
from . import Datatype

TIME = re.compile(
    r'^(\.\d+|\d+(\.\d*)?)(ms|milli(seconds?)?|s|sec|m(in)?|hr?|hours?|dy?|days?)$'
)


class Time(Datatype):
    def __init__(self, data: str):
        if m := TIME.match(data):
            value = float(m.group(1))
            unit = m.group(0)[len(m.group(1)):][0:3]

            if unit in ['s', 'sec']:
                value *= 1000
            elif unit in ['m', 'min']:
                value *= 1000 * 60
            elif unit in ['h', 'hr', 'hou']:
                value *= 1000 * 60 * 60
            elif unit in ['d', 'dy', 'day']:
                value *= 1000 * 60 * 60 * 24

            self.text = str(int(value))
        elif re.match(r'^(\.\d+|\d+(\.\d*)?)$', data):
            warn(
                f'Time unit not specified for `{data}`. Assuming milliseconds.')
            self.text = data
        else:
            warn(f'Unknown time value `{data}`. Defaulting to 0 milliseconds.')
            self.text = '0'
