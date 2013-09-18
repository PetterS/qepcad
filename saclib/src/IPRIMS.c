/*======================================================================
                      L <- IPRIMS(A,Ap,I)

Integral polynomial real root isolation, modified Uspensky method,
standard interval.

Inputs
  A  : in Z[X], without multiple roots.
  Ap : is the derivative of A.
  I  : a standard interval.

Outputs
  L  : a list (I1,...,Ir) of isolating intervals 
       for the real roots of A in I.  
       Each interval Ij is a left open right closed interval (aj,bj) 
       with binary rational endpoints and I1 < I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word IPRIMS(A,Ap,I)
       Word A,Ap,I;
{
       Word A1,I1,Ip1,L,L1,Lp,a,a1,ap1,b,b1,bp1,c,hp,hs,k,kp;
       /* hide L,a,a1,b,b1,hs,k,kp; */

Step1: /* Degree zero. */
       if (PDEG(A) == 0)
         {
         L = NIL;
         goto Return;
         }

Step2: /* Transform A. */
       FIRST2(I,&a,&b);
       c = RNDIF(b,a);
       RNFCL2(c,&k,&kp);
       if (b == 0)
         hp = 0;
       else
         {
         hs = RNQ(b,c);
         hp = FIRST(hs);
         }
       A1 = IUPBHT(A,k);
       A1 = IUPTR(A1,hp);
       A1 = IUPNT(A1);

Step3: /* Compute roots. */
       L1 = IPRIMU(A1);

Step4: /* Transform isolation intervals. */
       Lp = NIL;
       while (L1 != NIL)
         {
         ADV(L1,&I1,&L1);
         FIRST2(I1,&a1,&b1);
         ap1 = RNPROD(a1,c);
         ap1 = RNDIF(b,ap1);
         bp1 = RNPROD(b1,c);
         bp1 = RNDIF(b,bp1);
         Ip1 = LIST2(bp1,ap1);
         Lp = COMP(Ip1,Lp);
         }

Step5: /* Convert isolating intervals. */
       L = IIC(A,Ap,I,Lp);

Return: /* Prepare for return. */
       return(L);
}
