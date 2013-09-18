/*======================================================================
                      LDSSBR(A,b; xs,N)

Linear diophantine system solution, based on Rosser ideas.

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

void LDSSBR(A,b, xs_,N_)
       Word A,b, *xs_,*N_;
{
       Word B,C,C1,C2,Cp,N,b1,m,n,s,xs;
       /* hide C2,Cp,N,b1,m,n,s,xs; */

Step1: /* Initialize. */
       n = LENGTH(A);
       m = LENGTH(b);

Step2: /* Adjoin identity matrix to A and zero vector to -b. */
       C = MIAIM(A);
       B = VIAZ(VINEG(b),n);

Step3: /* Sort columns of c. */
       C = MINNCT(C);
       C = MICS(C);

Step4: /* Pivot row zero. */
       C1 = FIRST(C);
       if (FIRST(C1) == 0)
         goto Step6;

Step5: /* Eliminate pivot row. */
       do
         {
         B = VIERED(B,C1,1);
         C = RED(C);
         if (C == NIL)
           s = 0;
         else
           {
           C2 = FIRST(C);
           s = FIRST(C2);
           if (s != 0)
             {
             C1 = VIERED(C1,C2,1);
             C = MICINS(C,C1);
             C1 = C2;
             }
           }
         }
       while (s != 0);
       n = n - 1;

Step6: /* System inconsistent. */
       ADV(B,&b1,&B);
       if (b1 != 0)
         {
         xs = NIL;
         N = NIL;
         goto Return;
         }

Step7: /* Remove pivot row. */
       Cp = C;
       while (Cp != NIL)
         {
         C1 = FIRST(Cp);
         C1 = RED(C1);
         SFIRST(Cp,C1);
         Cp = RED(Cp);
         }
       m = m - 1;

Step8: /* Finished. */
       if (m > 0)
         {
         if (n > 0)
           goto Step3;
         else
           goto Step6;
         }
       xs = B;
       N = C;

Return: /* Prepare for return. */
       *xs_ = xs;
       *N_ = N;
       return;
}
