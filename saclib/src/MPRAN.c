/*======================================================================
                      A <- MPRAN(r,m,q,N)

Modular polynomial, random.

Inputs
  m : a BETA-digit, m > 0.
  q : in Q, q = q1/q2 with 0 < q1 <= q2 < BETA.
  N : a list (nr,...,n1) of non-negative BETA-digits.
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  A : in Z/(m)[X1,...,Xr], a random polynomial with deg_i(A) <= ni 
      for 1 <= i <= r.  q is the probability that any particular 
      term of A has a non-zero coefficient.
======================================================================*/
#include "saclib.h"

Word MPRAN(r,m,q,N)
       Word r,m,q,N;
{
       Word A,Np,a,d,e,n,q1,q2,qs,rp,t;
       /* hide d,e,q1,q2,qs,rp,t; */

Step1: /* Compute qls=int(q*BETA). */
       FIRST2(q,&q1,&q2);
       DQR(q1,0,q2,&qs,&t);

Step2: /* r=0. */
       if (r == 0)
         {
         d = DRANN();
         if (d < qs)
           A = MDRAN(m);
         else
           A = 0;
         goto Return;
         }

Step3: /* r > 0. */
       rp = r - 1;
       ADV(N,&n,&Np);
       A = NIL;
       for (e = 0; e <= n; e++)
         {
         if (rp == 0)
           {
           d = DRANN();
           if (d < qs)
             a = MDRAN(m);
           else
             a = 0;
           }
         else
           a = MPRAN(rp,m,q,Np);
         if (a != 0)
           A = COMP2(e,a,A);
         }
       if (A == NIL)
         A = 0;

Return: /* Prepare for return. */
       return(A);
}
