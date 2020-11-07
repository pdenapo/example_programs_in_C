CFLAGS= -g  $(shell pkg-config --cflags --libs readline) -I../duktape -lm
CC=gcc -std=c99 
SOURCES= duktape-console.c ../duktape/duktape.c ../duktape/duk_print_alert.c

duktape-console:  duktape-console.c
			$(CC) $(SOURCES) -o duktape-console $(CFLAGS) 

clean:	
		rm -f duktape-console


