/* test.c */
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
    duk_eval_string(ctx, line);
  }
  duk_destroy_heap(ctx);
  return 0;
}