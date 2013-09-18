/*=====================================================================
                         DLINIT(p,n; F,G,A,B,C)

Discrete logarithm initialization of tables.

Inputs
   p : a prime beta digit.
   n : a beta digit, n >= 1, such that p^n is a beta digit.

Outputs
   F : A monic irreducible polynomial of degree n over Z_p in array 
       representation defining a field GF(p^n).
   G : A polynomial over Z_p in array representation that is a
       generator of GF(p^n).
   A : an array of q = p^n beta digits.  A[0] = 0 and for 0 < i < q,
       A[i] = (G^i)(p), where G is a generator of GF(p^n).
   B : an array of q beta digits such that B[i] = j if and only if
       A[j] = i.
   C : an array of q beta digits.  For 0 <= i < q, i is the
       discrete logarithm of some a in GF(p^n) and C[i] is the
       discrete logarithm of a + 1 in GF(p^n).

Additional effect 
       p^n - 1 is assigned to the global variable FFSIZE and
       C is assigned to the global variable FFPLUS1.
=======================================================================*/
#include "saclib.h"

void DLINIT(p,n,Fp,Gp,A,B,C)
	BDigit p,n;
	BDigit **Fp,**Gp,**A,**B,**C;
{
	BDigit a,q;
	Word F,G;

Step1: /* n = 1. */
        if (n == 1) {
	   F = LIST2(1,1);
	   *Fp = MAPFMUP(F);
	   a = PFFGEN(p);
	   *Gp = MAPFMUP(LIST2(0,a));
	   *A = PFFAP(p,a);
	   *B = INVPERM(p,*A);
	   *C = PFFAP1(p,*A,*B);
	   goto Step3; }

Step2: /* n > 1. */
        F = MPFFDP(p,n);
        *Fp = MAPFMUP(F);
        *Gp = MPFFGEN(p,*Fp);
        q = IEXP(p,n);
        *A = MPFFAP(p,*Fp,*Gp);
        *B = INVPERM(q,*A);
        *C = MPFFAP1(p,q,*A,*B);

Step3: /* Initialize global variables. */
	FFSIZE = IEXP(p,n) - 1;
	FFPLUS1 = *C;

Return: /* Return F, G, A, B and C. */
	return;
}
