/*===========================================================================
			      D <- MAIPDE(r,M)

Matrix of integral polynomials determinant, exact division algorithm.

Inputs
  r : a BETA-digit, r >= 0.
  M : a square matrix over Z[x_1,...,x_r]. M is represented as a list
      of rows.

Outputs
  D : in Z[x_1,...,x_r], the determinant of M.
======================================================================*/
#include "saclib.h"

Word MAIPDE(r,M)
       Word r,M;
{
       Word D,M1,M2,Mp1,P,R,R1,R2,Rp,S,S1,S2,Ss,Ss2,i,j,t;

Step1: /* Initialize. */
       M1 = M;
       P = 0;
       t = 1;

Step2: /* Order 1 matrix. */
       if (RED(M1) == NIL) {
	  D = FIRST(FIRST(M1));
	  if (t < 0)
	     D = IPNEG(r,D);
	  goto Return; }

Step3: /* Find pivot row, if possible. */
       Mp1 = M1;
       i = 0;
       do {
	  i = i + 1;
	  ADV(Mp1,&R,&Mp1); }
       while (FIRST(R) == 0 && Mp1 != NIL);

Step4: /* No pivot row. */
       if (FIRST(R) == 0) {
	  D = 0;
	  goto Return; }

Step5: /* Update sign. */
       if (EVEN(i) == 1)
	  t = -t;

Step6: /* Compute m2. */
       ADV(R,&R1,&R);
       M2 = NIL;
       j = 0;
       do {
	  j = j + 1;
	  ADV(M1,&S,&M1);
	  if (j != i) {
	     ADV(S,&S1,&S);
	     Ss = NIL;
	     Rp = R;
	     do {
		ADV(Rp,&R2,&Rp);
		ADV(S,&S2,&S);
		Ss2 = IPDIF(r,IPPROD(r,R1,S2),IPPROD(r,S1,R2));
		if (P != 0)
		   Ss2 = IPEQ(r,Ss2,P);
		Ss = COMP(Ss2,Ss); }
	     while (Rp != NIL);
	     M2 = COMP(Ss,M2); } }
       while (M1 != NIL);

Step7: /* Prepare for next pivot step. */
       P = R1;
       M1 = M2;
       goto Step2;

Return: /* Prepare for return. */
       return(D);
}
