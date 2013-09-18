/*===========================================================================
			      C <- IPROD(A,B)

Integer product.

Inputs
  A,B : in Z.

Outputs
  C   : A * B.
===========================================================================*/
#include "saclib.h"

Word IPROD(A,B)
       Word A,B;
{
       Word c,cp,n,n1,n2,n3,o1,o2,s1,s2,w;
       Word *Ap,Ah[FIXED];
       Word *Bp,Bh[FIXED];
       Word C,*Cp,Ch[FIXEDX2],W[WORK],*Wp;

Step1: /* A or B zero. */
       if (A == 0 || B == 0) {
	  C = 0;
	  goto Return; }

Step2: /* A and B single-precision. */
       if (A < BETA && B < BETA) {
	  DPR(A,B,&cp,&c);
	  if (cp == 0)
	     C = c;
	  else
	     C = LIST2(c,cp);
	  goto Return; }

Step3: /* A or B single-precision. */
       if (A < BETA) {
	  C = IDPR(B,A);
	  goto Return; }
       if (B < BETA) {
	  C = IDPR(A,B);
	  goto Return; }

Step4: /* A and B double or triple precision. */
       if (RED2(B) == NIL) {
	  if (RED2(A) == NIL) {
	     C = IPROD2X2(A,B);
	     goto Return; }
         else
	    if (RED3(A) == NIL) {
	       C = IPROD3X2(A,B);
	       goto Return; } }
       else {
	  if (RED3(B) == NIL)
	     if (RED2(A) == NIL) {
		C = IPROD3X2(B,A);
		goto Return; }
           else
	      if (RED3(A) == NIL) {
		 C = IPROD3X3(A,B);
		 goto Return; } }

Step5: /* Copy |A|,|B| into arrays, determine lengths and signs. */
       IFLTA(A,Ah,FIXED,&Ap,&n1,&s1,&o1);
       IFLTA(B,Bh,FIXED,&Bp,&n2,&s2,&o2);
       n3 = n1 + n2;
       n = MAX(n1,n2);

Step6: /* Classical multiplication or Karatsuba. */
       if (n <= MAXCLASSICAL) {
	  Cp = Ch;
	  if (n1 >= n2)
	     IPRODA(Ap,n1,Bp,n2,Cp);
	  else
	     IPRODA(Bp,n2,Ap,n1,Cp); }
       else {
	  if (n > FIXED) {
	     Cp = GETARRAY(n3 + 1);
	     w = 2 * (n - 4 + 3 * (DLOG2(n - 3) - 1));
	     Wp = GETARRAY(w); }
	  else {
	     Cp = Ch;
	     Wp = W; }
	  CLEAR(Cp,n3 + 1);
	  if (n1 >= n2)
	     KARATSUBA(Ap,n1,Bp,n2,Cp,Wp);
	  else
	     KARATSUBA(Bp,n2,Ap,n1,Cp,Wp); }

Step7: /* Store the product in a list. */
       if (s1 == s2)
	  C = IFATL(Cp,n3,1);
       else
	  C = IFATL(Cp,n3,-1);

Step8: /* Free up memory. */
       if (n > FIXED) {
	  if (n1 > FIXED)
	     FREEARRAY(Ap);
	  if (n2 > FIXED)
	     FREEARRAY(Bp);
	  FREEARRAY(Cp);
	  FREEARRAY(Wp); }

Return: /* Prepare for return. */
       return(C);
}
