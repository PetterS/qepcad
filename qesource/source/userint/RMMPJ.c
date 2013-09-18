/*======================================================================
                      Jp <- RMMPJ(J,k)

Remove Marked Projection Polynomials.

\Input
  \parm{J}  is the projection polynomial list.
  \parm{k}  is the current level.
  
\Output
  \parm{J'} is obtained from $J$ by permanently removing
            the marked $k$-level projection polynomials.
\Side
  \parm{J} is modified.
======================================================================*/
#include "qepcad.h"

Word RMMPJ(Word J, Word k)
{
       Word J_k,J_k_j,Jp,Jp_k;

Step1: /* Remove. */
       J_k = LELTI(J,k);
       Jp_k = NIL;
       while (J_k != NIL)
         {
         ADV(J_k,&J_k_j,&J_k);
         if (LELTI(J_k_j,PO_STATUS) == PO_KEEP) Jp_k = COMP(J_k_j,Jp_k);
         }
       Jp_k = INV(Jp_k);
       SLELTI(J,k,Jp_k);
       Jp = J;

Return: /* Prepare for return. */
       return(Jp);
}

