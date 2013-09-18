/*======================================================================
                        D <- MAIPDM(r,M)

Matrix of integral polynomials determinant, modular algorithm.

Inputs
   r : a non-negative BETA-digit.
   M : a square matrix over Z[x_1,...,x_r], represented as a list
       of rows.

Output
   D : the determinant of M, an element of Z[x_1,...,x_r],
======================================================================*/
#include "saclib.h"

Word MAIPDM(r,M)
        Word r,M;
{
        Word b,b1,b11,bp,D,Ds,M1,M11,Mp,Ms,n,P,Q,p,pp;

Step1: /* Matrix of order 1. */
        if (RED(M) == NIL) {
           D = FIRST(FIRST(M));
           goto Return; }

Step2: /* Compute a coefficient bound. */
        n = LENGTH(M);
        Mp = M;
        b = 1;
        do {
           ADV(Mp,&M1,&Mp);
           b1 = 0;
           do {
              ADV(M1,&M11,&M1);
              if (M11 != 0) {
                 b11 = IPSUMN(r,M11);
                 b1 = ISUM(b1,b11); } }
           while (M1 != NIL);
           if (b1 == 0) {
              D = 0;
              goto Return; }
           b = IPROD(b,b1); }
        while (Mp != NIL);
        b = ILOG2(b);

Step3: /* Apply chinese remainder theorem. */
        P = LPRIME;
        Q = 1;
        bp = 0;
        D = 0;
        do {
           if (P == NIL)
              FAIL("MAIPDM","Prime list exhausted",r,M,b,bp);
           ADV(P,&p,&P);
           Ms = MAIPHM(r,p,M);
           Ds = MMPDMA(r,p,Ms);
           pp = MDINV(p,MDHOM(p,Q));
           D = IPCRA(Q,p,pp,r,D,Ds);
           Q = IDPR(Q,p);
           bp = bp + DLOG2(p); }
        while (bp < b);

Return: /* Prepare for return. */
       return(D);
}
