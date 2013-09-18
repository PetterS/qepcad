/*===========================================================================
		    MMAPSE(m,A,B,S,T,C; U,V)

Medium modulus array polynomial, solution of equation.

Inputs
  m : a medium BETA-digit.
  A,B,S,T : in Z/(m)[x] such that ldcf(A) is a unit, deg(T) < deg(A),
	    and A*S + B*T = 1.  A,B,S,T are in array representation.
  C : in Z/(m)[x].  C is in array representation.
  U,V : arrays large enough to hold polynomials of degrees
        max(PDEG(B)-1,PDEG(C)-PDEG(A)) and PDEG(A)-1, respectively.

Side effects
  Polynomials U' and V' in Z/(m)[x] are computed such that A*U + B*V = C,
  and deg(V) < deg(A).   U' and V' are put in U and V, respectively.
===========================================================================*/
#include "saclib.h"

void MMAPSE(m,A,B,S,T,C, U,V)
       Word m,*A,*B,*S,*T,*C, *U,*V;
{
       Word *J,*K,*P,*Q,d;

Step1: /* Initialize. */
       d = MAPDEG(T) + MAPDEG(C);
       P = MAPGET(d);
       d = MAX(d - MAPDEG(A),0);
       Q = MAPGET(d);

Step2: /* Compute. */
       MMAPPROD(m,T,C,P);
       MMAPQR(m,P,A,Q);
       MAPASSIGN(P,V);
       d = MAX(MAPDEG(C) - MAPDEG(A) + 1,MAPDEG(B));
       J = MAPGET(d-1);
       MMAPTPR(m,d,S,C,J);
       K = MAPGET(d-1);
       MMAPTPR(m,d,B,Q,K);
       MAPSUM(m,J,K,U);

Step3: /* Free arrays. */
       MAPFREE(J);
       MAPFREE(K);
       MAPFREE(P);
       MAPFREE(Q);

Return: /* Prepare for return. */
       return;
}
