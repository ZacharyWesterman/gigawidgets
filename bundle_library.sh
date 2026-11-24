#!/usr/bin/env bash
set -e

rm -rf .bundle GigaWidgets.zip
mkdir .bundle/GigaWidgets -p

sed "s/{VERSION}/$(./get_version.sh)/g" config/library.properties > .bundle/GigaWidgets/library.properties
rsync -a src .bundle/GigaWidgets/
mkdir .bundle/GigaWidgets/examples
cp examples/*.ino .bundle/GigaWidgets/examples/

cd .bundle
zip ../GigaWidgets.zip GigaWidgets -r

echo
echo "Arduino library built: GigaWidgets.zip"
