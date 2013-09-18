/*======================================================================
                      PQFF(F,L; Lp)

Polynomials in Quantifier Free Formula.
 
\Input
  \parm{F} is a quantifier-free formula.
  \parm{L} is a list of 3-tuple~$(A,r,I)$,
       where $A$ is a distinct integral polynomial,
             $r$ is the number of variables in $A$.
             $I$ is the index.
\Output
  \parm{L'} is obtained from $L$ by appending  
            the new polynomials occuring in $F$.

\Side
  \parm{L} is modified.
======================================================================*/
#include "qepcad.h"

void PQFF(Word F, Word L, Word *Lp_)
{
       Word A,F1,Fp,I,L1,Lp,Ls,Ls1,T,r;

Step1: /* Classify the formula $F$. */
       T = FIRST(F);
       if (T == OROP || T == ANDOP || T == NOTOP || T == RIGHTOP || T == LEFTOP || T == EQUIOP) goto Step3;

Step2: /* Atmotic formula. */
       FIRST4(F,&T,&A,&r,&I);
       L1 = LIST3(A,r,I);
       Ls = L;
       while (Ls != NIL)
         {
         ADV(Ls,&Ls1,&Ls);
         if (EQUAL(L1,Ls1))
           { Lp = L; goto Return; }
         }
       Lp = CONC(L,LIST1(L1));
       goto Return;

Step3: /* All others. */
       Lp = L; Fp = RED(F);
       while (Fp != NIL)
         {
         ADV(Fp,&F1,&Fp);
         PQFF(F1,Lp,&Lp);
         }
       goto Return;

Return: /* Prepare for return. */
       *Lp_ = Lp;
       return;
}
