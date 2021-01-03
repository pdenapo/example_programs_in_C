#include "arb.h"

int main()
{
    arb_t x, y;
    arb_init(x); arb_init(y);
    arb_set_ui(x, 3);       /* x = 3 */
    arb_const_pi(y, 128);   /* y = pi, to 128 bits */
    arb_sub(y, y, x, 53);   /* y = y - x, to 53 bits */
    arb_printn(y, 20, 0); putchar('\n');
    arb_clear(x); arb_clear(y);
    return 0;
}