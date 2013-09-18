/*======================================================================
                      Pp <- PERMCY(P)

Permutation, cyclic.

Inputs
  P  : a list (P1,P2,...,Pn), n >= 0.

Outputs  
  Pp : (P2, P3,..., Pn, P1).
======================================================================*/
#include "saclib.h"

Word PERMCY(P)
       Word P;
{
       Word Pp,Ps,p,p1;
       /* hide Ps,p,p1; */

Step1: /* Compute. */
       Pp = NIL;
       if (P == NIL)
         goto Return;
       ADV(P,&p1,&Ps);
       while (Ps != NIL)
         {
         ADV(Ps,&p,&Ps);
         Pp = COMP(p,Pp);
         }
       Pp = COMP(p1,Pp);
       Pp = INV(Pp);

Return: /* Prepare for return. */
       return(Pp);
}
