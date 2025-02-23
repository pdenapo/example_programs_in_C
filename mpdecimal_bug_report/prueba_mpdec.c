#include <mpdecimal.h>

int main()
{
  mpd_context_t ctx;
  mpd_t *a;
    mpd_init(&ctx,128);
  // If I change this line to the crash does not occur
  //mpd_ieee_context(&ctx, 128);
  
  // We create a decimal and store a value in it
  a= mpd_new(&ctx);
  mpd_set_string(a, "?", &ctx);

  // This causes a crash. The documentation says:
  // Set result from s. The context is respected. This means that rounding, overflow etc. can take place. If the string is not 
  // valid, the MPD_Conversion_syntax condition is added to status and result is set to NaN.

  mpd_print(a);

  // in the ieee context prints Nan 
   
  mpd_del(a);
  return 0;
}
