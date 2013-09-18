/*======================================================================
                      AFUPLM(M,A; L,P)

Algebraic number Field Univaraite Polynomials Leading coefficients 
and Monic associates.

\Input
  \parm{M} is the integral minimal polynomial 
           of an algebraic number $\alpha$.
  \parm{A} is a list $(A_1,\ldots,A_n)$, $n >= 0$, 
           of univariate polynomials over $Q(\alpha)$.
           Note that $A_i$ can be $0$.  
      
\Output
  \parm{L} is the list $(L_1,\ldots,L_n)$
           where $L_i$ is the leading coefficient of $A_i$.
  \parm{P} is the list $(P_1,\ldots,P_n)$ n >= 0$
           where $P_i$ is the monic associate of $A_i$.
           (If $A_i = 0$, then $L_i = 0$ and $P_i = 1$.)
           Therefore $A_i = L_i  P_i$  for every $i$.
======================================================================*/
#include "qepcad.h"

void AFUPLM(Word M, Word A, Word *L_, Word *P_)
{
       Word A1,Ap,L,L1,P,P1;

Step1: /* Compute. */
       L = NIL; P = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         if (A1 == 0)
           { L1 = 0; P1 = PINV(0,AFFINT(1),1); }
         else
           { L1 = PLBCF(1,A1); 
	     P1 = AFPAFP(1,M,AFINV(M,L1),A1); }
         L = COMP(L1,L); P = COMP(P1,P);
         }
       L = INV(L); P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       *L_ = L;
       *P_ = P;
       return;
}
