/*======================================================================
                      t <- QFFTEV(F,c,k)

Quantifier-Free Formula Trial Evaluation.

\Input
 \parm{F} is a non-constant normalized quantifier--free formula.
 \parm{c} is a non-root cell.
 \parm{k} is the level of the cell~$c$.
  
\Output
 \parm{t} is the trial truth value of $F$ on the cell $c$.
======================================================================*/
#include "qepcad.h"
static Word zeroQ(Word s, Word I_L);
static Word ATOMETFEVAL(Word Q, Word D, Word c, Word F);

Word QepcadCls::QFFTEV(Word F, Word c, Word k)
{
       Word F1,Fp,I,Pt,T,i,j,m,s,t,tp,z;
       /* hide m,t,tp,z; */

Step1: /* Classify the formula $F$. */
       T = FIRST(F);
       if (T == OROP) goto Step3;
       if (T == ANDOP) goto Step4;
       if (T == NOTOP)
       {
	 t = QFFTEV(SECOND(F),c,k);
	 if      (t == TRUE)  t = FALSE;
	 else if (t == FALSE) t = TRUE;
	 goto Return;
       }

Step2: /* Non-constant normalized atomic formula. */
       if (FIRST(F) == IROOT)
       {
	 t = ATOMETFEVAL(GVPF,GVPC,c,F);
	 goto Return;
       }

       /* Hoon's "true" and "false" - a 0-level formula with polynomial 0. */
       if (THIRD(F) == 0) {
	 t = (T == LEOP || T == GEOP || T == EQOP);
	 goto Return;
       }

       I = FOURTH(F); FIRST2(I,&i,&j);
       if (i > k) { t = UNDET; goto Return; }
       Pt = LELTI(LELTI(c,SIGNPF),k-i+1); 
       s = LELTI(Pt,j);
       if (s == UNDET) { t = UNDET; goto Return; }
       switch (T)
         {
         case LTOP: if (s < 0)  t = TRUE; else t = FALSE; break;
         case LEOP: if (s <= 0) t = TRUE; else t = FALSE; break;
         case GTOP: if (s > 0)  t = TRUE; else t = FALSE; break;
         case GEOP: if (s >= 0) t = TRUE; else t = FALSE; break;
         case EQOP: if (s == 0) t = TRUE; else t = FALSE; break;
         case NEOP: if (s != 0) t = TRUE; else t = FALSE; break;
         }
       goto Return;

Step3: /* Disjunction. */
       Fp = RED(F); z = 1;
       while (Fp != NIL)
         {
         ADV(Fp,&F1,&Fp);
         tp = QFFTEV(F1,c,k);
         if (tp == TRUE) { t = TRUE; goto Return; }
         if (tp == UNDET) z = 0;
         }
       if (z == 1) t = FALSE; else t = UNDET;
       goto Return;

Step4: /* Conjunction. */
       Fp = RED(F); z = 1;
       while (Fp != NIL)
         {
         ADV(Fp,&F1,&Fp);
         tp = QFFTEV(F1,c,k);
         if (tp == FALSE) { t = FALSE; goto Return; }
         if (tp == UNDET) z = 0;
         }
       if (z == 1) t = TRUE; else t = UNDET;
       goto Return;

Return: /* Prepare for return. */
       return(t);
}

/*
Inputs:
 s  : a list of N integers
 I_L: a list of integers in the range 1,...,N

Outputs:
 t  : t = TRUE if for some e \in I_L we have s[e] == 0
      t = FALSE otherwise
*/
static Word zeroQ(Word s, Word I_L)
{
  while(I_L != NIL && LELTI(s,FIRST(I_L)) != 0)
    I_L = RED(I_L);
  return I_L == NIL ? FALSE : TRUE;
}

/*
  Q : a QEPCAD projection factor set
  D : a QEPCAD CAD structure with P.F. set P
  C : a cell in D
  F : a normalized atomic Extended Tarski formula
 */
static Word ATOMETFEVAL(Word Q, Word D, Word c, Word F)
{
        Word X,T,j,P,k,I,t,ic,x,B,i,Q_k,I_L,Ip,n,Qp_k,m,S,count,Sp;
	double f;

Step1: /* Get info from F */
	FIRST6(F,&X,&T,&j,&P,&k,&I);
	if (LELTI(c,LEVEL) < k)
	{
	  t = UNDET;
	  goto Return;
	}

Step2: /* Get B, c's (k-1)-level base cell, and ic, the index of
c's k-level base cell in B's stack. */
	ic = LELTI(c,INDX);
	B = D;
	for(i = 1; i < k; i++)
	{
	  ADV(ic,&x,&ic);
	  B = LELTI(LELTI(B,CHILD),x);
	}
	ic = FIRST(ic);
	
Step3: /* Get the list of positions of elements of P in Q */
	Q_k = LELTI(Q,k);
	I_L = NIL;
	for(Ip = I; Ip != NIL; Ip = RED(Ip))
	{
	  n = SECOND(FIRST(Ip));
	  Qp_k = Q_k;
	  for(m = 1; n != THIRD(LELTI(FIRST(Qp_k),PO_LABEL)); m++)
	    Qp_k = RED(Qp_k);
	  I_L = COMP(m,I_L);
	}
  
Step4: /* If any of the elements of P are identically zero over B, 
return FALSE */
	S = LELTI(B,CHILD);
	if (zeroQ(FIRST(LELTI(FIRST(S),SIGNPF)),I_L))
	{
	  t = FALSE;
	  goto Return;
	}

Step5: /* Make sure P has at least |j| roots! */
	count = 0;
	for(Sp = RED(S); Sp != NIL; Sp = RED2(Sp))
	  if (zeroQ(FIRST(LELTI(FIRST(Sp),SIGNPF)),I_L))
	    count++;
	if (ABS(j) > count)
	{
	  t = FALSE;
	  goto Return;
	}

Step6: /* If j < 0 we turn the stack (and pos/neg) upside down! */
	if (j < 0)
	{
	  S = CINV(S);
	  if      (T == LTOP) T = GTOP;
	  else if (T == GTOP) T = LTOP;
	  else if (T == LEOP) T = GEOP;
	  else if (T == GEOP) T = LEOP;
	  j = -j;
	  ic = LENGTH(S) - ic + 1;
	}

Step7: /* Count distinct roots of prod P and check againts T & j */
	count = 0;
	S = RED(S);
	for(m = 2; m < ic; m += 2)
	{
	  if (zeroQ(FIRST(LELTI(FIRST(S),SIGNPF)),I_L))
	    count++;
	  S = RED2(S);
	}
	if (ic % 2 == 1 || !zeroQ(FIRST(LELTI(FIRST(S),SIGNPF)),I_L))
	  f = count + 0.5;
	else
	  f = count + 1;
	f = f - j;
	
	switch (T)
	{
	case LTOP: if (f < 0.0)  t = TRUE; else t = FALSE; break;
	case LEOP: if (f <= 0.0) t = TRUE; else t = FALSE; break;
	case GTOP: if (f > 0.0)  t = TRUE; else t = FALSE; break;
	case GEOP: if (f >= 0.0) t = TRUE; else t = FALSE; break;
	case EQOP: if (f == 0.0) t = TRUE; else t = FALSE; break;
	case NEOP: if (f != 0.0) t = TRUE; else t = FALSE; break;
	}
  
Return: /* Prepare to return */
	return t;
}

