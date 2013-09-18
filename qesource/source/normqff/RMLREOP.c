/*======================================================================
                      Fp <- RMLREOP(F)

Remove all LEFTOP, RIGHTOP, and EQUIOP from a quantifier-free formula.

\Input
   \parm{F} is a quantifier free formula.
     
\Output
  \parm{F'} is a quantifier free fomrula obatained from F
            by removing $\Leftarrow$, $\Rightarrow$, $\Leftrightarrow$.
======================================================================*/
#include "qepcad.h"

Word RMLREOP(Word F)
{
       Word F1,F2,Fb,Fp,Fp1,Fp2,Fs1,Fs2,T;

Step1: /* Classify the formula F. */
       T = FIRST(F);
       if (T == ANDOP) goto Step3;
       if (T == OROP) goto Step3;
       if (T == NOTOP) goto Step3;
       if (T == RIGHTOP) goto Step4;
       if (T == LEFTOP) goto Step5;
       if (T == EQUIOP) goto Step6;

Step2: /* Atomic Formula. */
       Fp = F; goto Return;

Step3: /* Conjunction/Disjunction/Negation. */
       Fb = RED(F); Fp = LIST1(T);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMLREOP(F1);
         Fp = COMP(Fp1,Fp);
         }
       Fp = INV(Fp);
       goto Return;

Step4: /* $\Rightarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       Fp1 = RMLREOP(F1); Fp2 = RMLREOP(F2);
       Fp = LIST3(OROP,LIST2(NOTOP,Fp1),Fp2);
       goto Return;

Step5: /* $\Leftarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       Fp1 = RMLREOP(F1); Fp2 = RMLREOP(F2);
       Fp = LIST3(OROP,Fp1,LIST2(NOTOP,Fp2));
       goto Return;

Step6: /* $\Leftrightarrow$. */
       F1 = SECOND(F); F2 = THIRD(F);
       Fp1 = RMLREOP(F1); Fp2 = RMLREOP(F2);
       Fs1 = LIST3(OROP,LIST2(NOTOP,Fp1),Fp2);
       Fs2 = LIST3(OROP,Fp1,LIST2(NOTOP,Fp2));
       Fp = LIST3(ANDOP,Fs1,Fs2);
       goto Return;

Return: /* Prepare for return. */
       return(Fp);
}
