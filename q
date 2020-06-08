#!/bin/bash
clear

PORT=`./detectdevice.sh "$1"`
if [ ! -z ${PORT} ]; then
	miniterm.py ${PORT} 38400 -e --exit-char 3
fi
