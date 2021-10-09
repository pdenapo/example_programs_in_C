CC=gcc 
SOURCES= ../linenoise/linenoise.c linenoise-minimal.c
CFLAGS= -I ../linenoise

linenoise-minimal:  $(SOURCES)
				$(CC) $(CFLAGS) $(SOURCES) -o linenoise-minimal $(CLIBS)

clean:	
		rm -f linenoise-minimal


