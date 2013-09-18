/*======================================================================
                      IPFSBM(r,A; B,G)

Integral Polynomial Finest Squarefree Basis with Multiplicities.
 
\Input
  \parm{A} is a list $(A_1,\ldots,A_n)$, $n \geq 0$,
           of positive primitive integral polynomials 
           in $r$ variables, $r \geq 1$.
           Note that $deg(A_i)$ can be $0$. (i.e. $A_i = 1$.)
 
\Output
  \parm{B} is a list $(B1,\ldots,Bm)$, $m  \geq 0$,
           which is a finest squarefree basis for $A$.
  \parm{G} is a $n$ by $m$ matrix $(Gi,j)$ such that
           $A_i = B_1^G_{i,1} \cdots B_m^G_{i,m}$.
           (If $A_i = 1$, then $G_{i,k} = 0$ for $1 \leq k \eq m$.)
======================================================================*/
#include "qepcad.h"

void IPFSBM(Word r, Word A, Word *B_, Word *G_)
{
       Word A1,Ap,B,B1,Bp,E,E1,E11,F1,F11,G,G1,Gp,Q,Q1,Q11,Qp,R11,
            R111,X,X1,X11,e11,f11,i,j,m,n,t,x;
       /* hide i,j,m,n,t,x; */

Step1: /* Complete factorization. Get $Q $and $E$ from $A$. */
       Ap = A; Q = NIL; E = NIL;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap); Q1 = NIL; E1 = NIL;
         if (PDEG(A1) > 0) F1 = IPSF(r,A1); else F1 = NIL;
         while (F1 != NIL)
           {
           ADV(F1,&F11,&F1); FIRST2(F11,&e11,&f11);
           R11 = ISFPF(r,f11);
           while (R11 != NIL)
             { ADV(R11,&R111,&R11); Q1 = COMP(R111,Q1); E1 = COMP(e11,E1); }
           }
         Q1 = INV(Q1); E1 = INV(E1); Q = COMP(Q1,Q); E = COMP(E1,E);
         }
       Q = INV(Q); E = INV(E);

Step2: /* Get the finest squarefree basis.  Get $X$ and $B$ from $Q$. */
       B = NIL; m = 0; X = NIL; Qp = Q;
       while (Qp != NIL)
         {
         ADV(Qp,&Q1,&Qp); X1 = NIL;
         while (Q1 != NIL)
           {
           ADV(Q1,&Q11,&Q1); Bp = B;
           t = 0; x = m + 1;
           while (Bp != NIL && t == 0)
             {
             ADV(Bp,&B1,&Bp); x = x - 1;
             if (EQUAL(B1,Q11)) t = 1;
             }
           if (t == 0)
             { B = COMP(Q11,B); m = m + 1; X1 = COMP(m,X1); }
           else
             X1 = COMP(x,X1);
           }
         X1 = INV(X1); X = COMP(X1,X);
         }
        B = INV(B); X = INV(X);

Step3: /* Compute multiplicity matrix.  Get $G$ from $E$ and $X$. */
       n = LENGTH(A);
       G = NIL;
       for (i = 1; i <= n; i++)
         {
         G1 = NIL;
         for (j = 1; j <= m; j++)
           G1 = COMP(0,G1);
         G = COMP(G1,G);
         }
       Gp = G;
       while (Gp != NIL)
         {
         ADV(Gp,&G1,&Gp); ADV(X,&X1,&X); ADV(E,&E1,&E);
         while (E1 != NIL)
           {
           ADV(E1,&E11,&E1); ADV(X1,&X11,&X1);
           SLELTI(G1,X11,E11);
           }
         }
       goto Return;

Return: /* Prepare for return. */
       *B_ = B;
       *G_ = G;
       return;
}
