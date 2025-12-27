from ..logging import warn, error
from . import Datatype


def Pair(left_type: type, right_type: type | None = None) -> type:
    class TypeClass(Datatype):
        def __init__(self, data: str):
            items = data.split(' ')
            if len(items) > 2:
                warn(
                    f'Found {len(items)} values in "{data}", expected 2; extra values ignored.')
            elif len(items) < 2:
                error(
                    f'Expected 2 values in data pair "{data}", but {len(items)} found')
                exit(1)

            val1 = left_type(items[0])
            val2 = right_type(items[1]) if right_type else left_type(items[1])

            self.text = f'{{{val1}, {val2}}}'

    return TypeClass
