CFLAGS=$(shell pkg-config --cflags readline)  
CLIBS =$(shell pkg-config --libs readline) 

using_readline:	using_readline.c
	          $(CC) $(CFLAGS) using_readline.c -o using_readline $(CLIBS)

clean:	
		rm -f using_readline
		


