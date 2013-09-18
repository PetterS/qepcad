/*======================================================================
                   Q <- IPRNEVAL(r,P,t,b)

Integral polynomial rational number evaluation

Inputs
 r : a BETA-digit, r >= 1
 P : an r-variate integral polynomial
 t : an integer 1 <= t <= r
 b : a rational number

Outputs
 Q : an r-variate rational polynomial equal to 
     P(x1,...x_{t-1},b,x_{t+1},...,x_r) Note:  Q is still represented 
     as an r-variate SACLIB polynomial!
======================================================================*/
#include "qepcad.h"

Word IPRNEVAL(BDigit r, Word P, BDigit t, Word b)
{
  Word Q,L,C,e,Cp,Pp,Qp;

  if (t < r)
  {
    Q = NIL;
    for(L = CINV(P); L != NIL; L = RED2(L)) {
      FIRST2(L,&C,&e);
      Cp = IPRNEVAL(r - 1,C,t,b);
      if (Cp != 0)
	Q = COMP2(e,Cp,Q); }
    if (Q == NIL)
      Q = 0;
  }
  else
  {
    Pp = RPFIP(r,P);
    Qp = RPEMV(r,Pp,b); /* r - 1 variable rep */
    if (Qp == 0)
      Q = 0;
    else
      Q = LIST2(0,Qp);    /* r variate rep */
  }

  return Q;
}
