#!/bin/sh

cd ..

find . -iname *.pro -type f -exec lupdate {} \;
