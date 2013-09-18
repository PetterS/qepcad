/*======================================================================
                      LDSMKB(A,b; xs,N)

Linear diophantine system solution, modified Kannan and Bachem
algorithm.

Inputs
  A : an m by n matrix over Z. A is represented as a list of columns.
  b : an m-vector over Z.

Outputs
 xs : an n-vector over Z (a particular solution to Ax = b) if the
      system is consistent, the empty list otherwise.
  N : a list of n-vectors over Z (basis vectors of the solution
      module of Ax = 0) if the system is consistent, the empty list
      otherwise.

Remarks:
  A and b are modified.
======================================================================*/
#include "saclib.h"

void LDSMKB(A,b, xs_,N_)
       Word A,b, *xs_,*N_;
{
       Word B,C,C1,Cp,Cp1,Cs,Cs1,N,R,Rp,T,c,h,i,j,k,m,n,r,xs;
       /* hide C1,Cp,Cp1,Cs,N,Rp,c,h,i,j,k,m,n,r,xs; */

Step1: /* Adjoin identity matrix to A and zero vector to -b. */
       n = LENGTH(A);
       C = MIAIM(A);
       B = VIAZ(VINEG(b),n);

Step2: /* Initialize. */
       m = LENGTH(b);
       C1 = FIRST(C);
       j = 0;
       do
         {
         j = j + 1;
         ADV(C1,&c,&C1);
         }
       while (c == 0);
       R = LIST1(j);
       if (j <= m)
         r = 1;
       else
         r = 0;
       k = 1;
       if (n == 1)
         goto Step5;

Step3: /* Eliminate column k+1 and augment row-sequence. */
       Cs = REDI(C,k);
       Cs1 = FIRST(Cs);
       Cp = C;
       Rp = R;
       for (h = 1; h <= k + 1; h++)
         {
         if (h <= k)
           ADV(Rp,&i,&Rp);
         else
           i = m + n + 1;
         Cp1 = Cs1;
         j = 0;
         do
           {
           j = j + 1;
           ADV(Cp1,&c,&Cp1);
           }
         while (c == 0);
         if (j >= i)
           {
           if (j == i)
             {
             C1 = FIRST(Cp);
             VIUT(C1,Cs1,i,&C1,&Cs1);
             SFIRST(Cp,C1);
             }
           Cp = RED(Cp);
           }
         else
           {
           SFIRST(Cs,Cs1);
           C = LEROT(C,h,k + 1);
           R = LEINST(R,h - 1,j);
           if (j <= m)
             r = r + 1;
           goto Step4;
           }
         }

Step4: /* Normalize off-diagonal elements. */
       for (j = h; j >= 1; j--)
         {
         Cs = REDI(C,j - 1);
         ADV(Cs,&T,&Cp);
         Rp = REDI(R,j);
         while (Rp != NIL)
           {
           ADV(Cp,&Cp1,&Cp);
           ADV(Rp,&i,&Rp);
           T = VIERED(T,Cp1,i);
           }
         SFIRST(Cs,T);
         }
       k = k + 1;
       if (k < n)
         goto Step3;

Step5: /* Check consistency of the system. */
       for (j = 1; j <= r; j++)
         {
         ADV(C,&T,&C);
         ADV(R,&i,&R);
         B = VIERED(B,T,i);
         }
       j = 0;
       do
         {
         j = j + 1;
         ADV(B,&c,&B);
         }
       while (j != m && c == 0);

Step6: /* System consistent. */
       if (c == 0)
         {
         Cp = C;
         while (Cp != NIL)
           {
           Cp1 = FIRST(Cp);
           Cp1 = REDI(Cp1,m);
           SFIRST(Cp,Cp1);
           Cp = RED(Cp);
           }
         xs = B;
         N = C;
         goto Return;
         }

Step7: /* System inconsistent. */
       xs = NIL;
       N = NIL;

Return: /* Prepare for return. */
       *xs_ = xs;
       *N_ = N;
       return;
}
