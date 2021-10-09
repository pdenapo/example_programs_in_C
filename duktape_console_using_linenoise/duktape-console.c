// Ducktape Console- version using Linenoise

#include <stdio.h>
#include "duktape.h"
#include "duk_print_alert.h"
#include <linenoise.h>

static void push_file_as_string(duk_context *ctx, const char *filename)
{
  FILE *f;
  size_t len;
  char *buffer;

  f = fopen(filename, "rb");
  if (f)
  {
    len = getdelim(&buffer, &len, '\0', f);
    fclose(f);
    // printf("código leído: \n %s \n", buffer);
    duk_push_lstring(ctx, (const char *)buffer, (duk_size_t)len);
  }
  else
  {
    duk_push_undefined(ctx);
  }
}

duk_ret_t run_script(duk_context *ctx, const char *file_name)
{
  push_file_as_string(ctx, file_name);
  if (duk_peval(ctx) != 0)
  {
    /* Use duk_safe_to_string() to convert error into string.  This API
     * call is guaranteed not to throw an error during the coercion.
     */
    printf("Script error: %s\n", duk_safe_to_string(ctx, -1));
  }
  duk_pop(ctx);
  duk_pop(ctx);
  return 1;
}

duk_ret_t load(duk_context *ctx)
{
  const char *file_name = duk_require_string(ctx, 0);
  return run_script(ctx, file_name);
}

// print the message many times, for example:
// print_many(5,"hola")

static duk_ret_t print_many(duk_context *ctx)
{
  int times = duk_require_int(ctx, 0);
  printf("times=%i \n", times);

  const char *msg = duk_require_string(ctx, 1);

  //const char *msg = "hola";

  for (int i = 0; i < times; i++)
    printf("%s \n", msg);
  return 0; // no return value (= undefined)
}

int main(int argc, char *argv[])
{

  linenoiseSetMultiLine(1);

  duk_context *ctx = duk_create_heap_default();
  if (!ctx)
  {
    printf("Failed to created Duktape context.\n");
    exit(1);
  }
  duk_print_alert_init(ctx, 0 /*flags*/);

  // We register some functions in the global object to be used from javascript

  duk_push_c_function(ctx, &load, 1 /*nargs*/);
  duk_put_global_string(ctx, "load");

  duk_push_c_function(ctx, &print_many, 1 /*nargs*/);
  duk_put_global_string(ctx, "print_many");

  printf("Duktape console using linenoise\n");
  while (1)
  {
    char *line = linenoise(">");
    if (!line)
      break;
    linenoiseHistoryAdd(line);
    int ret = duk_peval_string(ctx, line);

    if (ret != 0)
    {
      printf("Error: %s \n ", duk_to_string(ctx, -1));
    }
    else
    {
      if (!duk_is_undefined(ctx, -1))
        printf("%s \n", duk_to_string(ctx, -1));
    }

    duk_pop(ctx);
  }
  duk_destroy_heap(ctx);
  return 0;
}