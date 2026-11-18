from ..logging import error
from . import Datatype
from pathlib import Path

_IMG_DEFS = []


class ImageSource(Datatype):
    def __init__(self, data: str):
        if data.startswith('code:'):
            self.text = f'({data[5:]})'
            return

        path = Path(data)
        builtin_path = Path(f'src/ui/icons/{data}.hpp')

        if not path.exists():
            if not builtin_path.exists():
                error(
                    f'Image source `{data}` is not an existing file or builtin image.')
                exit(1)

            self.icl = [f'"{builtin_path}"']
            self.text = f'ui::icon::{data}'
            return

        if not path.is_file():
            error(f'Image source `{data}` is a directory, not an image file.')
            exit(1)

        # Read data to determine what type of file
        filedata = b''
        with open(str(path), 'rb') as fp:
            filedata = fp.read()

        if filedata[:2] == b'BM':
            imagetype = 'Bmp'
        elif filedata[:8] == b'\x89PNG\x0d\x0a\x1a\x0a':
            imagetype = 'Png'
        elif filedata[:2] == b'\xff\xd8' and filedata[-2:] == b'\xff\xd9':
            imagetype = 'Jpeg'
        else:
            error(f'Image file `{data}` is not a JPEG, PNG or BMP image file.')
            exit(1)

        self.icl = [
            f'"src/ui/core/renderable/image_file/{imagetype.lower()}.hpp"'
        ]

        imagebytes = [f'{i}' for i in filedata]

        global _IMG_DEFS
        if imagebytes in _IMG_DEFS:
            image_id = _IMG_DEFS.index(imagebytes)
        else:
            image_id = len(_IMG_DEFS)
            _IMG_DEFS += [imagebytes]
            self.globaldef = [
                f'unsigned char __img_{image_id}_data[] = {{{",".join(imagebytes)}}};',
                f'const ui::{imagetype} __img_{image_id}(__img_{image_id}_data, {len(imagebytes)});',
            ]

        self.text = f'__img_{image_id}'
