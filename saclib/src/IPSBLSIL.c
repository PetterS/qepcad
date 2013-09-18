/*=====================================================================
			L <- IPSBLSIL(A)

Integral polynomial squarefree basis labeled standard isolation
list.

Input
  A : A squarefree basis of integral polynomials, A =
      (A_1,...,A_m).

Output
  L : A labeled standard isolation list for the real roots
      of A.
=====================================================================*/
#include "saclib.h"

Word IPSBLSIL(A)
       Word A;
{
       Word A1,Ap,L1,L2,L;

Step1: /* For each A_i, isolate, label and merge. */
       L = NIL;
       Ap = A;
       while (Ap != NIL) {
	  ADV(Ap,&A1,&Ap);
	  L1 = IPRRID(A1);
	  L2 = ALSIL(A1,L1);
	  L = IPLSILM(L2,L);
	              }
Return: /* Return L. */
       return(L);
}
