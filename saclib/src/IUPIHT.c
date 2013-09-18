/*======================================================================
                      B <- IUPIHT(A,n)

Integral univariate polynomial integer homothetic transformation.

Inputs
  A : in Z[X], non-zero.
  n : in Z, non-zero.

Outputs
  B : in Z[X], the primitive part of A(nx).
======================================================================*/
#include "saclib.h"

Word IUPIHT(A,n)
       Word A,n;
{
       Word B,M,c,s;
       /* hide c,s; */

Step1: /* Compute. */
       M = PMON(n,1);
       B = IPGSUB(1,A,1,LIST1(M));
       IPSCPP(1,B,&s,&c,&B);

Return: /* Prepare for return. */
       return(B);
}
