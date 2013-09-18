/*======================================================================
                      L <- AFUPRICL(M,I,A)

Algebraic number field univariate polynomial real root isolation, 
Collins-Loos algorithm.  

Inputs
  M : in Z[x], the minimal polynomial of an algebraic number alpha.
  I : an acceptable isolating interval for alpha.  
  A : in Q(alpha)[x], A is monic and deg(A)=n.

Outputs
  L : a strong isolation list for the real roots of A.
======================================================================*/
#include "saclib.h"

Word AFUPRICL(M,I,A)
       Word M,I,A;
{
       Word Ap,As,C,L,Lp,b,d;

Step1: /* Degree zero. */
       if (PDEG(A) == 0)
         {
         L = NIL;
         goto Return;
         }

Step2: /* Initialize. */
       As = A;
       Ap = AFPDMV(1,M,A);
       C = NIL;

Step3: /* Compute derivatives. */
       while (PDEG(As) > 1)
         {
         b = PTBCF(1,As);
         C = COMP(b,C);
         As = Ap;
         Ap = AFPDMV(1,M,As);
         }

Step4: /* Isolate roots. */
       Lp = NIL;
       d = AFUPRB(M,I,A);
       do
         {
         L = AFUPRII(M,I,As,Ap,d,Lp);
         if (C == NIL)
           goto Return;
         ADV(C,&b,&C);
         Ap = As;
         As = AFPINT(1,M,Ap,b);
         Lp = L;
         }
       while (1);

Return: /* Prepare for return. */
       return(L);
}
