/*======================================================================
                      IUPRC(A,B; C,R)

Integral univariate polynomial resultant and cofactor.

Inputs
  A,B : in Z[x], of positive degree.

Outputs
  R   : in Z, the resultant of A and B.
  C   : in Z[x], C is such that for some D in Z[x], A*D + B*C = R.
======================================================================*/
#include "saclib.h"

void IUPRC(A,B, C_,R_)
       Word A,B, *C_,*R_;
{
       Word As,Bs,C,Cs,I,Q,R,Rs,d,e,f,m,n,p,q;

Step1: /* Compute coefficient bound. */
       m = PDEG(A);
       n = PDEG(B);
       d = IPMAXN(1,A);
       e = IPMAXN(1,B);
       d = IEXP(d,n);
       e = IEXP(e,m);
       f = IFACTL(m + n);
       f = IPROD(e,f);
       f = IPROD(d,f);
       f = IPROD(2,f);

Step2: /* Initialize. */
       I = LPRIME;
       Q = 1;
       C = 0;
       R = 0;

Step3: /* Loop. */
       while (I != NIL) {
	  ADV(I,&p,&I);
	  As = MPHOM(1,p,A);
	  if (PDEG(As) == m) {
	     Bs = MPHOM(1,p,B);
	     if (PDEG(Bs) == n) {
		MUPRC(p,As,Bs,&Cs,&Rs);
		q = MDHOM(p,Q);
		q = MDINV(p,q);
		C = IPCRA(Q,p,q,1,C,Cs);
		R = IPCRA(Q,p,q,0,R,Rs);
		Q = IPROD(Q,p);
		if (ICOMP(Q,f) >= 0)
		   goto Return; } } }

Step4: /* Algorithm fails. */
       FAIL("IUPRC","Prime list exausted",A,B,f,Q);

Return: /* Prepare for return. */
       *C_ = C;
       *R_ = R;
       return;
}
