from .options import Options


class HorizontalOrdering(Options):
    options = ['LEFT', 'RIGHT', 'LEFT-TO-RIGHT', 'RIGHT-TO-LEFT']

    def format_option(self, data: str) -> str:
        return data.upper()

    def __str__(self) -> str:
        return f'ui::ALIGN_{self.text.split("-")[0]}'
