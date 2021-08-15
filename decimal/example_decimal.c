
#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif

#include <stdio.h>

int main()
{
    _Decimal64 x = 0.10dd;
    _Decimal64 y = 0.20dd;
    _Decimal64 z = x+y;    
    printf("%Df\n", z);
    return 0;
}
