from pathlib import Path
from xml.etree.ElementTree import Element
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
    def __init__(self, xml: Element):
        self.uid = uid()
        self.var = f'_{self.uid}'
        self.text = xml.text

        attrs = self.__class__.__annotations__

        # Warn about attributes that do not apply to this widget
        for key in xml.attrib.keys():
            if key == 'child_count' or key not in attrs:
                warn(f'Widget `{xml.tag}` has no such attribute `{key}`')

        errored = False

        # Error if found a required attribute that does not have a value
        for key, value in attrs.items():
            if key == 'child_count':
                continue

            if key not in xml.attrib.keys():
                # Attribute is not specified in the XML

                if value != Optional[value]:
                    error(
                        f'Widget `{xml.tag}` missing required attribute `{key}`')
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
                self.__setattr__(key, obj(xml.attrib.get(key)))

        child_ct = 0
        self.children = []
        for child in xml:
            self.children += [construct(child)]
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

    def function(self, func_name: str, set_root: bool = False) -> str:
        text = f'\n{self}'
        if set_root:
            text += f'\nui::setRoot({self.var})'
        text += f'\nreturn {self.var};'
        text = text.replace('\n', '\n  ')
        text = f'ui::Widget* {func_name}() {{{text}\n}}'

        icl = '\n'.join(
            ['#include "src/ui.hpp"'] +
            [
                f'#include {i}' for i in self.includes()
            ]
        )

        return f'{icl}\n\n{text}'

    def includes(self) -> list[str]:
        if hasattr(self, 'children'):
            icl = []
            for child in self.children:
                icl += child.includes()

            return list(set(icl))

        return []


def construct(xml: Element) -> Widget:
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

    return typedef(xml)


# Dynamically import all classes from files in the `widgets` directory
for i in [
    i.name[:-3]
    for i in Path(__file__).parent.iterdir()
    if i.name != '__init__.py' and not i.is_dir()
]:
    __import__(f'xmltree.widgets.{i}')
