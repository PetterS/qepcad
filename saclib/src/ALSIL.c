/*=====================================================================
			M <- ALSIL(A,L)

Attach labels to standard isolation list.

Inputs
  A : an integral polynomial all of whose real roots are
      simple.
  L : a standard isolation list for all of the real roots
      of A.

Outputs
  M : a labeled standard isolation list for all of the real
      roots of A.
=====================================================================*/
#include "saclib.h"

Word ALSIL(A,L)
       Word A,L;
{
       Word a,I,Lp,n,M,t,T;

Step1: /* Determine trend of first interval. */
       n = PDEG(A);
       a = PLDCF(A);
       if (EVEN(n))
	  t = -1;
       else 
	  t = +1;
       if (ISIGNF(a) < 0)
	  t = -t;

Step2: /* Label each interval. */
       M = NIL;
       Lp = L;
       while (Lp != NIL) {
	  I = FIRST(Lp);
	  Lp = RED(Lp);
	  T = LIST3(I,A,t);
	  t = -t;
	  M = COMP(T,M); }
       M = INV(M);

Return: /* Return M. */
       return(M);
}
