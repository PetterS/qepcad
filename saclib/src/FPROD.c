/*======================================================================
			FPROD(A,B,d,C)

Floating-point product.

Inputs
   A, B : floating-point numbers.
   d : a sign (rounding direction).
   C : an array large enough for the product.

Output
   C : a floating-point number approximating the product of A and B.
       Let p_1 and p_2 be the respective precisions of A and B, P
       the maximum of p_1 and p_2.  If d = -1, C is the greatest
       P-precision floating-point number less than or equal to the
       product.  If d = +1, C is the least P-precision floating-point
       number greater than or equal to the product.  If d = 0, C is
       the nearest P-precision floating-point number to the product
       (if two are equally near, the one with even mantissa is chosen).
======================================================================*/
#include "saclib.h"

void FPROD(A,B,d,C)
	Word *A,*B;
	BDigit d;
	Word *C;
{
	BDigit c2,e,f,i,j,p,P,s,sp,t;
	Word *D;

Step1: /* Product zero. */
        P = maxm(A[2],B[2]);
	if (A[1] == 0 || B[1] == 0) {
	   C[1] = 0;
	   C[2] = P;
	   goto Return; }

Step2: /* Small precisions. */
        if (A[2] == 1) {
           if (B[2] == 1) {
              FPROD1(A,B,d,C);
              goto Return;  }
           else if (B[2] == 2) {
              FPROD21(B,A,d,C);
              goto Return; }
           else goto Step3; }
        if (A[2] == 2) {
           if (B[2] == 2) {
              FPROD2(A,B,d,C);
              goto Return; }
           else if (B[2] == 1) {
              FPROD21(A,B,d,C);
              goto Return; } }

Step3: /* Compute minimum precision, exponent and sign of product. */
	f = 0;                           /* No array allocated. */
	p = minm(A[2],B[2]);
	e = A[0] + B[0];
	if (A[1] == B[1])
	   s = 1;
	else
	   s = -1;

Step4: /* Single precision multiplier. */
	if (A[2] == 1 || B[2] == 1) {
	  if (A[2] == 1)
	    IPRODA(B+3,B[2],A+3,A[2],C+2);
	  else
	    IPRODA(A+3,A[2],B+3,B[2],C+2);
	  C[1] = 0;
	  goto Step8; }

Step5: /* Compute short product. */
	if (A[2] >= B[2]) {
  	   ISPROD(A+3,A[2],B+3,B[2],C+1); }
	else
	   ISPROD(B+3,B[2],A+3,A[2],C+1);

Step6: /* Full product needed? */
       c2 = C[2];
       if (C[P+2] >= BETA2)              /* c is normalized. */
         {
         if (d == 0)
           {
           if ( BETA2 - (p - 2) <= c2 && c2 < BETA2) 
             goto Step7;
           }
         else if ( BETA - (p - 2) <= c2)
           goto Step7;
         }
       else                              /* c is not normalized. */
         {
         if (c2 >= BETA2)                /* Mask out high order bit of c2. */
           c2 = c2 - BETA2;
         if (d == 0)
           {
           if ( BETA/4 - (p - 2) <= c2 && c2 < BETA/4)
             goto Step7;
           }
         else if ( BETA2 - (p - 2) <= c2)
           goto Step7;
         }
       goto Step8;

Step7: /* Full product. */
       f = 1;                             /* Array allocated. */
       D = GETARRAY(p+P);
       IPRODA(A+3,A[2],B+3,B[2],D);
       for (i = 1; i <= P + 2; i++)
	 C[i] = D[p+i-3];

Step8: /* Normalize result. */
       if (C[P+2] < BETA2) {
	 LSHIFT1(C+1,P+2);
	 e = e - 1; }

Step9: /* Read guard digits. */
       if (C[2] > BETA2)
	 sp = 3;
       else {
	 if (C[2] == 0)
	   sp = 0;
	 else if (C[2] == BETA2)
	   sp = 2;
	 else
	   sp = 1;
	 if (sp != 1 && C[1] != 0)
	   sp = sp + 1; }

Step10: /* Determine sticky bit if needed. */
       if ((d == s && sp == 0) || (d == 0 && sp == 2)) {
	 i = 1;
	 j = 1;
	 while ((A[2+i] == 0 || B[2+j] == 0) && i + j < p) {
	   if (A[2+i] == 0)
	     i++;
	   if (B[2+j] == 0)
	     j++; }
	 if (i + j >= p)
	   t = 0;
         else
	   t = 1; }

Step11: /* Round up if needed. */
       if ((d == s && (sp != 0 || t != 0)) ||
           (d == 0 && (sp == 3 || (sp == 2 && (t != 0 || ODD(C[3])))))) {
	 i = 3;
	 while (i <= P + 2 && C[i] == BETA1) {
	   C[i] = 0;
	   i = i + 1; }
	 if (i <= P + 2) 
	   C[i] = C[i] + 1;
	 else {
	   C[P+2] = BETA2;
	   e = e + 1; } }
	
Step12: /* Store exponent, sign and precision. */
	C[0] = e;
	C[1] = s;
	C[2] = P;
	if (f != 0)
	  FREEARRAY(D);

Return: /* Return. */
	return;
}
