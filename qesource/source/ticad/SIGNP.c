/*======================================================================
                      SIGNP(c,k,B,I,E,L)

Signatures of Projection factors.
 
\Input
   \parm{c} is a non-root cell.
   \parm{k} is the level of the cell~$c$.
   \parm{B} is an algebraic univariate squarefree basis.
   \parm{I} is a list of the real roots of $B$.
   \parm{E} is a multiplicity matrix. 
   \parm{L} is a list of leading coefficients. 
 
\Output
   The signatures of~$P_{k+1}$, 
   the $(k+1)$--level projection factors,
   on the cells in the stack over~$c$ 
   are determined and attached to them.
======================================================================*/
#include "qepcad.h"

void SIGNP(Word c, Word k, Word B, Word I, Word E, Word L)
{
       Word Lt,Pt,S,S1,c1,cb;

Step1: /* Compute the signatures of $B$. */
       S = SIGNB(B,I);

Step2: /* Compute the signature of $L$. */
       Lt = SIGNL(c,L);

Step3: /* Compute the signatures of $P_{k+1}$ and attach. */
       cb = LELTI(c,CHILD);
       while (cb != NIL)
         {
         ADV(cb,&c1,&cb); ADV(S,&S1,&S);
         Pt = SVPROD(Lt,SVPOWR(S1,E));
         SFIRST(LELTI(c1,SIGNPF),Pt);
         }
       goto Return;

Return: /* Prepare for return. */
       return;
}
