from ..logging import error
from . import Datatype


class Options(Datatype):
    def __init__(self, data: str):
        options = getattr(self.__class__, 'options')
        self.text = self.format_option(data)

        if self.text not in options:
            error(
                f'Invalid {self.__class__.__name__} "{data}". Acceptable values are {", ".join(options)}')
            exit(1)

    def format_option(self, data: str) -> str:
        return data
