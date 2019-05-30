#!/usr/bin/env bash
FILE=sig_test
if [ ! -f "$FILE" ]; then
	echo "will create 100Mb $FILE "
	dd if=/dev/urandom of=$FILE bs=1 count=6
	echo "done"
else
	echo "test file exists"
fi
