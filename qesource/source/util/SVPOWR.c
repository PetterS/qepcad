/*======================================================================
                      C <- SVPOWR(A,G)

Sign Vector Power Product.

\Input
  \parm{A}  is a list $(A_1,\ldots,A_m)$, $m>=0$, of signs.
  \parm{G}  is a $n$ by $m$ matrix $(G_{i,j})$, $n \geq 0$ 
            of non-negative $\beta$--intergers.

\Output
  \parm{C}  is the list $(C_1,\ldots,C_n)$
            such that  $C_i = A_1^{G_{i,1}} \cdots A_m^{G_{i,m}} 
            Note the following the two special cases:
            Case 1. if $n = 0$ and $m = 0$, then 
                    $C = ()$.
            Case 2. if $n \neq 0$ and $m = 0$, then 
                    $C =(1,\ldots,1)$.
======================================================================*/
#include "qepcad.h"

Word SVPOWR(Word A, Word G)
{
       Word A1,Ap,C,C1,C11,G1,G11,Gp;
       /* hide C1,C11; */

Step1: /* Compute. */
       C = NIL; Gp = G;
       while (Gp != NIL)
         {
         C1 = 1;
         ADV(Gp,&G1,&Gp);
         Ap = A;
         while (G1 != NIL)
           {
           ADV(G1,&G11,&G1);
           ADV(Ap,&A1,&Ap);
           C11 = SPOWER(A1,G11);
           C1 = C1 * C11;
           }
         C = COMP(C1,C);
         }
       C = INV(C);
       goto Return;

Return: /* Prepare for return. */
       return(C);
}
