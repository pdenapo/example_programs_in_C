# see  
#  https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

# create a shared library
gcc -fPIC -shared my_lib.c -o mylib.so

# compile the example program
gcc   test_dlopen.c -o test_dlopen -ldl
