// Ducktape Console- version using Linenoise

#include <stdio.h>
#include "duktape.h"
#include "duk_print_alert.h"
#include <linenoise.h>

// Función útil para debug. Estaba en la versión 1 pero la removieron por portabilidad.
static void duk_dump_context_stderr(duk_context *ctx)
{
  duk_push_context_dump(ctx);
  fprintf(stderr, "%s\n", duk_to_string(ctx, -1));
  duk_pop(ctx);
}

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

/* Adder: add argument values. */
static duk_ret_t native_adder(duk_context *ctx)
{
  int i;
  int n = duk_get_top(ctx); /* #args */
  double res = 0.0;

  for (i = 0; i < n; i++)
  {
    res += duk_to_number(ctx, i);
  }

  duk_push_number(ctx, res);
  return 1; /* one return value */
}

// print the message many times, for example:
// print_many(5,"hola")

static duk_ret_t print_many(duk_context *ctx)
{
  // Para debug podemos usar
  // duk_dump_context_stderr(ctx);
  // El índice indica el lugar y los distintos tipos de require qué tipo
  // de paràmetro necesita esta función
  int times = duk_require_int(ctx, 0);
  const char *msg = duk_require_string(ctx, 1);

  //const char *msg = "hola";

  for (int i = 0; i < times; i++)
    printf("%s \n", msg);
  return 0; // no return value (= undefined)
}

void completion(const char *buf, linenoiseCompletions *lc)
{
  if (buf[0] == 'a')
  {
    linenoiseAddCompletion(lc, "alert");
    linenoiseAddCompletion(lc, "adder");
  }
  else if (buf[0] == 'l')
  {
    linenoiseAddCompletion(lc, "load");
  }
  else if (buf[0] == 'p')
  {
    linenoiseAddCompletion(lc, "print");
    linenoiseAddCompletion(lc, "print_many");
  }
}

int main(int argc, char *argv[])
{

  linenoiseSetMultiLine(1);
  /* Set the completion callback. This will be called every time the
     * user uses the <tab> key. */
  linenoiseSetCompletionCallback(&completion);

  /* Load history from file. The history file is just a plain text file
     * where entries are separated by newlines. */
  linenoiseHistoryLoad("history.txt"); /* Load the history at startup */

  duk_context *ctx = duk_create_heap_default();
  if (!ctx)
  {
    printf("Failed to created Duktape context.\n");
    exit(1);
  }
  duk_print_alert_init(ctx, 0 /*flags*/);

  // We register some functions in the global object to be used from javascript

  // Command to load an script, ej. load("hello.js")
  duk_push_c_function(ctx, &load, 1 /*nargs*/);
  duk_put_global_string(ctx, "load");

  duk_push_c_function(ctx, &print_many, 2 /*nargs*/);
  duk_put_global_string(ctx, "print_many");

  // Example from the ducktape page
  duk_push_c_function(ctx, native_adder, DUK_VARARGS);
  duk_put_global_string(ctx, "adder");

  printf("Duktape console using linenoise\n");
  while (1)
  {
    char *line = linenoise(">");
    if (!line)
      break;
    linenoiseHistoryAdd(line);
    linenoiseHistorySave("history.txt"); /* Save the history on disk. */

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