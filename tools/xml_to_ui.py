#!/usr/bin/env python3

from argparse import ArgumentParser
import lxml.etree
from sys import stderr
import xmltree
from xmltree.logging import warn

parser = ArgumentParser(
    prog='xml_to_ui',
    description='Convert an XML file into the C++ code for a GigaWidget UI generator function.',
)
parser.add_argument('filename', help='The input XML file.')
parser.add_argument(
    '--function', '-f', type=str, action='store', required=True,
    help='The name of the output function.'
)
parser.add_argument(
    '--style', '-s', type=str, action='append',
    default=[],
    help='One or more CSS files for default styling.'
)
args = parser.parse_args()

try:
    root = lxml.etree.parse(args.filename).getroot()
except Exception as e:
    print(f'ERROR: {e}', file=stderr)
    print(f'Failed to parse `{args.filename}` as XML.', file=stderr)
    exit(1)

css = xmltree.parse_css(args.style)
selectors = xmltree.apply_styles(root, css)
widget = xmltree.construct(root, selectors)

print(widget.function(func_name=args.function))
