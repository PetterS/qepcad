/*===========================================================================
                                v <- VAR(L)

Variations.

Inputs
  L : a list (s_1,...,s_t) of signs, where s_i is -1, 0, or 1.

Outputs
  v : in Z.  v is equal to the number of variations in L.
===========================================================================*/
#include "saclib.h"

Word VAR(L)
       Word L;
{
       Word v,Lp,s_1,s_2;

Step1: /* Skip leading zeros. */
       Lp = L;
       v = 0;
       s_1 = 0;
       while (Lp != NIL && s_1 == 0) {
          s_1 = FIRST(Lp);
          Lp = RED(Lp); }

Step2: /* Count variations. */
       while (Lp != NIL) {
          s_2 = FIRST(Lp);
          Lp = RED(Lp);
          if (s_2 == -s_1) {
             v = v + 1;
             s_1 = s_2; } }

Return: /* Return v. */
       return(v);
}

