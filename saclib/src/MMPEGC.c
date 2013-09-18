/*===========================================================================
			   MMPEGC(p,A,B; C,U,V)

Medium modulus polynomial extended greatest common divisor.

Inputs
   p : a medium prime.
 A,B : in Z/(p)[x].  A and B are in list representation.

Outputs
   C : in Z/(p)[x], C = gcd(A,B).
 U,V : in Z/(p)[x], A U + B V = C.
       If deg(A/C) > 0, then deg(V) < deg(A/C), else deg(V) = 0.
       If deg(B/C) > 0, then deg(U) < deg(B/C), else deg(U) = 0.
       If A = 0, U = 0. If B = 0, V = 0.
===========================================================================*/
#include "saclib.h"

void MMPEGC(p,A,B, C_,U_,V_)
       Word p,A,B, *C_,*U_,*V_;
{
       Word *Ap,*Bp,*Cp,*Dp,*Ep,*Up,*Vp,C,U,V,m,n;

Step1: /* Convert to array representation. */
       Ap = MAPFMUP(A);
       Bp = MAPFMUP(B);

Step2: /* Compute. */
       m = MAPDEG(Ap);
       n = MAPDEG(Bp);
       Cp = MAPGET(minm(m,n));
       Vp = MAPGET(m);
       MMAPHEG(p,Ap,Bp,Cp,Vp);
       if (A == 0) {
	  C = MUPFMAP(Cp);
	  U = 0;
	  V = MUPFMAP(Vp); }
       else {
	  Dp = MAPGET(n+MAPDEG(Vp));
	  MAPPROD(p,Bp,Vp,Dp);
	  Ep = MAPGET(maxm(MAPDEG(Cp),MAPDEG(Dp)));
	  MAPDIF(p,Cp,Dp,Ep);
	  Up = MAPGET(MAPDEG(Ep)-MAPDEG(Ap));
	  MMAPQR(p,Ep,Ap,Up);
	  C = MUPFMAP(Cp);
	  U = MUPFMAP(Up);
	  V = MUPFMAP(Vp);
	  MAPFREE(Up);
	  MAPFREE(Dp);
	  MAPFREE(Ep); }
       MAPFREE(Ap);
       MAPFREE(Bp);
       MAPFREE(Cp);
       MAPFREE(Vp);

Return: /* Prepare for return. */
       *C_ = C;
       *U_ = U;
       *V_ = V;
       return;
}
