/*======================================================================
                      Fp <- RMCAFS(F)

Remove Constant Atomic Formulas.

\Input
  \parm{F} is a quantifier--free formula.
 
\Output
  \parm{F'} is a quantifier--free formula 
            obtained from \v{F} by removing all the
            constant atomic formulas if possible.
======================================================================*/
#include "qepcad.h"

Word RMCAFS(Word F)
{
       Word F1,F2,Fb,Fp,Fp1,Fp2,T,t,t1,t2;
       /* hide t,t1,t2; */

Step1: /* Classify the formula F. */
       T = FIRST(F);
       if (T == ANDOP) goto Step3;
       if (T == OROP) goto Step4;
       if (T == NOTOP) goto Step5;
       if (T == RIGHTOP) goto Step6;
       if (T == LEFTOP) goto Step7;
       if (T == EQUIOP) goto Step8;

Step2: /* Atomic Formula. */
       t = TYPEAF(F);
       if (t == TRUE) { Fp = LIST4(EQOP,0,0,NIL); goto Return; }
       if (t == FALSE) { Fp = LIST4(NEOP,0,0,NIL); goto Return; }
       Fp = F; goto Return;

Step3: /* Conjunction. */
       Fb = RED(F); Fp = LIST1(ANDOP);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMCAFS(F1); t = TYPEQFF(Fp1);
         if (t == FALSE) { Fp = LIST4(NEOP,0,0,NIL); goto Return; }
         if (t == UNDET) Fp = COMP(Fp1,Fp);
         }
       if (LENGTH(Fp) == 1) { Fp = LIST4(EQOP,0,0,NIL); goto Return; }
       if (LENGTH(Fp) == 2) { Fp = FIRST(Fp); goto Return; }
       Fp = INV(Fp); goto Return;

Step4: /* Disjunction. */
       Fb = RED(F); Fp = LIST1(OROP);
       while (Fb != NIL)
         {
         ADV(Fb,&F1,&Fb);
         Fp1 = RMCAFS(F1); t = TYPEQFF(Fp1);
         if (t == TRUE) { Fp = LIST4(EQOP,0,0,NIL); goto Return; }
         if (t == UNDET) Fp = COMP(Fp1,Fp);
         }
       if (LENGTH(Fp) == 1) { Fp = LIST4(NEOP,0,0,NIL); goto Return; }
       if (LENGTH(Fp) == 2) { Fp = FIRST(Fp); goto Return; }
       Fp = INV(Fp); goto Return;

Step5: /* Negation. */
       F1 = SECOND(F); Fp1 = RMCAFS(F1); t = TYPEQFF(Fp1);
       if (t == TRUE) Fp = LIST4(NEOP,0,0,NIL);
       else if (t == FALSE) Fp = LIST4(EQOP,0,0,NIL);
       else Fp = LIST2(NOTOP,Fp1);
       goto Return;

Step6: /* $\Rightarrow$. */
       F1 = SECOND(F); Fp1 = RMCAFS(F1); t1 = TYPEQFF(Fp1);
       F2 = THIRD(F); Fp2 = RMCAFS(F2); t2 = TYPEQFF(Fp2);
       if (t1 == TRUE) Fp = Fp2;
       else if (t1 == FALSE) Fp = LIST4(EQOP,0,0,NIL);
       else if (t2 == TRUE) Fp = LIST4(EQOP,0,0,NIL);
       else if (t2 == FALSE) Fp = LIST2(NOTOP,Fp1);
       else Fp = LIST3(RIGHTOP,Fp1,Fp2);
       goto Return;

Step7: /* $\Leftarrow$. */
       F1 = THIRD(F); Fp1 = RMCAFS(F1); t1 = TYPEQFF(Fp1);
       F2 = SECOND(F); Fp2 = RMCAFS(F2); t2 = TYPEQFF(Fp2);
       if (t1 == TRUE) Fp = Fp2;
       else if (t1 == FALSE) Fp = LIST4(EQOP,0,0,NIL);
       else if (t2 == TRUE) Fp = LIST4(EQOP,0,0,NIL);
       else if (t2 == FALSE) Fp = LIST2(NOTOP,Fp1);
       else Fp = LIST3(LEFTOP,Fp2,Fp1);
       goto Return;

Step8: /* $\Leftrightarrow$. */
       F1 = SECOND(F); Fp1 = RMCAFS(F1); t1 = TYPEQFF(Fp1);
       F2 = THIRD(F); Fp2 = RMCAFS(F2); t2 = TYPEQFF(Fp2);
       if (t1 == TRUE) Fp = Fp2;
       else if (t2 == TRUE) Fp = Fp1;
       else if (t1 == FALSE && t2 == FALSE) Fp = LIST4(EQOP,0,0,NIL);
       else if (t1 == FALSE) Fp = LIST2(NOTOP,Fp2);
       else if (t2 == FALSE) Fp = LIST2(NOTOP,Fp1);
       else Fp = LIST3(EQUIOP,Fp1,Fp2);
       goto Return;

Return: /* Prepare for return. */
       return(Fp);
}
