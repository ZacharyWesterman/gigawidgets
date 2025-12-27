from .options import Options


class HorizontalAlignment(Options):
    options = ['LEFT', 'RIGHT', 'CENTER']

    def format_option(self, data: str) -> str:
        return data.upper()

    def __str__(self) -> str:
        return f'ui::ALIGN_{self.text}'
