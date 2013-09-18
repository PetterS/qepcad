/*======================================================================
                      Pp <- RMMPF(P,k)

Remove Marked Projection Factors.

\Input
  \parm{P} is the projection factor list.
  \parm{k} is the current level.
  
\Output
  \parm{P'} is obtained from $P$ by permanently removing
            the marked $k$--level projection factors.
\Side
  \parm{P} is modified.
======================================================================*/
#include "qepcad.h"

Word RMMPF(Word P, Word k)
{
       Word P_k,P_k_j,Pp,Pp_k;

Step1: /* Remove. */
       P_k = LELTI(P,k);
       Pp_k = NIL;
       while (P_k != NIL)
         {
         ADV(P_k,&P_k_j,&P_k);
         if (LELTI(P_k_j,PO_STATUS) == PO_KEEP) Pp_k = COMP(P_k_j,Pp_k);
         }
       Pp_k = INV(Pp_k);
       SLELTI(P,k,Pp_k);
       Pp = P;

Return: /* Prepare for return. */
       return(Pp);
}
