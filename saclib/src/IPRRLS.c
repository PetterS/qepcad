/*======================================================================
                      IPRRLS(A1,A2,L1,L2; Ls1,Ls2)

Integral polynomial real root list separation.

Inputs
  A1,A2 : in Z[X], with no multiple real roots and with no common real roots.
  L1,L2 : lists of isolating intervals for some or all of the real roots
          of A1 and A2, respectively.  The intervals in L1 and L2 have
          binary rational endpoints, and are either left-open and
          right-closed or one-point intervals. Let
          L1 = (I_{1,1},...,I_{1,r_1}), L2=(I_{2,1},...,I_{2,r_2}).
          Then I_{1,1}  <  I_{1,2}  <  ... <  I_{1,r_1}
          and  I_{2,1}  <  I_{2,2} <  ... <  I_{2,r_2}.

Outputs
  Ls1,Ls2 : Ls1 = (Is_{1,1},...,Is_{1,r_1}) and
            Ls2 = (Is_{2,1},...,Is_{2,r_2}),
	    where Is_{i,j} is a binary rational subinterval of I_{i,j}
	    containing the root of Ai in I_{i,j}.  Each Is_{1,j} is strongly
	    disjoint from each Is_{2,j}.
======================================================================*/
#include "saclib.h"

void IPRRLS(A1,A2,L1,L2, Ls1_,Ls2_)
       Word A1,A2,L1,L2, *Ls1_,*Ls2_;
{
       Word I1,I2,Lp1,Lp2,Ls1,Ls2,s;
       /* hide Lp1,Lp2,s; */

Step1: /* Initialize. */
       if (L1 == NIL || L2 == NIL)
         {
         Ls1 = L1;
         Ls2 = L2;
         goto Return;
         }
       ADV(L1,&I1,&Lp1);
       Ls1 = NIL;
       ADV(L2,&I2,&Lp2);
       Ls2 = NIL;

Step2: /* Refine and merge. */
       do
         {
         IPRRS(A1,A2,I1,I2,&I1,&I2,&s);
         if (s < 0)
           {
           Ls1 = COMP(I1,Ls1);
           if (Lp1 != NIL)
             ADV(Lp1,&I1,&Lp1);
           else
             I1 = 0;
           }
         else
           {
           Ls2 = COMP(I2,Ls2);
           if (Lp2 != NIL)
             ADV(Lp2,&I2,&Lp2);
           else
             I2 = 0;
           }
         }
       while (!(I1 == 0 || I2 == 0));

Step3: /* Finish. */
       if (I1 == 0)
         {
         Ls2 = COMP(I2,Ls2);
         while (Lp2 != NIL)
           {
           ADV(Lp2,&I2,&Lp2);
           Ls2 = COMP(I2,Ls2);
           }
         }
       else
         {
         Ls1 = COMP(I1,Ls1);
         while (Lp1 != NIL)
           {
           ADV(Lp1,&I1,&Lp1);
           Ls1 = COMP(I1,Ls1);
           }
         }
       Ls1 = INV(Ls1);
       Ls2 = INV(Ls2);

Return: /* Prepare for return. */
       *Ls1_ = Ls1;
       *Ls2_ = Ls2;
       return;
}
