/*======================================================================
                      AFCSBM(M,A; B,G)

Algebraic number Field univariate polynomial Coarsest Squarefree Basis 
with Multiplicities.

\Input
  \parm{M} is the integral minimal polynomial 
           of an algebraic number $\alpha$.
  \parm{A} is a list $(A_1,\ldots,A_n)$, $n \geq 0$, of
           monic positive univariate polynomials over $Q(\alpha)$. 
           Note that $deg(A_i)$ can be 0. (i.e. $A_i = 1$)

Output:
  \parm{B} is a list $(B_1,\ldots,Bm)$, $m \geq 0$
           which is a coarsest squarefree basis for $A$. 
  \parm{G} is the multiplicity matrix $(G_{i,j})$ of $B$ in $A$.
           (If $A_i = 1$, then $G_{i,k} = 0$ for every $k$.)
======================================================================*/
#include "qepcad.h"

void AFCSBM(Word M, Word A, Word *B_, Word *G_)
{
       Word A1,A11,Ap,As1,B,D,D1,E,F,G,H,L1,L11,U,d11;

Step1: /* Set up. */
       Ap = A; D = NIL; B = NIL; H = NIL;

Step2: /* Are we done? */
       if (Ap == NIL) { D = INV(D); U = MMFLR(D); G = MBPROD(U,H); goto Return; }

Step3: /* Squarefree Factorization. */
       ADV(Ap,&A1,&Ap);
       if (PDEG(A1) == 0)
         { D1 = NIL; As1 = NIL; }
       else
         {
         L1 = AFUPSF(M,A1); D1 = NIL; As1 = NIL;
         while (L1 != NIL)
           {
           ADV(L1,&L11,&L1); FIRST2(L11,&d11,&A11);
           D1 = COMP(d11,D1); As1 = COMP(A11,As1);
           }
         D1 = INV(D1); As1 = INV(As1);
         }
       D = COMP(D1,D);

Step4: /* Merge. */
       if (B != NIL && As1 != NIL)
         { AFMSBM(M,B,As1,&B,&E,&F); H = CONC(MBPROD(H,E),F); }
       else if (B != NIL)
         { B = B; H = H; }
       else if (As1 != NIL)
         { B = As1; H = IDENTMAT(LENGTH(As1)); }
       else
         { B = NIL; H = NIL; }
       goto Step2;

Return: /* Prepare for return. */
       *B_ = B;
       *G_ = G;
       return;
}
