/*===========================================================================
			       IFCL2(a; m,n)

Integer, floor and ceiling, logarithm, base 2.

Inputs
  a  : non-zero integer.

Outputs
  m, n : BETA-digits, are the floor and ceiling
         of log2(abs(a)) respectively.
===========================================================================*/
#include "saclib.h"

void IFCL2(a, m_,n_)
       Word a, *m_,*n_;
{
       Word a1,ap,b,k,m,n,t;

Step1: /* Process BETA-digits. */
       t = 0;
       if (a < BETA) {
	  a1 = a;
	  m = 0; }
       else {
	  ap = a;
	  m = -ZETA;
	  do {
	     ADV(ap,&a1,&ap);
	     m = m + ZETA;
	     if (ap != NIL && a1 != 0)
		t = 1; }
	  while (ap != NIL); }

Step2: /* Process leading digit. */
       if (a1 < 0)
	  a1 = -a1;
       k = PDLOG2(a1) - 1;
       m = m + k;
       b = (01 << k);
       if (a1 != b)
	  t = 1;

Step3: /* Finish. */
       n = m + t;

Return: /* Prepare for return. */
       *m_ = m;
       *n_ = n;
       return;
}
