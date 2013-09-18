/*=====================================================================
			 L <- IPRRIS(A)

Integral polynomial real root isolation, Sturm method.
 
Inputs  
   A : in Z[x], non-zero, squarefree.

Outputs
   L : a list (I_1,...,I_r) of isolating intervals for all of
       the real roots of A, with I_1 < I_2 < ... < I_r.
       Each I_j is either an open or a one-point logarithmic
       standard interval.
======================================================================*/
#include "saclib.h"

Word IPRRIS(A)
       Word A;
{
       Word Ap,Ab,b,bp,L,L1,s,S,S1,S2,t,v1,v2;

Step1: /* Compute a primitive Sturm sequence S. */
       Ab = IPIPP(1,A);
       Ap = IPIPP(1,IPDMV(1,Ab));
       S = IPPNPRS(Ab,Ap);

Step2: /* Isolate positive roots. */
       b = IUPPRB(Ab);
       L = NIL;
       S1 = IPLSEVAL(S,0);
       v1 = VAR(S1);
       if (b == 0)
	  goto Step3;
       S2 = IPLSEVAL(S,b);
       v2 = VAR(S2);
       s = FIRST(S2);
       L = IPRRISS(S,0,b,v1,v2,s);

Step3: /* Is 0 a root? */
       t = FIRST(S1);
       if (t == 0)
	  L = COMP(LIST2(0,0),L);

Step4: /* Isolate negative roots. */
       Ab = IUPNT(Ab);
       b = IUPPRB(Ab);
       if (b == 0)
	  goto Return;
       bp = LBRNNEG(b);
       S2 = IPLSEVAL(S,bp);
       v2 = VAR(S2);
       s = FIRST(S1);
       L1 = IPRRISS(S,bp,0,v2,v1,s);

Step5: /* Concatenate isolation lists. */
       L = CONC(L1,L);

Return: /* Prepare for return. */
       return(L);
}
