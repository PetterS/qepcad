/*======================================================================
                      B <- LEXNEX(A)

Lexicographically next.

Inputs
  A : a non-null list (a1,...,am) such that ai is a non-null reductum
      of a_{i+1} for each 1 <= i < m.

Outputs
  B : the lexicographically next such list of the same length,
      if one exists, and is () otherwise.
======================================================================*/
#include "saclib.h"

Word LEXNEX(A)
       Word A;
{
       Word B,a,b,c,i,j;
       /* hide a,b,c,i,j; */

Step1: /* Step first element. */
       ADV(A,&b,&B);
       c = RED(b);
       if (c != NIL)
         {
         B = COMP(c,B);
         goto Return;
         }
       i = 1;

Step2: /* Find an element to step. */
       while (B != NIL)
         {
         ADV(B,&a,&B);
         i = i + 1;
         c = RED(a);
         if (c != b)
           goto Step3;
         b = a;
         }
       goto Return;

Step3: /* Found one. */
       for (j = 1; j <= i; j++)
         {
         B = COMP(c,B);
         c = RED(c);
         }

Return: /* Prepare for return. */
       return(B);
}
