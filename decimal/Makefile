CC= gcc
CFLAGS= -std=gnu99 -g -Wl,--no-as-needed -ldfp 
SOURCES= example_decimal.c

example_decimal:  $(SOURCES)
	     $(CC) $(SOURCES) -ldfp -o example_decimal $(CFLAGS) 

clean:	
		rm -f example_decimal


