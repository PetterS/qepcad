/*======================================================================
           C <- AFPCMV(r,M,A,B)

Algebraic number field polynomial composition in main variable.

Inputs:
  r :  a BETA-integer.  r >= 0.
  M :  an element of Z[X].  M is the minimal polynomial of alpha.
  A :  an element of Q(alpha)[X1,...,Xr].
  B :  an  element of Q(alpha)[X1,...,Xr].

Outputs:
  C :  an element of Q(alpha)[X1,...,Xr].  C(X1,...,Xr) =
       A(X1,...,X_{r-1},B(X1,...,Xr)).
======================================================================*/
#include "saclib.h"

Word AFPCMV(r,M,A,B)
       Word r,M,A,B;
{
       Word C;

       Word Ap,a2,P,e1,e2,i;

Step1: /* A=0. */
       if (A == 0)
         {
         C = 0;
         goto Return;
         }

Step2: /* Apply Horner's method. */
       ADV2(A,&e1,&a2,&Ap);
       C = PINV(r - 1,a2,1);
       if (r>1) C = PCPV(r,C,1,r);
       while (Ap != NIL)
         {
         ADV2(Ap,&e2,&a2,&Ap);
         a2 = PINV(r - 1,a2,1);
         if (r>1) a2 = PCPV(r,a2,1,r);
         for (i = 1; i <= e1 - e2;i++)
           C = AFPPR(r,M,C,B);
         C = AFPSUM(r,C,a2);
         e1 = e2;
         }
       for (i = 1; i <= e1; i++)
         C = AFPPR(r,M,C,B);

Return:
       return(C);
}
