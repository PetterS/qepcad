/*======================================================================
                      RPWRITE(r,A,V)

Rational polynomial write.

Inputs
  A : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.
  V : a variable list for A.

Side effects :
  A is written in the output stream in recursive format using
  the variable list V.
======================================================================*/
#include "saclib.h"

void RPWRITE(r,A,V)
     Word r,A,V;

{
  Word rp,Ap,Vp,v,e,a;

  Step1: /* r = 0 or A = 0 */
    if (r == 0 || A == 0) {
      RNWRITE(A);
      return;
    }

  Step2: /* r = 1 */
    if (r == 1) {
      v = FIRST(V);
      RUPWRITE(A,v);
      return;
    }

  Step3: /* r > 1 */
    rp = r - 1;
    Ap = A;
    Vp = CINV(V);
    ADV(Vp,&v,&Vp);
    Vp = INV(Vp);
    CWRITE('(');
    do {
      ADV2(Ap,&e,&a,&Ap);
      RPWRITE(rp,a,Vp);
      if (e > 0)
	VWRITE(v);
      if (e > 1) {
	CWRITE('^');
	AWRITE(e);
      }
      if (Ap != NIL)
	CWRITE('+');
    } while (Ap != NIL);
    CWRITE(')');
}
