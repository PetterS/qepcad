/*======================================================================
                       IMPBAA(A,B,m,n,s,t,h; p,u)

Integer multiply by power of BETA and add to array.

Inputs
   A, B : Arrays containing integers A' and B' respectively.
   m, n : The lengths of A' and B' respectively.
   s,t  : Nonzero signs associated with A' and B' respectively.
   h    : A non-negative BETA-digit.

Outputs
   p : The length of C, where C = s (BETA^h) A' + t B'.
   u : The sign of C.

Effect
   |C| replaces B' in array B, the size of which must be at
   least max(m + h, n) + 1.
======================================================================*/
#include "saclib.h"

void IMPBAA(A,B,m,n,s,t,h, p_,u_)
        Word *A,*B,m,n,s,t,h,*p_,*u_;
{
        Word b,c,i,p,q,r,u;

Step1: /* A' = 0. */
        if (m == 0) {
           p = n;
           u = t;
           goto Return; }

Step2: /* B' = 0. */
        if (n == 0) {
           p = m + h;
           u = s;
           for (i = 0; i < h; i++)
              B[i] = 0;
           for (i = 0; i < m; i++)
              B[i+h] = A[i];
           goto Return; }

Step3: /* Branch on signs */
	if (s != t) 
	   goto Step9;

Step4: /* Same signs. Estimate length of result, determine its sign. */
	p = maxm(n,m + h);
	u = s;

Step5: /* n <= h. */
	if (n <= h) {
	   for (i = n; i< h; i++)
	      B[i] = 0;
	   for (i = h; i < p; i++)
	      B[i] = A[i-h];
	   goto Return; }

Step6: /* Add with carry. */
	q = minm(n,m + h);
	c = 0;
	for (i = h; i < q; i++) {
	   b = A[i-h] + B[i] + c;
	   if (b >= BETA) {
	      b = b - BETA;
	      c = 1; }
	   else
	      c = 0;
	   B[i] = b; }

Step7: /* Continue with longer summand. */
	if (q < n) {
	   i = q;
	   while (c != 0 && i < p) {
	      b = B[i] + 1;
	      if (b == BETA)
	         b = 0;
	      else
	         c = 0;
	      B[i] = b;
	      i = i + 1; } }
	else if (n < p) {
           i = q;
           while (c != 0 && i < p) {
	      b = A[i-h] + 1;
	      if (b == BETA)
                 b = 0;
              else
                 c = 0;
              B[i] = b;
              i = i + 1; }
           while (i < p) {
              B[i] = A[i-h];
              i = i + 1;  } }

Step8: /* Determine length of result. Return.*/
	if (c != 0) {
	   B[p] = 1;
	   p = p + 1; }
	goto Return;

Step9: /* Opposite signs. Estimate length of result, determine its sign. */
	p = maxm(n,m + h);
        q = minm(n,m + h);
	if (m + h > n)
	   u = s;
	else if (m + h < n)
	   u = t;
	else {
	   i = p - 1;
	   do {
	      b = A[i-h] - B[i];
	      i = i - 1; }
	   while (b == 0 && i >= h);
           while (b == 0 && i >= 0) {
	      b = -B[i];
	      i = i - 1; }
	   u = signm(b);
	   if (u == 0) {
	      p = 0;
	      goto Return; }
	   if (s < 0)
	      u = -u;
	   p = i + 2;
	   q = p; }

Step10: /* Subtract with borrow. */
	c = 0;
        if (s == u) {
           r = minm(n,h);
	   for (i = 0; i < r; i++) {
	      b = -B[i] + c;
	      if (b != 0) {
	         b = b + BETA;
	         c = -1;
	         B[i] = b; } }
	   if (n < h) {
	      q = h;
	      for (i = n; i < h; i++)
	         B[i] = BETA1; }
	   for (i = h; i < q; i++) {
	      b = A[i-h] - B[i] + c;
	      if (b < 0) {
	         b = b + BETA;
	         c = -1; }
	      else
	         c = 0;
	      B[i] = b; } }
	else {
	   for (i = h; i < q; i++) {
              b = B[i] - A[i-h] + c;
              if (b < 0) {
                 b = b + BETA;
                 c = -1; }
              else
                 c = 0;
              B[i] = b; } }

Step11: /* Continue with longer summand. */
	if (m + h > n) {
           i = q;
	   while (c != 0) {
	      b = A[i-h] - 1;
	      if (b < 0)
	         b = BETA1;
	      else
	         c = 0;
	      B[i] = b;
              i = i + 1; }
           while (i < p) {
              B[i] = A[i - h];
              i = i + 1; } }
	else if (m + h < n) {
	   i = q;
	   while (c != 0) {
	      b = B[i] - 1;
	      if (b < 0)
	         b = BETA1;
	      else
	         c = 0;
	      B[i] = b;
              i = i + 1; } }

Step12: /* Determine length of result. */
	while (B[p-1] == 0)
	   p = p - 1;

Return: /* Return p and u. */
        *p_ = p;
	*u_ = u;
        return;
}
