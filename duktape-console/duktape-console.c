// Ducktape Console- version using GNU-Readline

#include <stdio.h>
#include "duktape.h"
#include "duk_print_alert.h"
#include "readline.h"

int main(int argc, char *argv[]) {
  duk_context *ctx = duk_create_heap_default();
  duk_print_alert_init(ctx, 0 /*flags*/);
  printf("Duktape console\n");
  while (1)
  {
    char* line = readline (">");
	  if (!line)
     	break; 	
   	int ret = duk_peval_string(ctx, line);

        if (ret != 0) {
            printf("Error: %s \n ",duk_to_string(ctx, -1));
        }
        else {
            if (!duk_is_undefined(ctx, -1))
                printf("%s \n",duk_to_string(ctx, -1));
        }
        
        duk_pop(ctx);
    
  }
  duk_destroy_heap(ctx);
  return 0;
}