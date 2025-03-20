#!/bin/sh -v
gcc -o prueba  prueba.c  $(pkgconf libxls --libs --cflags)
