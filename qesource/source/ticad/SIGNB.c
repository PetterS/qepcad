/*======================================================================
                      S <- SIGNB(B,I)

Signatures of squarefree Basis polynomials.
 
\Input
  \parm{B} is a list $(B_1,\ldots,B_v)$, $v \geq 0$,
           which a square-free basis,
           either algebraic or integral.
  \parm{I} is a list $(I_1,b_1,\ldots,I_u,b_u)$, $u \geq 0$,
           where $I_1 < I_2 < \cdots < I_u$
           are disjoint isolating intervals
           for all the real roots of $\prod_{j=1}^v B_j$ and
           each $b_i$ is the unique $B_k$ which has a root in $I_i$.
 
\Output
  \parm{S} is a $(2u+1)$ by $v$ matrix  $(S_{i,j})$ where
           $S_{i,j}$ is the sign of $B_j$ in the $i$--th cell
           in the stack determined by the real roots.
======================================================================*/
#include "qepcad.h"

Word SIGNB(Word B, Word I)
{
       Word I1,Ip,K,S,S0,S1,Sp1,b1,i,j,k,s,u,v;
       /* hide i,j,u,v; */

Step1: /* Setup. */
       K = NIL; Ip = I;
       while (Ip != NIL)
         { ADV2(Ip,&I1,&b1,&Ip); k = LSRCH(b1,B); K = COMP(k,K); }
       K = INV(K); u = LENGTH(K); v = LENGTH(B); S = NIL;

Step2: /* Rightmost cell. */
       S1 = NIL; for (j = 1; j <= v; j++) S1 = COMP(1,S1); S = COMP(S1,S);
       i = u;

Step3: /* Done? */
       if (i == 0) goto Return;

Step4: /* Next two cells. */
       k = LELTI(K,i);
       Sp1 = S1; S0 = NIL; S1 = NIL;
       for (j = 1; j <= v; j++)
         {
         ADV(Sp1,&s,&Sp1);
         if (j == k)
           {
           S0 = COMP(0,S0);
           S1 = COMP(-s,S1);
           }
         else
           {
           S0 = COMP(s,S0);
           S1 = COMP(s,S1);
           }
         }
       S0 = INV(S0); S1 = INV(S1); S = COMP2(S1,S0,S);
       i = i - 1;
       goto Step3;

Return: /* Prepare for return. */
       return(S);
}
