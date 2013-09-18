/*======================================================================
                      AMUPVARIR(M,I,A; n,J)

Algebraic module univariate polynomial variations, interval refinement.

Inputs
  M : an element of Z[X].  M is the integral minimal polynomial of a real
      algebraic number alpha.
  I : I is an acceptable isolating interval for alpha.
  A :  an element of Z[alpha][X].  A /= 0.

Outputs
  n : a BETA-digit, n = min(var(A),2).
  J : an acceptable isolating interval for alpha contained in I.
======================================================================*/
#include "saclib.h"

Word AMUPVARIR(M,I,A, n_,J_)

       Word M,I,A;
       Word *n_,*J_;
{
       Word n,J;
       Word Ap,a,e,s,t;

Step1: /* Count coefficient sign variations and stop when
          two are obtained. */
       n = 0;
       Ap = A;
       ADV2(Ap,&e,&a,&Ap);
       AMSIGNIR(M,I,a,&s,&J);
       while (Ap != NIL)
         {
         ADV2(Ap,&e,&a,&Ap);
         AMSIGNIR(M,J,a,&t,&J);
         if (s != t)
           {
           n = n + 1;
           s = t;
           if (n > 1)
             goto Return;
           }
         }

Return:
       *n_ = n;
       *J_ = J;
       return;
}
