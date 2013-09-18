/*======================================================================
                      M <- LBIBMS(L)

List of BETA-integers bubble-merge sort.

Inputs
  L  : an arbitrary list of BETA-integers, possibly with repetitions.

Outputs
  M  : the result of sorting  L into non-decreasing order.
       A combination of bubble-sort and merge-sort is used.
       The list L is modified to produce M.
======================================================================*/
#include "saclib.h"

Word LBIBMS(L)
       Word L;
{
       Word B,Bp,C,L1,L2,Lp,Lpp,Lppp,M,i,j,k,m,n,q,qp,r,t;
       /* hide Bp,L1,L2,Lp,Lpp,i,j,k,m,n,q,qp,r,t; */

Step1: /* Short list. */
       t = 10;
       n = LENGTH(L);
       if (n < t)
         {
         LBIBS(L);
         M = L;
         goto Return;
         }

Step2: /* Prepare for merge. */
       k = 0;
       m = 1;
       q = n;
       do
         {
         k = k + 1;
         m = m + m;
         q = q / 2;
         }
       while (!(q < t));
       r = n - m * q;
       B = NIL;
       Lp = L;
       for (i = 1; i <= m; i++)
         {
         if (i <= r)
           qp = q;
         else
           qp = q - 1;
         Lpp = Lp;
         for (j = 1; j <= qp; j++)
           Lpp = RED(Lpp);
         Lppp = RED(Lpp);
         SRED(Lpp,NIL);
         LBIBS(Lp);
         B = COMP(Lp,B);
         Lp = Lppp;
         }

Step3: /* Merge. */
       for (i = 1; i <= k; i++)
         {
         C = NIL;
         Bp = B;
         do
           {
           ADV2(Bp,&L1,&L2,&Bp);
           L1 = LBIM(L1,L2);
           C = COMP(L1,C);
           }
         while (!(Bp == NIL));
         B = C;
         }
       M = FIRST(B);

Return: /* Prepare for return. */
       return(M);
}
