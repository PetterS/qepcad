/*======================================================================
                      d <- MMDDET(p,M)

Matrix of modular digits determinant.

Inputs
  p : a BETA-digit, prime.
  M : a square matrix over GF(p), represented as a list of rows.

Outputs
  d : in GF(p), the determinant of M.
======================================================================*/
#include "saclib.h"

Word MMDDET(p,M)
       Word p,M;
{
       Word M1,M2,Mp1,R,R1,R2,Rp,Rs,S,S1,S2,Ss,a,ap,d,i,j;
       /* hide Mp1,R2,Rp,S1,S2,a,ap,d,i,j; */

Step1: /* Initialize. */
       M1 = M;
       d = 1;

Step2: /* Order 1 matrix. */
       if (RED(M1) == NIL)
         {
         a = FIRST(FIRST(M1));
         d = MDPROD(p,d,a);
         goto Return;
         }

Step3: /* Find pivot row, if possible. */
       Mp1 = M1;
       i = 0;
       do
         {
         i = i + 1;
         ADV(Mp1,&R,&Mp1);
         }
       while (FIRST(R) == 0 && Mp1 != NIL);

Step4: /* No pivot row. */
       if (FIRST(R) == 0)
         {
         d = 0;
         goto Return;
         }

Step5: /* Transform pivot row. */
       ADV(R,&a,&R);
       d = MDPROD(p,d,a);
       if (EVEN(i) == 1)
         d = MDNEG(p,d);
       ap = MDINV(p,a);
       Rs = NIL;
       do
         {
         ADV(R,&R1,&R);
         R1 = MDPROD(p,R1,ap);
         Rs = COMP(R1,Rs);
         }
       while (R != NIL);
       R = INV(Rs);

Step6: /* Compute m2. */
       M2 = NIL;
       j = 0;
       do
         {
         j = j + 1;
         ADV(M1,&S,&M1);
         if (j != i)
           {
           ADV(S,&S1,&S);
           Ss = NIL;
           Rp = R;
           do
             {
             ADV(Rp,&R2,&Rp);
             ADV(S,&S2,&S);
             S2 = MDDIF(p,S2,MDPROD(p,S1,R2));
             Ss = COMP(S2,Ss);
             }
           while (Rp != NIL);
           M2 = COMP(Ss,M2);
           }
         }
       while (M1 != NIL);

Step7: /* Prepare for next pivot step. */
       M1 = M2;
       goto Step2;

Return: /* Prepare for return. */
       return(d);
}
