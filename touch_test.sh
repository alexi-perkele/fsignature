#!/usr/bin/env bash
FILE=sig_test
if [ ! -f "$FILE" ]; then
	echo "will create $FILE "
	dd if=/dev/urandom of=$FILE bs=2M count=7
	echo "done"
else
	echo "test file exists"
fi
