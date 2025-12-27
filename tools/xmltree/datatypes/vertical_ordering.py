from .options import Options


class VerticalOrdering(Options):
    options = ['TOP', 'BOTTOM', 'TOP-DOWN', 'BOTTOM-UP']

    def format_option(self, data: str) -> str:
        return data.upper()

    def __str__(self) -> str:
        return f'ui::ALIGN_{self.text.split("-")[0]}'
