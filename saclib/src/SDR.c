/*======================================================================
                      SDR(S; A,I)

System of distinct representatives.

Inputs
   S : a list (S_1,...,S_n), n >= 1, where each S_i is a set
       represented as an ordered list of beta digits.

Outputs
   A,I : either A is a list (a_1,...,a_n) of distinct representatives
         for (S_1,...,S_n) and I = (), or else A = () and I = (i_1,...,i_k)
         is a subsequence of (1,...,n) such that (S_{i_1},...,S_{i_k})
         has no system of distinct representatives.

Algorithm
   See "Combinatorial Theory" by Marshall Hall, Jr, Blaisdell Pub. Co,
   1967, pages 44-49.

Analysis
   Let m be the maximum number of elements in any of the S_i.  Then the
   computing time is dominated by m n^2.
======================================================================*/
#include "saclib.h"

void SDR(S, A_,I_)
        Word S, *A_,*I_;
{
        BDigit a,b,i,j,k,r;
        Word A,As,B,I,S1,S2,Sp,T,T1,T2,Tp1,Ts1;

Step1: /* Initialize the main loop. */
        A = NIL;
        As = NIL;
        Sp = S;
        r = 0;

Step2: /* Direct extension, S_i contains an element not already chosen
          as a representative. */

        ADV(Sp,&S1,&Sp);
        B = SDIFF(S1,As);
        if (B != NIL) {
           a = FIRST(B);
           A = COMP(a,A);
           As = LINSRT(a,As);
           goto Step8; }

Step3: /* Initialize indirect extension. */
        T1 = S1;
        Ts1 = T1;
        T = NIL;

Step4: /* Test for nonextensibility. */
        if (T1 == NIL)
           goto Step9;

Step5: /* Compute the next set T_i. */
        T2 = NIL;
        Tp1 = T1;
        do {
           ADV(Tp1,&a,&Tp1);
           i = LSRCH(a,A);
           j = r - i + 1;
           S2 = LELTI(S,j);
           T2 = SUNION(T2,S2); }
        while (Tp1 != NIL);
        T2 = SDIFF(T2,Ts1);
        Ts1 = SUNION(Ts1,T2);
        T = COMP(T1,T);
        T1 = T2;

Step6: /* Test whether T_i contains a possible representative. */
        B = SDIFF(T2,As);
        if (B == NIL)
           goto Step4;

Step7: /* Reassign representatives. */
        b = FIRST(B);
        As = LINSRT(b,As);
        do {
           ADV(T,&T1,&T);
           do {
              ADV(T1,&a,&T1);
              i = LSRCH(a,A);
              j = r - i + 1;
              S1 = LELTI(S,j);
              k = LSRCH(b,S1); }
           while (k == 0);
           SLELTI(A,i,b);
           b = a; }
        while (T != NIL);
        A = COMP(b,A);

Step8: /* Test for completion. */
        r = r + 1;
        if (Sp != NIL)
           goto Step2;
        else {
           A = INV(A);
           I = NIL;
           goto Return; }

Step9: /* Compute I. */
        I = LIST1(r + 1);
        while (Ts1 != NIL) {
           ADV(Ts1,&a,&Ts1);
           i = LSRCH(a,A);
           j = r - i + 1;
           I = LINSRT(j,I); }
        A = NIL;

Return: /* Return A and I. */
       *A_ = A;
       *I_ = I;
       return;
}
