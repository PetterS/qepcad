/*======================================================================
                      Fp <- RMNOTOP(F)

Remove NOTOP from a quantifier--free formula.

\Input
   \parm{F} is a quantifier free formula which uses the following operators:
            $\lor$, $\land$, and $\neg$.   

\Output    
  \parm{F'} is the quantifier free formula equivalent to \v{F}, 
            obtained from \v{F} by removing all the $\neg$ operators 
            except those directly proceeding an atomic extended Tarski 
	    formula.
======================================================================*/
#include "qepcad.h"

Word RMNOTOP(Word F)
{
       Word F1,Fb,Fp,Fp1,T;

Step1: /* Classify the formula v{F}. */
       T = FIRST(F);
       if (T == ANDOP) goto Step3;
       if (T == OROP) goto Step3;
       if (T == NOTOP) goto Step4;

Step2: /* Atomic Formula. */
       Fp = F; goto Return;

Step3: /* Conjunction/Disjunction. */
       Fb = RED(F); Fp = LIST1(T);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMNOTOP(F1);
         Fp = COMP(Fp1,Fp);
         }
       Fp = INV(Fp);
       goto Return;

Step4: /* Negation. */
       F1 = SECOND(F);
       Fp = RMNOTOPN(F1);
       goto Return;

Return: /* Prepare for return. */
       return(Fp);
}
