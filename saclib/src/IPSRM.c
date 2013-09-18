/*======================================================================
                      L <- IPSRM(A,I)

Integral polynomial strong real root isolation, modified Uspensky
method.

Inputs
  A : in Z[X], without multiple roots and with no real roots in common
      with A''.
  I : either the null list () or a standard interval or an interval
      whose positive and non-negative parts are standard.

Outputs
  L : a list (I1,...,Ir) of isolating intervals for all the real roots
      of A if I=(), or for all the real roots of A in I if I /= ().
      The intervals Ij contain no roots of A' or A'', are left-open
      and right-closed, have binary rational endpoints, and satisfy
      I1 < I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word IPSRM(A,I)
       Word A,I;
{
       Word I1,I2,L,L1,L2,a,b,n;
       /* hide L,n; */

Step1: /* Degree zero. */
       n = PDEG(A);
       if (n == 0)
         {
         L = NIL;
         goto Return;
         }

Step2: /* Compute intervals. */
       if (I == NIL)
         {
         b = IUPRB(A);
         a = RNNEG(b);
         I1 = LIST2(a,0);
         I2 = LIST2(0,b);
         }
       else
         {
         FIRST2(I,&a,&b);
         if (RNSIGN(a) >= 0)
           {
           I1 = NIL;
           I2 = I;
           }
         else
           if (RNSIGN(b) <= 0)
             {
             I1 = I;
             I2 = NIL;
             }
           else
             {
             I1 = LIST2(a,0);
             I2 = LIST2(0,b);
             }
         }

Step3: /* Compute non-positive roots. */
       if (I1 != NIL)
         L1 = IPSRMS(A,I1);
       else
         L1 = NIL;

Step4: /* Compute positive roots. */
       if (I2 != NIL)
         L2 = IPSRMS(A,I2);
       else
         L2 = NIL;

Step5: /* Concatenate. */
       L = CONC(L1,L2);

Return: /* Prepare for return. */
       return(L);
}
