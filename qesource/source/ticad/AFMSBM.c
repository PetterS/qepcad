/*======================================================================
                      AFMSBM(M,A,B; C,E,F)

Algebraic number Field Merge two Squarefree Basis with Multiplicities.

\Input
  \parm{M} is the integral minimal polynomial 
           of an algebraic number $\alpha$.
  \parm{A} is a list $(A_1,\ldots,A_n)$, $n > 0$, which is
           a squarefree basis over $Q(\alpha)$.
  \parm{B} is a list $(B_1,\ldots,B_m)$, $m > 0$, which is 
           a squarefree basis over $Q(\alpha)$.
      
\Output
  \parm{C} is a list $(C_1,\ldots,C_l)$ which is
           a squarefree basis for $(A_1,\ldots,A_n,B_1,\ldots,B_m)$.
  \parm{E} is the $n$ by $l$ multiplicity matrix of $C$ in $A$.
  \parm{F} is the $m$ by $l$ multiplicity matrix of $C$ in $B$.
======================================================================*/
#include "qepcad.h"

void AFMSBM(Word M, Word A, Word B, Word *C_, Word *E_, Word *F_)
{
       Word A1,Ap,As,B1,Bp,Bs,C,E,Ep,F,Fp,G,G11,h,i,j,m,n;
       /* hide h,i,j,m,n; */

Step1: /* Setup. */
       As = NIL; Ap = A;
       while (Ap != NIL) { ADV(Ap,&A1,&Ap); As = COMP(A1,As); } As = INV(As);
       Bs = NIL; Bp = B;
       while (Bp != NIL) { ADV(Bp,&B1,&Bp); Bs = COMP(B1,Bs); } Bs = INV(Bs);

Step2: /* gcd. */
       G = NIL; Ap = As;
       while (Ap != NIL)
         {
         A1 = FIRST(Ap);
         Bp = Bs;
         while (Bp != NIL)
           {
           B1 = FIRST(Bp);
           if (PDEG(A1) == 0 || PDEG(B1) == 0)
             { G11 = PMON(AFFINT(1),0); G = COMP(G11,G); }
           else
             {
             AFUPGC(M,A1,B1,&G11,&A1,&B1);
             SFIRST(Ap,A1); SFIRST(Bp,B1); G = COMP(G11,G);
             }
           Bp = RED(Bp);
           }
         Ap = RED(Ap);
         }
       G = INV(G);

Step3: /* Basis element from $A^*$. */
       n = LENGTH(As); m = LENGTH(Bs);
       E = NIL; for (i = 1; i <= n; i++) E = COMP(NIL,E);
       F = NIL; for (j = 1; j <= m; j++) F = COMP(NIL,F);
       C = NIL;
       for (i = 1; i <= n; i++)
         {
         ADV(As,&A1,&As);
         if (PDEG(A1) > 0)
           {
           C = COMP(A1,C);

           Ep = E;
           for (h = 1; h <= i - 1; h++) 
             { SFIRST(Ep,COMP(0,FIRST(Ep))); Ep = RED(Ep); }
           SFIRST(Ep,COMP(1,FIRST(Ep))); Ep = RED(Ep);
           for (h = i + 1; h <= n; h++) 
             { SFIRST(Ep,COMP(0,FIRST(Ep))); Ep = RED(Ep); }

           Fp = F;
           for (h = 1; h <= m; h++)     
             { SFIRST(Fp,COMP(0,FIRST(Fp))); Fp = RED(Fp); }
           }
         }

Step4: /* Basis element from $B^*$. */
       for (j = 1; j <= m; j++)
         {
         ADV(Bs,&B1,&Bs);
         if (PDEG(B1) > 0)
           {
           C = COMP(B1,C);

           Ep = E;
           for (h = 1; h <= n; h++)     
             { SFIRST(Ep,COMP(0,FIRST(Ep))); Ep = RED(Ep); }

           Fp = F;
           for (h = 1; h <= j - 1; h++) 
             { SFIRST(Fp,COMP(0,FIRST(Fp))); Fp = RED(Fp); }
           SFIRST(Fp,COMP(1,FIRST(Fp))); Fp = RED(Fp);
           for (h = j + 1; h <= m; h++) 
             { SFIRST(Fp,COMP(0,FIRST(Fp))); Fp = RED(Fp); }
           }
         }

Step5: /* Basis element from $G$. */
       for (i = 1; i <= n; i++) for (j = 1; j <= m; j++)
         {
         ADV(G,&G11,&G);
         if (PDEG(G11) > 0)
           {
           C = COMP(G11,C);

           Ep = E;
           for (h = 1; h <= i - 1; h++) 
             { SFIRST(Ep,COMP(0,FIRST(Ep))); Ep = RED(Ep); }
           SFIRST(Ep,COMP(1,FIRST(Ep))); Ep = RED(Ep);
           for (h = i + 1; h <= n; h++) 
             { SFIRST(Ep,COMP(0,FIRST(Ep))); Ep = RED(Ep); }

           Fp = F;
           for (h = 1; h <= j - 1; h++) 
             { SFIRST(Fp,COMP(0,FIRST(Fp))); Fp = RED(Fp); }
           SFIRST(Fp,COMP(1,FIRST(Fp))); Fp = RED(Fp);
           for (h = j + 1; h <= m; h++) 
             { SFIRST(Fp,COMP(0,FIRST(Fp))); Fp = RED(Fp); }
          }
        }

Return: /* Prepare for return. */
       *C_ = C;
       *E_ = E;
       *F_ = F;
       return;
}
