#!/usr/bin/env python3

from argparse import ArgumentParser
import xml.etree.ElementTree as xml
from sys import stderr
import xmltree

parser = ArgumentParser(
    prog='xml_to_ui',
    description='Convert an XML file into the C++ code for a GigaWidget UI generator function.',
)
parser.add_argument('filename', help='The input XML file.')
parser.add_argument('func_name', help='The name of the output function.')
args = parser.parse_args()

try:
    tree = xml.parse(args.filename)
except xml.ParseError as e:
    print(f'ERROR: {e}', file=stderr)
    print(f'Failed to parse `{args.filename}` as XML.', file=stderr)
    exit(1)

widget = xmltree.construct(tree.getroot())

print(widget.function(func_name=args.func_name))
