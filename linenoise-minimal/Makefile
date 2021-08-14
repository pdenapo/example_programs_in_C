CC=gcc -std=c99 

linenoise-minimal:  linenoise-minimal.c
	          $(CC) -L${PWD} -Wl,-rpath=${PWD}  linenoise-minimal.c -o linenoise-minimal   -llinenoise

clean:	
		rm -f linenoise-minimal


