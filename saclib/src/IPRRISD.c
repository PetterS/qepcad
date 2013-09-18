/*======================================================================
		      L <- IPRRISD(A,a,b)

Integral polynomial real root isolation, standard interval,
Descartes method.

Inputs
   A : in Z[x], squarefree.
   a, b:  logarithmic binary rational numbers, a < b, such that
          (a,b) is an open logarithmic standard interval.

Output
   L : (T(I_1),...,T(I_r)), where (I_1,...,I_r) is a list of 
       logarithmic standard isolating intervals for all the
       roots of A in the open interval (0,1) and T is the linear
       fractional transformation, T(x) = (b - a) x + a, that maps
       (0,1) onto (a,b).  Each I_j is either an open interval or
       a one-point interval,  and T(I_1) < ... < T(I_r).
======================================================================*/
#include "saclib.h"

Word IPRRISD(A,a,b)
       Word A,a,b;
{
       Word B,c,d,e,K,Kp,L,v;

Step1: /* Trivial cases. */
       L = NIL;     
       if (A == 0)
	 goto Return;
       v = IPVCHTP(A);
       if (v == 0) 
	  goto Return;
       if (v == 1) {
	  L = LIST1(LIST2(a,b));
	  goto Return; }
	
Step2: /* Initialize lists. */
       L = NIL;
       K = LIST3(A,a,b);

Step3: /* Make passes over to-do list. */
       while (K != NIL) {
	  Kp = K;
	  K = NIL;
	  while (Kp != NIL) {
	     ADV3(Kp,&B,&c,&d,&Kp);
	     e = LSIM(c,d);
	     B = IUPBHT(B,-1);
	     v = IPVCHTP(B);
	     if (v == 1)
		L = COMP(LIST2(c,e),L);
	     else if (v > 1)
		K = COMP3(B,c,e,K);
	     B = IUPTR1(B);
	     if (PORD(B) > 0)
		L = COMP(LIST2(e,e),L);
	     if (IUPVART(B) == 1) {
		v = IPVCHTP(B);
		if (v == 1)
		   L = COMP(LIST2(e,d),L);
		else if (v > 1)
		   K = COMP3(B,e,d,K); } } }

Step4: /* Sort isolating intervals. */
       LIBS(L);

Return: /* Prepare for return. */
       return(L);
}
