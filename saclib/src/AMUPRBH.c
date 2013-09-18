/*======================================================================
                      AMUPRBH(M,I,A;b,B)

Algebraic module univariate polynomial root bound and homothetic 
transformation.  

Inputs
  M : an element of Z[X].  M is the minimal polynomial for a real algebraic
      number alpha.
  I : an acceptable isolating interval for alpha.
  A : an element of Z[alpha][X].

Outputs
  b : a binary rational number.  b = 2^k is a root bound for A.
  B : an element of Z(alpha)[X].  B = A(2^kX).
======================================================================*/
#include "saclib.h"

void   AMUPRBH(M,I,A, b_,B_)

       Word M,I,A;
       Word *b_,*B_;
{
       Word b,B;
       Word Is,B1,B2,v1,v2;

Step1: /* Initialize. */
       b = LIST2(1,1);
       B = A;
       v1 = 1;
       v2 = 1;
       Is = I;

Step2: /* Check for positive roots outside the unit circle. */
       if (v1 != 0)
         {
         B1 = AMUPTR1(B);
         AMUPVARIR(M,Is,B1,&v1,&Is);
         v1 = v1 + PORD(B1);
         }

Step3: /* Check for negative roots outside the unit circle. */
       if (v1 == 0 && v2 != 0)
         {
         B2 = AMUPTR1(AMUPNT(B));
         AMUPVARIR(M,Is,B2,&v2,&Is);
         v2 = v2 + PORD(B2);
         }

Step4: /* Root bound test and homothetic transformation. */
       if (v1 == 0 && v2 == 0)
         goto Return;
       else
         {
         b = RNPROD(b,RNINT(2));
         B = AMUPBHT(B,1);
         goto Step2;
         }

Return:
       *b_ = b;
       *B_ = B;
       return;
}
