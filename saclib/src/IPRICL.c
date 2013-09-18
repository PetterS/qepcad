/*======================================================================
                      L <- IPRICL(A)

Integral polynomial real root isolation, Collins-Loos algorithm.

Inputs
  A : an integral polynomial.

Outputs
  L : an inflectionless isolation list for A.
======================================================================*/
#include "saclib.h"

Word IPRICL(A)
       Word A;
{
       Word B,Bp,C,L,Lp,b,c,d;

Step1: /* Degree zero. */
       if (PDEG(A) == 0)
         {
         L = NIL;
         goto Return;
         }

Step2: /* Initialize. */
       B = IPPP(1,A);
       Bp = IPDMV(1,B);
       C = NIL;

Step3: /* Compute derivatives. */
       while (PDEG(B) > 1)
         {
         b = PTBCF(1,B);
         IPCPP(1,Bp,&c,&B);
         Bp = IPDMV(1,B);
         C = COMP2(b,c,C);
         }

Step4: /* Isolate roots. */
       Lp = NIL;
       do
         {
         d = IUPRB(B);
         L = IPRRII(B,Bp,d,Lp);
         if (C == NIL)
           goto Return;
         ADV2(C,&b,&c,&C);
         Bp = IPIP(1,c,B);
         B = IPINT(1,Bp,b);
         Lp = L;
         }
       while (1);

Return: /* Prepare for return. */
       return(L);
}
