/*==================================================================
                          SLIWE(I; k,c,d)

Standard logarithmic interval width and endpoints.

Input
   I : an open  standard logarithmic interval.

Outputs
   k :    the negative of the logarithm of the width of I, 
          a BETA-integer.
   c, d : the integers such that I = (c / 2^k,d / 2^k).
=================================================================*/
#include "saclib.h"

void SLIWE(I, k_,c_,d_)
        Word I,*k_,*c_,*d_;
{
        Word c,c1,c2,d,k,k1,k2,u1,u2;

Step1: /* Decompose I. */
        FIRST2(I,&u1,&u2);
        if (u1 != 0) 
           FIRST2(u1,&c1,&k1);
        if (u2 != 0)
           FIRST2(u2,&c2,&k2);

Step2: /* One endpoint zero. */
        if (u1 == 0) {
           k = k2;
           d = c2;
           c = 0;
           goto Return; }
        if (u2 == 0) {
           k = k1;
           c = c1;
           d = 0;
           goto Return; }

Step3: /* Neither endpoint zero. */
        if (k1 < k2) {
           k = k2;
           d = c2;
           c = IDIF(d,1); }
        else {
           k = k1;
           c = c1;
           d = ISUM(c,1); }

Return: /* Return outputs. */
        *k_ = k;
        *c_ = c;
        *d_ = d;
        return;
}
