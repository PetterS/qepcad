/*===========================================================================
                         E <- IPPVED(r,A)

Integral polynomial powers-of-variables exact divisors.

Inputs
  r : a BETA-digit, the number of variables, r >= 1.
  A : in Z[x_1,...,x_r], A non-zero.

Outputs
  E : the list (e_r,e_{r-1}...,e_1) of BETA-digits, such that
      x_i^e_i divides A but x_i^(e_i+1) does not.
===========================================================================*/
#include "saclib.h"

Word IPPVED(r,A)
       Word r,A;
{
       Word Ed,Ap,rp,E,Es,Ep,a,d;

Step1: /* r = 1. */
       Ap = A;
       if (r == 1) {
	 do {
	   d = PDEG(Ap);
	   Ap = PRED(Ap); }
	 while (Ap != 0);
	 E = LIST1(d);
	 goto Return; }

Step2: /* Initialize. */
       rp = r-1;
       d = PDEG(Ap);
       a = PLDCF(Ap);
       Es = IPPVED(rp,a);
       Ap = PRED(Ap);

Step3: /* Loop. */
       while (Ap != 0) {
	 d = PDEG(Ap);
	 a = PLDCF(Ap);
	 Ep = IPPVED(rp,a);
	 Es = VMIN(Es,Ep);
	 Ap = PRED(Ap); }
       E = COMP(d,Es);

Return: /* Prepare for return. */
       return(E);
}
