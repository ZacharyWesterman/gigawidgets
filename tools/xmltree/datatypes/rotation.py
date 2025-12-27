from .options import Options


class Rotation(Options):
    options = ['0', '90', '180', '270']

    def __str__(self) -> str:
        return f'ui::ROT_{self.text}_DEG'
