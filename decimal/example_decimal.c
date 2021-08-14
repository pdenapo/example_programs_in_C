
#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif

#include <stdio.h>

int main()
{
    _Decimal64 x = 0.10dd;
    printf("%Df\n", x);
    return 0;
}
