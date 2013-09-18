/*===========================================================================
			     IPCEVP(r,A; B,L)

Integral polynomial, choice of evaluation points.

Inputs
  r : a BETA-digit, r >= 1.
  A : in Z[x_1,...,x_r], non-zero and square-free in its main variable x_r.

Outputs
  L : a list (b_1,...,b_{r-1}) of BETA-digits, 
      with L as small as possible, in the reverse lexicographic order 
      in which 0 < 1 < -1 < 2 < -2 < ... , such that 
      deg_{x_r}(A(x_1,...,x_{r-1},x_r)) = deg_x(A(b_1,...,b_{r-1},x))
      and A(b_1,...,b_{r-1},x) is squarefree.
  B : in Z[x], B(x) = A(b_1,...,b_{r-1},x).
===========================================================================*/
#include "saclib.h"

void IPCEVP(r,A, B_,L_)
       Word r,A, *B_,*L_;
{
       Word Ab,At,B,C,Cp,D,E,F,L,a,at,b,e,rp;

Step1: /* Initialize. */
       rp = r - 1;
       At = A;
       L = NIL;

Step2: /* Univariate. */
       if (rp == 0) {
	  B = At;
	  goto Return; }

Step3: /* Prepare to choose b_{rp}. */
       b = 0;
       PADV(At,&e,&at,&Ab);

Step4: /* Evaluate at and Ab for x_{rp} = b_{rp}. */
       a = IPEMV(rp,at,b);
       if (a == 0)
	  goto Step6;
       C = IPEVAL(rp + 1,Ab,rp,b);
       C = PPLT(e,a,C);
       Cp = IPDMV(rp,C);
       IPGCDC(rp,C,Cp,&D,&E,&F);
       if (PDEG(D) > 0)
	  goto Step6;

Step5: /* Success. */
       L = COMP(b,L);
       rp = rp - 1;
       At = C;
       goto Step2;

Step6: /* Try again. */
       if (b > 0)
	  b = -b;
       else
	  b = 1 - b;
       goto Step4;

Return: /* Prepare for return. */
       *B_ = B;
       *L_ = L;
       return;
}
