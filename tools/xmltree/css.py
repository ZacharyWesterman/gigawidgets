import tinycss2
from tinycss2.parser import QualifiedRule
from .logging import warn
from typing import Generator


def get_rules(files: list[str]) -> Generator[QualifiedRule, None, None]:
    for filename in files:
        try:
            with open(filename, 'r', encoding='utf8') as fp:
                text = fp.read()
        except FileNotFoundError:
            warn(f'Unable to read file `{filename}`.')
            continue

        if text.strip() == '':
            continue

        yield from tinycss2.parse_rule_list(text, skip_whitespace=True)


def get_rule_selector(rule: QualifiedRule) -> str:
    return ''.join([
        i.serialize() for i in rule.prelude
    ]).strip()


def get_attrs(rule: QualifiedRule) -> Generator[tuple[str, str], None, None]:
    key = ''
    value = ''
    get_value = False

    for token in rule.content:
        ser = token.serialize()

        if ser == ':':
            get_value = True
            continue

        if ser == ';':
            if key.strip() != '':
                yield key.strip(), value.strip()
            key = ''
            value = ''
            get_value = False
            continue

        if get_value:
            value += ser
        else:
            key += ser

    if key.strip() != '':
        yield key.strip(), value.strip()


def parse_css(files: list[str]) -> dict[str, dict[str, str]]:
    data = {}

    for rule in get_rules(files):
        selector = get_rule_selector(rule)
        attrs = get_attrs(rule)

        if selector not in data:
            data[selector] = {}

        data[selector] |= attrs

    return data
