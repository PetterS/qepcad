/*======================================================================
                      D <- MMPDMA (r,p,M)

Matrix of modular polynomials determinant, modular algorithm.

Inputs
   r : a non-negative BETA-integer.
   p : a prime BETA-integer.
   M : a square matrix over Z/(p)[x_1,...,x_r].

Outputs
   D : the determinant of M, an element of Z/(p)[x_1,...,x_r].
======================================================================*/
#include "saclib.h"

Word MMPDMA(r,p,M)
        Word r,p,M;
{
       Word a,b,B,bp,d,D,Ds,M1,M11,Mp,Ms,n,N,N1,N11,X,rp;

Step1: /* Matrix of order 1. */
        if (RED(M) == NIL) {
           D = FIRST(FIRST(M));
           goto Return; }

Step2: /* r=0. */
        if (r == 0) {
           D = MMDDET(p,M);
           goto Return; }

Step3: /* Compute degree bound. */
        n = LENGTH(M);
        Mp = M;
        N = NIL;
        do {
           ADV(Mp,&M1,&Mp);
           N1 = NIL;
           do {
              ADV(M1,&M11,&M1);
              if (M11 != 0)
                 N11 = PDEGSV(r,M11,1);
              else
                 N11 = - (BETA / n);
              N1 = COMP(N11,N1); }
           while (M1 != NIL);
           N = COMP(N1,N); }
        while (Mp != NIL);
        ASSPR(N,&X,&d);

Step4: /* Apply evaluation and interpolation. */
        a = 0;
        rp = r - 1;
        B = PINV(0,1,1);
        D = 0;
        do {
           if (a == p)
              FAIL("MMPDMA","Elements of finite field exhausted",r,p,M);
           Ms = MMPEV(r,p,M,1,a);
           Ds = MMPDMA(rp,p,Ms);
           b = MPEMV(1,p,B,a);
           bp = MDINV(p,b);
           D = MPINT(p,B,a,bp,r,D,Ds);
           X = LIST4(1,1,0,MDNEG(p,a));
           B = MPPROD(1,p,B,X);
           a = a + 1; }
        while (PDEG(B) <= d);

Return: /* Return D. */
        return(D);
}
