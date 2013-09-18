/*======================================================================
                      MUPHEG(p,A,B; C,V)

Modular univariate polynomial half-extended greatest common divisor.


Inputs
   p : a BETA-digit, prime.
 A,B : in Z/(p)[X].

Outputs
   C : in Z/(p)[X], C = gcd(A,B).
   V : in Z/(p)[X] such that there exists a polynomial U such that
       AU+BV=C. If deg(A/C) > 0, then deg(V) < deg(A/C). If deg(A/C) = 0,
       deg(V) = 0. If B = 0, V = 0.
======================================================================*/
#include "saclib.h"

void MUPHEG(p,A,B, C_,V_)
       Word p,A,B, *C_,*V_;
{
       Word A1,A2,A3,C,Q,V,V1,V2,V3,a,ap;
       /* hide a,ap; */

Step1: /* Compute remainder sequence. */
       V1 = 0;
       V2 = LIST2(0,1);
       A1 = A;
       A2 = B;
       while (A2 != 0)
         {
         MPQR(1,p,A1,A2,&Q,&A3);
         V3 = MPDIF(1,p,V1,MPPROD(1,p,Q,V2));
         A1 = A2;
         A2 = A3;
         V1 = V2;
         V2 = V3;
         }

Step2: /* Adjust ldcf. */
       if (A1 == 0)
         {
         C = 0;
         V = 0;
         goto Return;
         }
       a = PLDCF(A1);
       ap = MDINV(p,a);
       C = MPMDP(1,p,ap,A1);
       V = MPMDP(1,p,ap,V1);

Return: /* Prepare for return. */
       *C_ = C;
       *V_ = V;
       return;
}
