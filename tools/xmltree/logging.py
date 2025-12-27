from sys import stderr


def red(text: str) -> str:
    return f'\033[91m{text}\033[0m'


def yellow(text: str) -> str:
    return f'\033[93m{text}\033[0m'


def warn(msg: str) -> None:
    print(f'{yellow("WARNING")}: {msg}', file=stderr)


def error(msg: str) -> None:
    print(f'{red("ERROR")}: {msg}', file=stderr)
