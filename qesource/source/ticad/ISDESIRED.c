/*======================================================================
                      t <- ISDESIRED(c,C)

Is it a desired cell?

\Input
  \parm{s} is a cell.
  \parm{C} is the condition for desired cell.

\Output
  \parm{t} is 1 if \v{c} satisfies the condion C. 0 otherwise.

\Remark
   t is set to 1 if c is the root cell, no matter what C is.
======================================================================*/
#include "qepcad.h"

Word ISDESIRED(Word c, Word C)
{
       Word C1,C2,Cp,T,V1,V2,t;
       /* hide C1,C2,Cp,T,V1,V2,t; */

Step1: /* Classify the condition. */
       if (LELTI(c,LEVEL) == 0) { t = 1; goto Return; }
       T = FIRST(C);
       if (T == OROP)    goto Step3;
       if (T == ANDOP)   goto Step4;
       if (T == NOTOP)   goto Step5;
       if (T == LEFTOP)  goto Step6;
       if (T == RIGHTOP) goto Step7;
       if (T == EQUIOP)  goto Step8;

Step2: /* Atomic condition. */
       V1 = SECOND(C); V2 = THIRD(C);
       if (V1 < 0 )  V1 = CELLATTR(c,V1);
       if (V2 < 0 )  V2 = CELLATTR(c,V2);
       if (V1 == NIL || V2 == NIL)
	 {t = 0; goto Return;}
       switch(T)
         {
         case LTOP: t = (V1 <   V2 ? 1 : 0); break;
         case EQOP: t = (V1 ==  V2 ? 1 : 0); break;
         case GTOP: t = (V1 >   V2 ? 1 : 0); break;
         case GEOP: t = (V1 >=  V2 ? 1 : 0); break;
         case NEOP: t = (V1 !=  V2 ? 1 : 0); break;
         case LEOP: t = (V1 <=  V2 ? 1 : 0); break;
         }
       goto Return;

Step3: /* Disjunction. */
       Cp = RED(C);
       while (Cp != NIL)
         {
         ADV(Cp,&C1,&Cp);
         t = ISDESIRED(c,C1);
         if (t == 1) goto Return;
         }
       t = 0;
       goto Return;

Step4: /* Conjunction. */
       Cp = RED(C); 
       while (Cp != NIL)
         {
         ADV(Cp,&C1,&Cp);
         t = ISDESIRED(c,C1);
         if (t == 0) goto Return;
         }
       t = 1;
       goto Return;

Step5: /* Negation. */
       C1 = SECOND(C);
       t = (ISDESIRED(c,C1) ? 0 : 1);
       goto Return;

Step6: /* <==. */
       C1 = SECOND(C);
       C2 = THIRD(C);
       t = (ISDESIRED(c,C1) || (!ISDESIRED(c,C2)) ? 1 : 0);
       goto Return;       

Step7: /* ==>. */
       C1 = SECOND(C);
       C2 = THIRD(C);
       t = ((!ISDESIRED(c,C1)) || ISDESIRED(c,C2) ? 1 : 0);
       goto Return;

Step8: /* <==>. */
       C1 = SECOND(C);
       C2 = THIRD(C);
       t = (ISDESIRED(c,C1) == ISDESIRED(c,C2) ? 1 : 0);
       goto Return;  

Return: /* Prepare for return. */
       return(t);
}
