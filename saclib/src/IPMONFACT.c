/*===========================================================================
                         IPMONFACT(r,A; L,Ap)

Integral polynomial monomial factors.

Inputs
  r : a BETA-digit, the number of variables, r >= 1.
  A : in Z[x_1,...,x_r], A non-zero.

Output
  L  : a list ((e_i,x_i),...,(e_j,x_j)) of the monomial factors of A with
       multiplicities, i.e., x_k^{e_k} divides A but x_k^{e_k + 1} does not,
       and e_k > 0. If (e_i,x_i) appears before (e_j,x_j) in L then i < j.
       Each x_k is represented as an element of Z[x_1,...,x_r].
  Ap : in Z[x_1,...,x_r], the quotient of A and the product of the 
       elements in L.
===========================================================================*/
#include "saclib.h"

Word IPMONFACT(r,A, L_,Ap_)
       Word r,A, *L_,*Ap_;
{
       Word L,Ap,E,e,a,i;

Step1: /* Initialize. */
       Ap = A;
       L = NIL;

Step2: /* Get highest powers of variables dividing A. */
       E = IPPVED(r,A);

Step3: /* Divide A by these powers of variables and form the output list. */
       i = r+1;
       while (E != NIL) {
	  ADV(E,&e,&E); i--;
	  if (e > 0) {
	     Ap = PDPV(r,Ap,i,e);
	     a = PMONSV(r,1,i,1);
	     L = COMP(LIST2(e,a),L); } }

Return: /* Prepare for return. */
       *L_ = L;
       *Ap_ = Ap;
       return;
}
