/*======================================================================
                      Ap <- CHANGEASSUMPTIONSLEVEL(A,r,necflag)

Change assumptions level

Input
  A : the normalized assumptions formula
  r : the target level
  necflag: a BDigit, either 0 or 1
           necflag = 1 means lower level to produce necessary conditions
           necflag = 0 means lower level to produce sufficient conditions
  
Ouput
  Ap : An unnormalized formula of level r.  If necflag = 1, then
       A ==> Ap, if necflag = 0, then Ap => A.
======================================================================*/
#include "qepcad.h"

static Word CHANGEASSUMPTIONSLEVELhelp(Word A, BDigit r, BDigit necflag);

Word CHANGEASSUMPTIONSLEVEL(Word A, BDigit r, BDigit necflag)
{
  Word Ap = CHANGEASSUMPTIONSLEVELhelp(A,r,necflag);
  if (Ap == UNDET && necflag == 1)
    Ap = TRUE;
  else if (Ap == UNDET && necflag == 0)
    Ap = FALSE;
  return Ap;
}

static Word CHANGEASSUMPTIONSLEVELhelp(Word A, BDigit r, BDigit necflag)
{
  Word F, Fp, T, Ap, f;

  if (!ISLIST(A)) { Ap = A; goto Return; }
  F = A;
  T = FIRST(F);
  
Step1: /* NOTOP */
       if (T == NOTOP)
       {
	 Fp = CHANGEASSUMPTIONSLEVEL(SECOND(F),r,(necflag+1)%2);
	 if      (Fp == UNDET) Ap = UNDET;
	 else if (Fp == TRUE)  Ap = FALSE;
	 else if (Fp == FALSE) Ap = TRUE;
	 else Ap = LIST2(NOTOP,Fp);
	 goto Return;
       }
Step2: /* Disjunction. */
       if (T == OROP)
       {
	 Ap = NIL;
	 for(F = RED(F); F != NIL; F = RED(F))
	 {
	   f = CHANGEASSUMPTIONSLEVEL(FIRST(F),r,necflag);
	   if (f == TRUE || (f == UNDET && necflag)) {
	     Ap = f;
	     goto Return; }
	   if (f != UNDET && f != FALSE)
	     Ap = COMP(f,Ap);
	 }
	 if (Ap == NIL)
	   Ap = FALSE;
	 else
	   Ap = COMP(OROP,Ap);
	 goto Return;
       }

Step3: /* Conjunction. */
       if (T == ANDOP)
       {
	 Ap = NIL;
	 for(F = RED(F); F != NIL; F = RED(F))
	 {
	   f = CHANGEASSUMPTIONSLEVEL(FIRST(F),r,necflag);
	   if (f == FALSE || (f == UNDET && !necflag)) {
	     Ap = f;
	     goto Return; }
	   if (f != UNDET && f != TRUE)
	     Ap = COMP(f,Ap);
	 }
	 if (Ap == NIL)
	   Ap = TRUE;
	 else
	   Ap = COMP(ANDOP,Ap);
	 goto Return;
       }

Step4: /* Non-constant normalized atomic formula. */
       if (FIRST(F) == IROOT)
       {
	 if (LELTI(F,5) > r)
	   Ap = UNDET;
	 else
	   Ap = F;
	 goto Return;
       }

       /* Hoon's "true" and "false" - a 0-level formula with polynomial 0. */
       if (THIRD(F) == 0) {
	 Ap = (T == LEOP || T == GEOP || T == EQOP);
	 goto Return;
       }

       if (THIRD(F) > r)
	 Ap = UNDET;
       else
	 Ap = F;
       goto Return;

Return:
       return Ap;
}

