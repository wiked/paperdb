#!/bin/bash
if [ -e bin/paperbd ]
then
	rm bin/paperdb
fi
gcc -o bin/paperdb main.c inc/*.c
