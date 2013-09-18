/*======================================================================
                      Lp <- LPERM(L,P)

List permute.

Inputs
  L : a list (a1,...,an).
  P : a list (p1,...,pn) of integers in the range 1,...,n.

Outputs
  Lp : the list (a_{p1},...,a_{pn}).
======================================================================*/
#include "saclib.h"

Word LPERM(L,P)
       Word L,P;
{
       Word Lp,Pp,a,p;
       /* hide Pp,a,p; */

Step1: /* Compute. */
       Lp = NIL;
       Pp = P;
       while (Pp != NIL)
         {
         ADV(Pp,&p,&Pp);
         a = LELTI(L,p);
         Lp = COMP(a,Lp);
         }
       Lp = INV(Lp);

Return: /* Prepare for return. */
       return(Lp);
}
