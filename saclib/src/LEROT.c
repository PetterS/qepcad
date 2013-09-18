/*======================================================================
                      M <- LEROT(L,i,j)

List element rotation.

Inputs
  L    : a list ( a1,...,an ) of objects, n > 0.
  i,j  : integers, 1 <= i <= j <= n.

Outputs
  M  : the list obtained from L by rotating the elements ai,...aj.
       M = ( a1,...,a{i-1},aj,ai,...,a{j-1},a{j+1},...an )
       The list L is modified .
       ( If i=j then M=L ).
======================================================================*/
#include "saclib.h"

Word LEROT(L,i,j)
       Word L,i,j;
{
       Word Lp,Lpp,M,a,b,k;
       /* hide algorithm */

Step1: /* i=j. */
       M = L;
       if (i == j)
         goto Return;

Step2: /* i < j. */
       Lp = L;
       for (k = 1; k <= i - 1; k++)
         Lp = RED(Lp);
       ADV(Lp,&a,&Lpp);
       for (k = i; k <= j - 1; k++)
         {
         b = FIRST(Lpp);
         SFIRST(Lpp,a);
         a = b;
         Lpp = RED(Lpp);
         }
       SFIRST(Lp,a);

Return: /* Prepare for return. */
       return(M);
}
