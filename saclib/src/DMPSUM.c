/*======================================================================
                      C <- DMPSUM(r,m,A,B)

Dense modular polynomial sum.

Inputs 
  r : a BETA-digit, r >= 1, the number of variables.
  A , B : in Z/(m)[X1,...Xr] dense representation.
  m : a BETA-digit.   

Outputs
  C : in Z/(m)[X1,...Xr] dense representation, C = A + B.
======================================================================*/
#include "saclib.h"

Word DMPSUM(r,m,A,B)
       Word r,m,A,B;
{
       Word Ap,Bp,C,a,b,c,e,f,i,rp;
       /* hide a,b,f,i,rp; */

Step1: /* A or B zero. */
       if (A == 0)
         {
         C = B;
         goto Return;
         }
       if (B == 0)
         {
         C = A;
         goto Return;
         }

Step2: /* General case. */
       rp = r - 1;
       if (FIRST(A) >= FIRST(B))
         {
         ADV(A,&e,&Ap);
         ADV(B,&f,&Bp);
         }
       else
         {
         ADV(B,&e,&Ap);
         ADV(A,&f,&Bp);
         }
       C = NIL;
       for (i = 1; i <= e - f; i++)
         {
         ADV(Ap,&a,&Ap);
         C = COMP(a,C);
         }
       do
         {
         ADV(Ap,&a,&Ap);
         ADV(Bp,&b,&Bp);
         if (rp == 0)
           c = MDSUM(m,a,b);
         else
           c = DMPSUM(rp,m,a,b);
         C = COMP(c,C);
         }
       while (!(Ap == NIL));

Step3: /* Finish. */
       C = INV(C);
       while (C != NIL && FIRST(C) == 0)
         {
         C = RED(C);
         e = e - 1;
         }
       if (C == NIL)
         C = 0;
       else
         C = COMP(e,C);
       goto Return;

Return: /* Prepare for return. */
       return(C);
}
