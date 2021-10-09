
SOURCES= ../linenoise/linenoise.c linenoise-minimal.c
CFLAGS= -I ../linenoise -I../duktape
CLIBS= -lm

SOURCES= duktape-console.c ../duktape/duktape.c ../duktape/duk_print_alert.c ../linenoise/linenoise.c 

duktape-console:  duktape-console.c
	$(CC) $(CFLAGS) $(SOURCES) -o duktape-console $(CLIBS)


clean:	
		rm -f duktape-console


