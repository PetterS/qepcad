/*======================================================================
                      n <- ORDER(a)

Order.

Inputs
  a  : object.

Outputs
  n  : integer, the order (depth) of a.
======================================================================*/
#include "saclib.h"

Word ORDER(a)
       Word a;
{
       Word a1,ap,n;
       /* hide a1,n; */

Step1: /* a an atom. */
       n = 0;
       if (a < BETA)
         goto Return;

Step2: /* a a list. */
       ap = a;
       while (ap != NIL)
         {
         ADV(ap,&a1,&ap);
         n = MAX(n,ORDER(a1));
         }
       n = n + 1;

Return: /* Prepare for return. */
       return(n);
}
