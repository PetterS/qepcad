/*===========================================================================
	  RUPFMRC(M1,M1p,m1,C1,L1,M2,M2p,m2,C2; L2,C)

Rational univariate polynomial from modular residues, with comparison.

Inputs
  M1 : in Z, M1 odd.
  M1p: in Z, M1p = floor((M1/2)^(1/2)).
  m1 : a BETA-digit, m1 = ILOG2(M1p).
  C1 : in Z/(M1)[x].
  L1 : a (possibly empty) list of rational numbers.
       Let (c_1,c_2,...,c_n) be the list of non-zero
       coefficients of C1 sorted by decreasing powers of x
       (i.e., if c_i is the coefficient of x^e in C1, and c_j
       that of x^f, then i < j iff e > f).  If L1 is non-NIL,
       then L1 = (r_1,r_2,...,r_k), with r_i = c_i (mod M1), for
       some k <= n.  Possibly, r_k = NIL, in which case, there
       is no rational number congruent to c_k modulo M1 whose
       numerator and denominator are both bounded in absolute
       value by M1p.
  M2 : in Z, M2 odd.
  M2p: in Z, M2p = floor((M2/2)^(1/2)).
  m2 : a BETA-digit, m2 = ILOG2(M2p).
  C2 : in Z/(M2)[x].

Outputs
  L2 : a (possibly empty) list of rational numbers.
       L2 satisfies conditions similar to those satisfied by L1,
       but with C1 replaced by C2.
  C : in Q[x] or NIL.  If it exists, C is the unique element of Q[x] 
      such that C1 = H_M1(C), C2 = H_M2(C) and all numerators
      and denominators of the coefficients of C are less than
      MIN( (M1/2)^(1/2), (M2/2)^(1/2) ) in absolute value.
      Otherwise, C = NIL.
===========================================================================*/
#include "saclib.h"

void RUPFMRC(M1,M1p,m1,C1,L1,M2,M2p,m2,C2, L2_,C_)
       Word M1,M1p,m1,C1,L1,M2,M2p,m2,C2, *L2_,*C_;
{
       Word C,C1p,C2p,L1p,L2,d1,d2,c1,c2,r1,r2;

Step1: /* C1 = 0 \/ C2 = 0 */
       if (C1 == 0 || C2 == 0) {
	  L2 = NIL;
	  if (C1 == C2)
	     C = 0;
	  else
	     C = NIL;
	  goto Return; }

Step2: /* Initialize. */
       L1p = L1;
       L2 = NIL;
       C = NIL;
       C1p = C1;
       C2p = C2;

Step3: /* Recover rational coefficients, if possible. */
       while (C1p != 0 || C2p != 0) {
	  PADV(C1p,&d1,&c1,&C1p);
	  PADV(C2p,&d2,&c2,&C2p);
	  if (d1 != d2) {
	     L2 = INV(L2);
	     C = NIL;
	     goto Return; }
	  if (L1p == NIL) {
	     if (ISIGNF(c1) < 0)
		c1 = ISUM(M1,c1);
	     r1 = RNFMR(M1,M1p,m1,c1); }
	  else
	     ADV(L1p,&r1,&L1p);
	  if (r1 == NIL) {
	     L2 = INV(L2);
	     C = NIL;
	     goto Return; }
	  if (ISIGNF(c2) < 0)
	     c2 = ISUM(M2,c2);
	  r2 = RNFMR(M2,M2p,m2,c2);
	  L2 = COMP(r2,L2);
	  if (EQUAL(r1,r2))
	     C = COMP2(r1,d1,C);
	  else {
	     L2 = INV(L2);
	     C = NIL;
	     goto Return; } }
       C = INV(C);
       
Return: /* Prepare for return. */
       *L2_ = L2;
       *C_ = C;
}
