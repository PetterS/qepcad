/*======================================================================
                      C <- MBPROD(A,B)

Matrix of Beta integers Product.

\Input 
  \parm{A} is a  $p$ by $q$ matrix of $\beta$--integers
           where $p \geq 0$ and $q \geq 0$.
  \parm{B} is a  $q$ by $r$ matrix of $\beta$--integers 
           where $q \geq 0$ and $r \geq 0$.
           The elements of the matrices $A$ and $B$ must 
           be sufficiently small so that the elements of 
           the resulting matrix $C=AB$ are also $\beta$--integers.
       
\Output
  \parm{C} is the $p$ by $r$ matrix of $\beta$--integers 
           such that $C = AB$.
======================================================================*/
#include "qepcad.h"

Word MBPROD(Word A, Word B)
{
       Word A1,A11,Ap,Ap1,B1,B11,Bp,Bs,C,C1,C11,i,j,k,p,q,qp,r;
       /* hide C11,i,j,k,p,q,qp,r; */

Step1: /* Get the sizes of $A$ and $B$. */
        p = LENGTH(A); if (p == 0) q = 0; else q = LENGTH(FIRST(A));
        qp = LENGTH(B); if (qp == 0) r = 0; else r = LENGTH(FIRST(B));

Step2: /* Multiply. */
        C = NIL; Ap = A;
        for (i = 1; i <= p; i++)
           {
           C1 = NIL; ADV(Ap,&A1,&Ap); Bp = B;
           for (j = 1; j <= r; j++)
              {
              C11 = 0; Bs = NIL; Ap1 = A1;
              for (k = 1; k <= q; k++)
                 {
                 ADV(Ap1,&A11,&Ap1);
                 ADV(Bp,&B1,&Bp); ADV(B1,&B11,&B1);
                 C11 = C11 + A11 * B11;
                 Bs = COMP(B1,Bs);
                 }
              Bp = INV(Bs); C1 = COMP(C11,C1);
              }
           C1 = INV(C1); C = COMP(C1,C);
           }
        C = INV(C);
        goto Return;

Return: /* Prepare for return. */
       return(C);
}
