/*======================================================================
                      L <- IPRIMU(A)

Integral polynomial real root isolation, modified Uspensky method,
unit interval.

Inputs
  A : in Z[X], squarefree.

Outputs
  L : a list (I1,...,Ir) of isolating intervals for all the roots of A 
      in the left closed right open interval (0,1).  
      Each Ij is a pair (aj,bj) of binary rational numbers, 
      with 0 <= a1 <= b1 <= ... <= ar <= br <= 1.  
      If aj = bj then (aj,bj) represents the one-point interval.
      If aj < bj then (aj,bj) represents the open interval.
======================================================================*/
#include "saclib.h"

Word IPRIMU(A)
       Word A;
{
       Word B,B1,I,L,S,a,b,c,e,e1,t,v,v1;
       /* hide e,e1,v,v1; */

Step1: /* Initialize. */
       L = NIL;
       S = NIL;
       B = A;
       a = 0;
       b = LIST2(1,1);
       e = PORD(A);
       v = IPVCHT(B);
       t = LIST2(1,2);

Step2: /* One variation or less. */
       if (v <= 1)
         {
         if (v == 1)
           {
           I = LIST2(a,b);
           L = COMP(I,L);
           }
         if (e > 0)
           {
           I = LIST2(a,a);
           L = COMP(I,L);
           }
         goto Step5;
         }

Step3: /* Bisect. */
       B1 = IUPBHT(B,-1);
       B = IUPTR1(B1);
       c = RNSUM(a,b);
       c = RNPROD(c,t);
       e1 = e;
       v1 = IPVCHT(B1);
       e = PORD(B);
       v = IPVCHT(B);

Step4: /* STACK left half. */
       if (e1 > 0 || v1 > 0)
         {
         S = COMP2(a,c,S);
         S = COMP3(v1,e1,B1,S);
         }
       a = c;
       goto Step2;

Step5: /* Finished. */
       if (S == NIL)
         goto Return;
       ADV3(S,&v,&e,&B,&S);
       ADV2(S,&a,&b,&S);
       goto Step2;

Return: /* Prepare for return. */
       return(L);
}
