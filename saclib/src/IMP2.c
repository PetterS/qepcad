/*===========================================================================
			       B <- IMP2(A,h)

Integer multiplication by power of 2.

Inputs
  A : in Z.
  h : a non-negative BETA-integer.

Outputs
  B : A * (2^h).
===========================================================================*/
#include "saclib.h"

Word IMP2(A,h)
       Word A,h;
{
       Word a,a0,a1,b,bp,D,d,i,k,kp,M,n,q,s;
       Word Ap,B,*Bp,*Bpp,Bh[FIXED];

Step1: /* A = 0 or h = 0. */
       if (A == 0 || h == 0) {
	  B = A;
	  goto Return; }

Step2: /* h = q * ZETA + k. */
       if (h < ZETA) {
	  q = 0;
	  k = h; }
       else {
	  q = h / ZETA;
	  k = h - q * ZETA; }

Step3: /* Mask. */
       kp = ZETA - k;
       M = ~(~0 << kp);

Step4: /* A non-zero BETA-digit. Shift by k bits. */
       if (A < BETA) {
	  if (A > 0) {
	     b = (A & M) << k;  /* shifted kp low order bits. */
	     bp = A >> kp; }    /* k high order bits. */
	  else {
	     a = -A;
	     b = -((a & M) << k);
	     bp = -(a >> kp); }
	  if (bp == 0)
	     B = b;
	  else
	     B = COMP(b,COMP(bp,NIL));
	  goto Step14; }

Step5: /* Initialize. */
       Bp = Bh;
       D = FIXED - 1;

Step6: /*  A double precision. Shift by k bits. */
       if (RED2(A) == NIL) {
	  FIRST2(A,&a0,&a1);
	  if (a1 < 0) {
	     a0 = -a0;
	     a1 = -a1;
	     s = -1; }
	  else
	     s = 1;
	  Bp[0] = (a0 & M) << k;
	  bp = a0 >> kp;
	  Bp[1] = ((a1 & M) << k) ^ bp;
	  bp = a1 >> kp;
	  if (bp == 0)
	     n = 2;
	  else {
	     Bp[2] = bp;
	     n = 3; }
	  goto Step12; }

Step7: /* Trailing zeros. Determine sign. */
       Ap = A;
       a = FIRST(Ap);
       while (a == 0) {
	  q = q + 1;
	  Ap = RED(Ap);
	  a = FIRST(Ap); }
       if (a < 0)
	  s = -1;
       else
	  s = 1;

Step8: /* Initialize for shifting. */
       n = 0;
       bp = 0;

Step9: /* Shift remaining digits by k bits. */
       if (s == -1)
	  do {
	     ADV(Ap,&a,&Ap);
	     a = -a;
	     b = a & M;
	     Bp[n] = (b << k) ^ bp;
	     bp = a >> kp;
	     n = n + 1; }
          while (Ap != NIL && n < D);
       else
	  do {
	     ADV(Ap,&a,&Ap);
	     b = a & M;
	     Bp[n] = (b << k) ^ bp;
	     bp = a >> kp;
	     n = n + 1; }
          while (Ap != NIL && n < D);

Step10: /* Allocate sufficiently large array. Resume shifting. */
       if (Ap != NIL) {
	  D = n + LENGTH(Ap) + 1;
	  Bpp = GETARRAY(D);
	  for (i = 0; i < n; i++)
	     Bpp[i] = Bp[i];
	  Bp = Bpp;
	  goto Step9; }

Step11: /* Last carry. */
       if (bp != 0) {
	  Bp[n] = bp;
	  n = n + 1; }

Step12: /* Store result in list. */
       B = IFATL(Bp,n,s);

Step13: /* Free up memory. */
       if (D >= FIXED)
	  FREEARRAY(Bp);

Step14: /* Append q BETA-zeros. */
       if (q != 0)
	  IMPB(B,q,&B,&d);

Return: /* Prepare for return. */
       return(B);
}
