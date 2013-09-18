/*======================================================================
                      IPOWER(A,L; B,n)

Integer power.  

Inputs
  A   : in Z, greater than or equal to 3, odd positive.
  L   : a list (pl_1,pl_2,...,pl_kl) of the first kl prime numbers, 
        with pl_kl greater than or equal to the base 3 logarithm of A.

Outputs
  B,n : If A=B^ml for some ml >= 2 then 
          n is the least such ml and B=A^(1/n).  
        Otherwise 
          B = 0 and n = 0.
======================================================================*/
#include "saclib.h"

void IPOWER(A,L, B_,n_)
       Word A,L, *B_,*n_;
{
       Word B,Lp,N,n,t;
       /* hide Lp,N,n,t; */

Step1: /* Compute bound on n. */
       N = ILOG2(A);
       N = (7 * N) / 11;

Step2: /* Apply iroot. */
       Lp = L;
       while (Lp != NIL)
         {
         ADV(Lp,&n,&Lp);
         if (n > N)
           goto Step3;
         IROOT(A,n,&B,&t);
         if (t == 0)
           goto Return;
         }

Step3: /* Non-power. */
       B = 0;
       n = 0;

Return: /* Prepare for return. */
       *B_ = B;
       *n_ = n;
       return;
}
