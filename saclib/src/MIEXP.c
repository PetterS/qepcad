/*======================================================================
                      B <- MIEXP(M,A,N)

Modular integer exponentiation.  

Inputs
  M : a positive integer.  
  A : an element of Z_M.  
  N : a non-negative integer.  

Outputs
  B : A^N in Z_M.
======================================================================*/
#include "saclib.h"

Word MIEXP(M,A,N)
       Word M,A,N;
{
       Word B,Np,t;
       /* hide t; */

Step1: /* Single precision. */
       if (M < BETA && N < BETA)
         {
         B = MDEXP(M,A,N);
         goto Return;
         }

Step2: /* N less than or equal to 1. */
       if (N == 0)
         {
         B = 1;
         goto Return;
         }
       if (N == 1)
         {
         B = A;
         goto Return;
         }

Step3: /* A=0. */
       if (A == 0)
         {
         B = 0;
         goto Return;
         }

Step4: /* Recursion. */
       IDQR(N,2,&Np,&t);
       B = MIEXP(M,A,Np);
       B = MIPROD(M,B,B);
       if (t == 1)
         B = MIPROD(M,B,A);

Return: /* Prepare for return. */
       return(B);
}
