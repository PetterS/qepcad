/*======================================================================
                        s <- SIPES(A,a)

Software interval polynomial evaluation of sign.

Inputs
   A : a software interval polynomial.
   a : a software floating-point number.

Output
   s : the sign of A(a), if this can be determined with floating
       point arithmetic of precision max(p,q), where p is the
       precision of A and q is the precision of a. Otherwise s = NIL.

Synopsis
   Step 4 computes a lower bound for A(a).  If the lower bound is
   positive then s = 1.  Otherwise Step 6 then computes an upper
   bound for A(a).  If the two bounds have the same sign, then that
   sign is s.  Otherwise s = NIL.  In each step, if a < 0 then A(a)
   is evaluated as B(-a) where B(x) = A(-x).
======================================================================*/
#include "saclib.h"

Word SIPES(A,a)
	Word *A,*a;
{
        BDigit c1,c2,i,n,p,q,r,t,u,v;
        BDigit *d,*e;
	Word s;

Step1: /* Get sizes. */
	n = A[0];
	p = A[3];
	q = a[2];
	r = MAX(p,q);
	c1 = p + 3;
	c2 = c1 + c1;
	t = n * c2 + 1;

Step2: /* a = 0? */
	if (a[1] == 0) {
	   s = A[2];
	   if (s != A[c1 + 2])
	      s = NIL;
	   goto Return; }

Step3: /* Get two arrays. */
	d = GETARRAY(r + 3);
        e = GETARRAY(r + 3);

Step4: /* Compute a lower bound. */
	if (a[1] > 0) {
	   u = t;
	   FCOPY(A + u,d);
	   for (i = 1; i <= n; i++) {
	      FPROD(d,a,-1,e);
	      u = u - c2;
	      FSUM(A + u,e,-1,d); } }
	else {
	   a[1] = 1;
	   u = t;
	   if (EVEN(n)) {
	      FCOPY(A + u,d);
	      v = 1; }
	   else {
	      FCOPY(A + u + c1,d);
	      d[1] = - d[1];
	      v = -1; }
	   for (i = 1; i <= n; i++) {
	      FPROD(d,a,-1,e);
	      u = u - c2;
	      v = - v;
	      if (v == 1)
	         FSUM(A + u,e,-1,d);
	      else {
	         A[u + c1 + 1] = - A[u + c1 + 1];
	         FSUM(A + u + c1,e,-1,d);
	         A[u + c1 + 1] = - A[u + c1 + 1]; } }
	   a[1] = -1; }

Step5: /* Is the lower bound positive? */
	s = d[1];
	if (s == 1) {
	   FREEARRAY(d);
	   FREEARRAY(e);
	   goto Return; }

Step6: /* Compute an upper bound. */
	if (a[1] >= 0) {
	   u = t + c1;
	   FCOPY(A + u,d);
	   for (i = 1; i <= n; i++) {
              FPROD(d,a,+1,e);
              u = u - c2;
              FSUM(A + u,e,+1,d); } }
	else {
	   a[1] = 1;
	   u = t;
	   if (EVEN(n)) {
	      FCOPY(A + u + c1,d);
	      v = 1; }
	   else {
	      FCOPY(A + u,d);
              d[1] = - d[1];
              v = -1; }
	   for (i = 1; i <= n; i++) {
              FPROD(d,a,+1,e);
	      u = u - c2;
	      v = - v;
	      if (v == 1)
	         FSUM(A + u + c1,e,+1,d);
	      else {
	         A[u + 1] = - A[u + 1];
                 FSUM(A + u,e,+1,d);
	         A[u + 1] = - A[u + 1]; } }
	   a[1] = -1; }

Step7: /* Do the two bounds agree? */
	if (s != d[1])
	   s = NIL;
	FREEARRAY(d);
        FREEARRAY(e);
	   
Return: /* Return s. */
	return(s); 
}
