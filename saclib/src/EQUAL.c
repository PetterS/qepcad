/*======================================================================
                      t <- EQUAL(a,b)

Equal.

Inputs
  a, b  : objects.

Outputs
  t  :  t = 1 if a and b are equal,
        t = 0 otherwise.
======================================================================*/
#include "saclib.h"

Word EQUAL(a,b)
       Word a,b;
{
       Word a1,ap,b1,bp,t;
       /* hide t; */

Step1: /* Identical atoms or list representations. */
       t = 0;
       if (a == b)
         {
         t = 1;
         goto Return;
         }

Step2: /* a or b is an atom. */
       if (a < BETA || b < BETA)
         goto Return;

Step3: /* Recursion. */
       ap = a;
       bp = b;
       while (ap != NIL && bp != NIL)
         {
         ADV(ap,&a1,&ap);
         ADV(bp,&b1,&bp);
         if (EQUAL(a1,b1) == 0)
           goto Return;
         if (ap == bp)
           {
           t = 1;
           goto Return;
           }
         }

Return: /* Prepare for return. */
       return(t);
}
