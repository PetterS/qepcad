/*======================================================================
                      IPLSRP(A; s,P)

Integral Polynomial List Similar to Rational Polynomials.

\Input
 \parm{A} is a list $(A_1,\ldots,A_n)$, $n \geq 0$,
          of rational univariate polynomials.
          Note that $A_i$ can be 0.  
      
\Output
  \parm{s} is the list $(s_1,\ldots,s_n)$, $n \geq 0$, 
           where $s_i$ is the sign of $A_i$.
  \parm{P} is the list $(P_1,\ldots,P_n)$, $n \geq 0$, 
           where $P_i$ is the  positive primitive
           integral polynomial similiar to $A_i$.
           (If $A_i = 0$, then $s_i = 0$ and $P_i = 1$.)
======================================================================*/
#include "qepcad.h"

void IPLSRP(Word A, Word *s_, Word *P_)
{
       Word A1,Ap,P,P1,a,s,s1;
       /* hide s1; */

Step1: /* Compute. */
       s = NIL; P = NIL;
       Ap = A;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         if (A1 == 0)
           { P1 = PMON(1,0); s1 = 0; }
         else
           { IPSRP(1,A1,&a,&P1); s1 = RNSIGN(a); }
         s = COMP(s1,s); P = COMP(P1,P);
         }
       s = INV(s); P = INV(P);
       goto Return;

Return: /* Prepare for return. */
       *s_ = s;
       *P_ = P;
       return;
}
