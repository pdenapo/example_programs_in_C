CFLAGS=$(shell pkg-config --cflags readline)  
CLIBS =$(shell pkg-config --libs readline) -lm

CFLAGS= -g  $(shell pkg-config --cflags --libs readline) -I../duktape 
CC=gcc -std=c99 
SOURCES= duktape-console.c ../duktape/duktape.c ../duktape/duk_print_alert.c

duktape-console:  duktape-console.c
	$(CC) $(CFLAGS) $(SOURCES) -o duktape-console $(CLIBS)


clean:	
		rm -f duktape-console


