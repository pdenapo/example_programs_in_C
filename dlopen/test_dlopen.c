#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int main(int argc, char** argv)
{
    void *handle;
    int (*square)(int x);

    handle = dlopen("./mylib.so", RTLD_LAZY);
 
    if (!handle) {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    *(void**)(&square) = dlsym(handle, "square");
    if (!square) {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    printf("The squre of 2 is %d \n",square(2));
    dlclose(handle);

    return EXIT_SUCCESS;
}