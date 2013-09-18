/*=======================================================================
                         n = PTDEG(r,A)

Polynomial total degree.

Inputs
   r : a positive beta digit.
   A : a polynomial in r variables over an arbitrary domain, in
       recursive representation.

Output
   n : the total degree of A.
=======================================================================*/
#include "saclib.h"

BDigit PTDEG(r,A)
        BDigit r;
        Word A;
{
	BDigit e,m,n,rp;
	Word a,Ap;

Step1: /* A = 0. */
        if (A == 0) {
           n = 0;
           goto Return; }

Step2: /* r = 1. */
	if (r == 1) {
	   n = PDEG(A);
	   goto Return; }

Step3: /* r > 1. */
	n = 0;
        Ap = A;
        rp = r - 1;
        while (Ap != NIL) {
	   ADV2(Ap,&e,&a,&Ap);
	   m = e + PTDEG(rp,a);
	   if (m > n)
	      n = m; }

Return: /* Return n. */
        return(n);
}

