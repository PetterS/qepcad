/*======================================================================
                      M <- LCONC(L)

List concatenation.

Inputs
  L  : a list of lists
       L = ( L1, ... , Ln ) , n>=0.
Outputs
  M  : the list obtained by concatenating L1,...,Ln.
       The lists L1,...,Ln are modified.
======================================================================*/
#include "saclib.h"

Word LCONC(L)
       Word L;
{
       Word L1,L2,Lp,Lp1,M;
       /* hide algorithm */

Step1: /* If L is empty. */
       if (L == NIL)
         {
         M = NIL;
         goto Return;
         }

Step2: /* General case. */
       Lp = L;
       do
         ADV(Lp,&M,&Lp);
       while (!(M != NIL || Lp == NIL));
       L1 = M;
       while (Lp != NIL)
         {
         ADV(Lp,&L2,&Lp);
         if (L2 != NIL)
           {
           Lp1 = LASTCELL(L1);
           SRED(Lp1,L2);
           L1 = L2;
           }
         }

Return: /* Prepare for return. */
       return(M);
}
