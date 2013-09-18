/*======================================================================
                           s <- HIPFES(n,A,a)

Hardware interval polynomial floating point evaluation of sign.

Inputs
   n : a BETA-digit.
   A : in HI[X]. A is of degree n.
   a : a double.

Output
   s : s = sign(A(a)) if this can be determined using floating-
       point arithmetic with directed rounding.  Otherwise s = NIL.

Warning
   HIPFES does not test for exponent overflow or underflow.

Remark
   Step 1 computes a lower bound for A(a); Step 3 computes an
   upper bound for A(a) if the lower bound is <= 0.  In each
   of these steps A(a) is evaluated as B(-a), where B(x) = A(-x),
   in case a < 0.
======================================================================*/
#include "saclib.h"

Word HIPFES(n,A,a)
       BDigit n;
       interval A[];
       double a;
{
       Word s;
       BDigit i,t;
       double c,d,e;

Step1: /* Compute lower bound for A(a). */
       rounddown();
       c = a;
       if (c > 0) {
         d = A[n].left;
         for (i=n-1;i>=0;i--) {
           d = d * c;
           d = d + A[i].left; } }
       else {
	 c = -c;
	 if (EVEN(n)) {
	   d = A[n].left;
           t = 1; }
	 else {
           d = -A[n].right;
           t = -1; }
	 for (i=n-1;i>=0;i--) {
           d = d * c;
	   t = -t;
	   if (t == 1)
             d = d + A[i].left;
	   else
             d = d - A[i].right; } }

Step2: /* Lower bound positive? */
       if (d > 0) {
         s = 1;
         goto Return; }

Step3: /* Compute upper bound for A(a). */
       roundup();
       c = a;
       if (c > 0) {
         e = A[n].right;
         for (i=n-1;i>=0;i--) {
           e = e * c;
           e = e + A[i].right; } }
       else {
	 c = -c;
	 if (EVEN(n)) {
	   e = A[n].right;
           t = 1; }
	 else {
	   e = -A[n].left;
           t = -1; }
	 for (i=n-1;i>=0;i--) {
           e = e * c;
	   t = -t;
	   if (t == 1)
             e = e + A[i].right;
	   else
             e = e - A[i].left; } }

Step4: /* Upper bound negative? */
       if (e < 0) {
         s = -1;
         goto Return; }

Step5: /* Both bounds zero? */
       if (d == 0 && e == 0)
         s = 0;
       else
         s = NIL;

Return: /* Prepare for return. */
        return(s);
}
