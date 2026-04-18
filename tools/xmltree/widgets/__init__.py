from pathlib import Path
from cssselect import GenericTranslator, SelectorError
from typing import Optional
import re

from ..logging import warn, error

_class_list = {}
_uid_ct = 0


def register(class_def: type) -> type:
    _class_list[class_def.__name__] = class_def
    return class_def


def uid():
    # pylint: disable=global-statement
    global _uid_ct
    # pylint: enable=global-statement
    _uid_ct += 1
    return _uid_ct


class Widget:
    def __init__(self, xml, selectors: list):
        self.uid: int = uid()
        self.var: str = f'_{self.uid}'
        self.text: str = xml.text if xml.text else ''
        self.classes: list[str] = []

        attrs = self.__class__.__annotations__

        # Get any CSS styles that apply to this widget.
        styles: dict[str, str] | None = None
        for ix, sel in enumerate(selectors):
            if sel[0] != xml:
                continue
            styles = sel[1]
            selectors.pop(ix)
            break

        # Apply CSS styles to this widget.
        # If not applicable, silently ignore.
        if styles:
            for key, value in styles.items():
                if key in ['class', 'child_count', 'children']:
                    continue

                key = key.replace('-', '_')
                if key not in attrs and not hasattr(self.__class__, key):
                    continue
                xml.attrib[key] = value

        # Allow these attributes to be used on every widget
        always_defined = (
            ('class', Optional[list[str]], []),
            ('onclick', Optional[str], None),
            ('onblur', Optional[str], None),
            ('onpress', Optional[str], None),
            ('onrelease', Optional[str], None),
            ('onhold', Optional[str], None),
            ('id', Optional[str], None),
        )
        for i in always_defined:
            attrs[i[0]] = i[1]
            setattr(self.__class__, i[0], i[2])

        # Warn about attributes that do not apply to this widget
        for key in xml.attrib.keys():
            if key == 'child_count' or key.replace('-', '_') not in attrs:
                warn(f'Widget `{xml.tag}` has no such attribute `{key}`')

        errored = False

        # Error if found a required attribute that does not have a value
        for key, value in attrs.items():
            if key == 'child_count':
                continue

            attr_key = key.replace('_', '-')

            if attr_key not in xml.attrib.keys():
                # Attribute is not specified in the XML

                if value != Optional[value]:
                    error(
                        f'Widget `{xml.tag}` missing required attribute `{key.replace("_", "-")}`')
                    errored = True
                elif hasattr(self.__class__, key):
                    # Optional attribute with a default value.
                    self.__setattr__(key, getattr(self.__class__, key))
                else:
                    # Assign None as the default value for optional attribute.
                    self.__setattr__(key, None)
            else:
                # Construct and assign the value for this attribute
                obj = value.__args__[0] if value == Optional[value] else value
                val = xml.attrib.get(attr_key)

                if key == 'class':
                    key = 'classes'
                    val = [] if val is None else val.split(' ')

                self.__setattr__(key, obj(val))

        child_ct = 0
        self.children = []
        for child in xml:
            # Skip comments
            if type(child.tag) is not str:
                continue
            self.children += [construct(child, selectors)]
            child_ct += 1

        # Error if the number of children does not match what the node requires.
        # If 'children' attribute isn't specified, then can have any number of children.
        if hasattr(self.__class__, 'child_count'):
            exp_child_ct = getattr(self.__class__, 'child_count')
            if child_ct != exp_child_ct:
                error(
                    f'Widget `{xml.tag}` requires exactly ' +
                    f'{exp_child_ct} child{"" if exp_child_ct == 1 else "ren"} ' +
                    f'but was given {child_ct}'
                )
                errored = True

        if errored:
            exit(1)

    def __str__(self) -> str:
        raise NotImplementedError(
            f'`__str__()` not implemented for `{self.__class__.__name__}`')

    def function(self, func_name: str, include: list[str], set_root: bool = False) -> str:
        text = '\n'.join(
            ['#include "src/ui.hpp"'] +
            [
                f'#include {i}' for i in self.includes()
            ]
        ) + '\n'

        for i in include:
            if not Path(i).is_file():
                warn(
                    f'Unable to include "{i}": file does not exist or is not readable.'
                )
                continue
            with open(i, 'r') as fp:
                text += f'\n{fp.read()}'

        body = f'\n{self}'
        if set_root:
            body += f'\nui::setRoot({self.var})'
        body += f'\nreturn {self.var};'
        body = body.replace('\n', '\n  ')
        text += f'\nui::Widget* {func_name}() {{{body}\n}}'

        return text

    def includes(self) -> list[str]:
        if hasattr(self, 'children'):
            icl = []
            for child in self.children:
                icl += child.includes()

            return list(set(icl))

        return []

    @property
    def shared_settings(self) -> list[str]:
        lines = []
        for i in ['onclick', 'onblur', 'onpress', 'onrelease', 'onhold']:
            if getattr(self, i):
                lines += [f'{self.var}->{i}({getattr(self, i)});']

        if getattr(self, 'id'):
            lines += [f'{self.var}->id = "{getattr(self, "id")}"_id;']

        return lines


def construct(xml, selectors: list) -> Widget:
    # Convert `kebab-case` or `snake_case` tag names to `PascalCase`
    # to align with class naming convention.
    class_name = (
        xml.tag[0].upper() +
        re.sub(r'[_-][a-zA-Z]', lambda s: s[0][1].upper(), xml.tag[1:])
    )

    typedef = _class_list.get(class_name)

    if typedef is None or not isinstance(typedef, type):
        error(
            f'Found tag `{xml.tag}`, but ' +
            f'no implementation found for a corresponding `{class_name}` widget.'
        )
        exit(1)

    return typedef(xml, selectors)


def apply_styles(tree,  css: dict[str, dict[str, str]]) -> list:
    result = []
    for selector, attrs in css.items():
        try:
            xpath = GenericTranslator().css_to_xpath(selector)
        except SelectorError as e:
            warn(f'Invalid CSS selector `{selector}`: {e}')
            continue

        for node in tree.xpath(xpath):
            result += [(node, attrs)]

    return result


# Dynamically import all classes from files in the `widgets` directory
for i in [
    i.name[:-3]
    for i in Path(__file__).parent.iterdir()
    if i.name != '__init__.py' and not i.is_dir()
]:
    try:
        __import__(f'xmltree.widgets.{i}')
    except ModuleNotFoundError:
        __import__(f'tools.xmltree.widgets.{i}')
