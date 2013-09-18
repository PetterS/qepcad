/*===========================================================================
			    IGCDCF(A,B; C,Ab,Bb)

Integer greatest common divisor and cofactors.  

Inputs
  A,B : in Z.

Outputs
  C   : gcd(A,B).  
  Ab  : If C = 0, then Ab = 0, otherwise Ab = A/C.
  Bb  : If C = 0, then Bb = 0, otherwise Bb = B/C.
===========================================================================*/
#include "saclib.h"

void IGCDCF(A,B, C_,Ab_,Bb_)
       Word A,B, *C_,*Ab_,*Bb_;
{
       Word Ab,Bb,C;

Step1: /* Compute. */
       C = IGCD(A,B);
       if (C == 0 || C == 1) {
	  Ab = A;
	  Bb = B; }
       else {
	  Ab = IEQ(A,C);
	  Bb = IEQ(B,C); }

Return: /* Prepare for return. */
       *C_ = C;
       *Ab_ = Ab;
       *Bb_ = Bb;
       return;
}
