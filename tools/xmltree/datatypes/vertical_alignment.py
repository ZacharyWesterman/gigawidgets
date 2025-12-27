from .options import Options


class VerticalAlignment(Options):
    options = ['TOP', 'BOTTOM', 'CENTER']

    def format_option(self, data: str) -> str:
        return data.upper()

    def __str__(self) -> str:
        return f'ui::ALIGN_{self.text}'
