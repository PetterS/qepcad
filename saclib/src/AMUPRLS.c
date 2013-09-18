/*======================================================================
                      AMUPRLS(M,I,A1,A2,L1,L2; Ls1,Ls2)

Algebraic module univariate polynomial real root list separation.

Inputs
      M : in Z[X], the minimal polynomial of an algebraic number alpha.
      I : an acceptable isolating interval for alpha.  
  A1,A2 : in Z[alpha,X]. A1 and A2 do not have any common roots and 
          their real roots are of odd multiplicity.
  L1,L2 : strong isolation lists for the real roots of A1 and A2 resp.  
          L1 = (I1_1,...,I1_r1),
          L2 = (I2_1,...,I2_r2).
          I1_1 < I1_2 < ... < I1_r1 and I2_1 < I2_2 < ... < I2_r2.

Outputs
  Ls1,Ls2 : lists (Isi_1,...,Isi*_r1) where Isi_j is a
            binary rational subinterval of Ii_j containing the root
            of Ai in Ii_j. Each Is1_j is strongly disjoint from each
            Is2_j.
======================================================================*/
#include "saclib.h"

void AMUPRLS(M,I,A1,A2,L1,L2, Ls1_,Ls2_)
       Word M,I,A1,A2,L1,L2, *Ls1_,*Ls2_;
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
         AMUPRRS(M,I,A1,A2,I1,I2,&I1,&I2,&s);
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
