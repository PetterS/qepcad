/*======================================================================
                      MUPEGC(p,A,B; C,U,V)

Modular univariate polynomial extended greatest common divisor.

Inputs
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X].

Outputs
   C : in Z/(p)[X], C = gcd(A,B).
 U,V : in Z/(p)[X], AU+BV=C.
       If deg(A/C) > 0, then deg(V) < deg(A/C), else deg(V) = 0.
       If deg(B/C) > 0, then deg(U) < deg(B/C), else deg(U) = 0.
       If A = 0, U = 0. If B = 0, V = 0.
======================================================================*/
#include "saclib.h"

void MUPEGC(p,A,B, C_,U_,V_)
       Word p,A,B, *C_,*U_,*V_;
{
       Word C,D,U,V;

Step1: /* Compute. */
       MUPHEG(p,A,B,&C,&V);
       if (A == 0)
         U = 0;
       else
         {
         D = MPPROD(1,p,B,V);
         D = MPDIF(1,p,C,D);
         U = MPQ(1,p,D,A);
         }

Return: /* Prepare for return. */
       *C_ = C;
       *U_ = U;
       *V_ = V;
       return;
}
