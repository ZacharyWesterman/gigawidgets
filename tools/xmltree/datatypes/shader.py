import re
from ..logging import error
from . import Datatype


class Shader(Datatype):
    def __init__(self, data: str):
        builtin_shaders = {
            'grayscale': '',
            'halfGrayscaleV': '',
            'negative': '',
            'glow': 'animated/',
            'startupRainbow': 'animated/',
        }

        name_camel = re.sub(r'[-_]\w', lambda s: s[0][1].upper(), data)
        name_snake = re.sub(
            r'[a-z][A-Z]', lambda s: f'{s[0][0]}_{s[0][1].lower()}', name_camel
        )

        if name_camel in builtin_shaders:
            self.text = f'ui::shader::{name_camel}'
            self.icl = [
                f'<ui/shaders/{builtin_shaders[name_camel]}{name_snake}.hpp>'
            ]
        else:
            error(f'Unknown shader `{data}`')
            exit(1)
