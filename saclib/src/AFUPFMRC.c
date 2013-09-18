/*===========================================================================
	  AFUPFMRC(Q1,Q1p,q1,C1,L1,Q2,Q2p,q2,C2; L2,C)

Algebraic number field univariate polynomial from modular residues,
with comparison.

Inputs
  Q1 : in Z,
  Q1p: in Z, Q1p = floor((Q1/2)^(1/2)).
  q1 : a BETA-digit, q1 = ILOG2(Q1p).
  C1 : in Z/(Q1)[a,y], monic, a is an algebraic number.
  L1 : a (possibly empty) list of lists of rational numbers.
       Let C1 = x^n + sum_{i=0}^{n-1}C1_i*x^i, and let
       (D_1,...,D_m) be the sublist of (C1_{n-1},...,C1_0)
       consisting of the nonzero C1_i.  Then L1 = (R_1,...,R_k),
       k <= m, where R_i is a (possible empty) list of rational
       numbers; if R_i in non-NIL, then the last element of R_i
       may be NIL.  Let D_i = sum_{j=0}^{l}d_j*a^j, and let E_i
       = (e_1,...,e_s), s <= l+1, be the sublist of
       (d_l,...,d_0) consisting of the nonzero d_j.  Then R_i =
       (r_1,...,r_t), 0 <= t <= s, where (if it exists) r_j is
       the rational number that is congruent to e_j modulo Q1
       whose numerator and denominator are both less than
       sqrt(Q1/2) in absolute value.  Possibly, r_t = NIL, in
       which case, there is no rational number that is congruent
       to e_t modulo Q1, whose numerator and denominator are
       both less than sqrt(Q1/2) in absolute value.
  Q2 : in Z.
  Q2p: in Z, Q2p = floor((Q2/2)^(1/2)).
  q2 : a BETA-digit, q2 = ILOG2(Q2p).
  C2 : in Z/(Q2)[a,y], monic.

Outputs
  C : in Q(a)[y] or NIL.  If it exists, C is the unique element of
      Q(a)[y] such that H_Q1(C) = C1, H_Q2(C) = C2, and the
      absolute values of the numerators and denominators
      appearing in the rational coefficients of C are less than
      min(sqrt(Q1/2),sqrt(Q2/2)).  Otherwise, C = NIL.
  L2: a (possibly empty) list of lists of rational numbers
      satisfying properties similar to those satisfied by the
      input L1, but with Q1, Q1p, q1, and C1 replaced by Q2,
      Q2p, q2, and C2, respectively.  If C /= NIL, then L2 = NIL.
===========================================================================*/
#include "saclib.h"

void AFUPFMRC(Q1,Q1p,q1,C1,L1,Q2,Q2p,q2,C2, L2_,C_)
       Word Q1,Q1p,q1,C1,L1,Q2,Q2p,q2,C2, *L2_,*C_;
{
       Word C,C1p,C2p,L1p,L2,R1,R2,d1,d2,c1,c2,c;

Step1: /* deg(C1) /= deg(C2) */
       if (PDEG(C1) != PDEG(C2)) {
	  L2 = NIL;
	  C = NIL;
	  goto Return; }

Step2: /* Initialize. */
       L2 = NIL;
       C = NIL;
       L1p = L1;
       C1p = PRED(C1);
       C2p = PRED(C2);

Step3: /* Recover the coefficients. */
       while (C1p != 0 && C2p != 0) {
	  PADV(C1p,&d1,&c1,&C1p);
	  PADV(C2p,&d2,&c2,&C2p);
	  if (d1 != d2) {
	     L2 = INV(L2);
	     C = NIL;
	     goto Return; }
	  if (L1p == NIL)
	     R1 = NIL;
	  else
	     ADV(L1p,&R1,&L1p);
	  RUPFMRC(Q1,Q1p,q1,c1,R1,Q2,Q2p,q2,c2, &R2,&c);
	  L2 = COMP(R2,L2);
	  if (c != NIL)
	     C = COMP2(c,d1,C);
	  else {
	     L2 = INV(L2);
	     C = NIL;
	     goto Return; } }
       C = INV(C);
       c = PMON(RNINT(1),0);
       C = PPLT(PDEG(C1),c,C);

Step5: /* Convert representation. */
       C = AFPCR(1,C);

Return: /* Prepare for return. */
       *L2_ = L2;
       *C_ = C;
       return;
}
