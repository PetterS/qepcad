/*======================================================================
                      Fp <- RMNOTOPN(F)

Remove NOTOP from a quantifier--free formula after Negating.

\Input
   \parm{F} is a quantifier free formula which uses the following operators:
            $\lor$, $\land$, and $\neg$.   

\Output    
  \parm{F'} is the quantifier free formula equivalent to $\neg$ \v{F}, 
            obtained from  $neg$ \v{F} by removing all the $\neg$ 
            operators except those directly proceeding an atomic extended
            Tarski formula.
======================================================================*/
#include "qepcad.h"

Word RMNOTOPN(Word F)
{
       Word F1,Fb,Fp,Fp1,I,P,T,Tp,r;
       /* hide Tp; */

Step1: /* Classify the formula \v{F}. */
       T = FIRST(F);
       if (T == ANDOP) goto Step3;
       if (T == OROP) goto Step4;
       if (T == NOTOP) goto Step5;

Step2: /* Atomic Formula. */
       if (FIRST(F) == IROOT)
       {
	 Fp = LIST2(NOTOP,F);
	 goto Return;
       }
       FIRST4(F,&T,&P,&r,&I);
       switch (T)
         {
         case LTOP: Tp = GEOP; break;
         case LEOP: Tp = GTOP; break;
         case GTOP: Tp = LEOP; break;
         case GEOP: Tp = LTOP; break;
         case EQOP: Tp = NEOP; break;
         case NEOP: Tp = EQOP; break;
         }
       Fp = LIST4(Tp,P,r,I);
       goto Return;

Step3: /* Conjunction. */
       Fb = RED(F); Fp = LIST1(OROP);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMNOTOPN(F1);
         Fp = COMP(Fp1,Fp);
         }
       Fp = INV(Fp);
       goto Return;

Step4: /* Disjunction. */
       Fb = RED(F); Fp = LIST1(ANDOP);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMNOTOPN(F1);
         Fp = COMP(Fp1,Fp);
         }
       Fp = INV(Fp);
       goto Return;

Step5: /* Negation. */
       F1 = SECOND(F);
       Fp = RMNOTOP(F1);
       goto Return;

Return: /* Prepare for return. */
       return(Fp);
}
