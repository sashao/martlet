#!/bin/sh

find ../ -iname *.pro -type f -exec lupdate {} \;
