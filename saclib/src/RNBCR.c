/*======================================================================
                      RNBCR(A,B; M,N,k)

Rational number binary common representation.  

Inputs
  A,B   : binary rational numbers.  
      
Outputs
  M,N,k : If A = 0 and B = 0,  then 
            M = N = k = 0.    
          If A = 0 and B /= 0, then 
            M = 0 and 
            N and k are the unique integers      
            such that B = N * 2^k with N odd.  
          If B = 0 and A /= 0, then 
            N = 0 and 
            M and k are the unique integers 
            such that A = M * 2^k with M odd.  
          If A /= 0 and B /= 0, then 
            M,N, and k are the unique integers such that 
            A = M * 2^k and  B = N * 2^k with at least one of M and N odd.
======================================================================*/
#include "saclib.h"

void RNBCR(A,B, M_,N_,k_)
       Word A,B, *M_,*N_,*k_;
{
       Word A2,B2,M,N,e1,e2,k;
       /* hide A2,B2,e1,e2,k; */

Step1: /* Express both A and B as odd integer times power of 2. */
       if (A == 0)
         M = 0;
       else
         {
         FIRST2(A,&M,&A2);
         if (A2 == 1)
           {
           e1 = IORD2(M);
           M = IDP2(M,e1);
           }
         else
           e1 = -IORD2(A2);
         }
       if (B == 0)
         {
         N = 0;
         e2 = 0;
         }
       else
         {
         FIRST2(B,&N,&B2);
         if (B2 == 1)
           {
           e2 = IORD2(N);
           N = IDP2(N,e2);
           }
         else
           e2 = -IORD2(B2);
         }

Step2: /* Obtain common power of 2. */
       if (A == 0)
         {
         k = e2;
         goto Return;
         }
       else
         if (B == 0)
           {
           k = e1;
           goto Return;
           }
       if (e1 <= e2)
         {
         N = IMP2(N,e2 - e1);
         k = e1;
         }
       else
         {
         M = IMP2(M,e1 - e2);
         k = e2;
         }

Return: /* Prepare for return. */
       *M_ = M;
       *N_ = N;
       *k_ = k;
       return;
}
