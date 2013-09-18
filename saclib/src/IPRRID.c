/*======================================================================
			 L <- IPRRID(A)

Integral polynomial real root isolation, Descartes method.

Inputs
 A : in Z[x], non-zero, squarefree.

Outputs
  L : a list (I_1,...,I_r) of standard logarithmic open or one-point
      binary rational isolating intervals for all of the real roots
      of A.  Let (a_j,b_j) denote the endpoints of I_j.  Then 
      a_1 <= b_1 <= ... <= a_r <= b_r.
======================================================================*/
#include "saclib.h"

Word IPRRID(A)
       Word A;
{
       Word n,k;
       Word Ab,As,I,L,Ls,a,b;

Step1: /* Degree zero. */
       n = PDEG(A);
       L = NIL;
       if (n == 0)
	  goto Return;

Step2: /* Isolate positive roots. */
       Ab = PDBORD(A);
       b = IUPPRB(Ab);
       if (b == 0)
	  goto Step3;
       k = -SECOND(b);
       As = IUPBHT(Ab,k);
       L = IPRRISD(As,0,b);

Step3: /* Is 0 a root? */
       if (FIRST(Ab) < n)
	  L = COMP(LIST2(0,0),L);

Step4: /* Isolate negative roots. */
       Ab = IUPNT(Ab);
       b = IUPPRB(Ab);
       if (b == 0)
	  goto Return;
       k = -SECOND(b);
       As = IUPBHT(Ab,k);
       Ls = IPRRISD(As,0,b);
       while (Ls != NIL) {
	  ADV(Ls,&I,&Ls);
	  FIRST2(I,&a,&b);
	  I = LIST2(LBRNNEG(b),LBRNNEG(a));
	  L = COMP(I,L); }

Return: /* Prepare for return. */
       return(L);

}
