/*===========================================================================
			    IDIFA(A,m,B,n; k)

Integer difference, array version.

Inputs
  A, B: in Z, in array representation.  The array for A should be large
        enough to hold A - B.
  m, n: BETA digits, the lengths of A and B, respectively.

Output
  k : the length of A - B.

Side effects
  A - B is computed and put in A.
===========================================================================*/
#include "saclib.h"

void IDIFA(A,m,B,n, k_)
       Word *A,m,*B,n, *k_;
{
       Word c,d,i,k,r,s,t;

Step1: /* A or B zero. */
       if (ISIGNA(A,m) == 0) {
	  for (i = 0; i < n; i++)
	     A[i] = -B[i];
	  k = n;
	  goto Return; }
       if (ISIGNA(B,n) == 0) {
	  k = m;
	  goto Return; }

Step2: /* Determine signs of inputs. */
       s = ISIGNA(A,m);
       t = ISIGNA(B,n);

Step3: /* Initialize and branch on signs. */
       if (s == t)
	  goto Step6;
       else if (s < 0)
	  goto Step5;

Step4: /* A positive and B negative. */
       k = minm(m,n);
       c = 0;
       for (i = 0; i < k; i++) {
	  d = A[i] - B[i] + c;
	  if (d >= BETA) {
	     d -= BETA;
	     c = 1; }
	  else
	     c = 0;
	  A[i] = d; }
       if (m == n) {
	  if (c == 1) {
	     A[m] = 1;
	     k = m + 1; } }
       else if (m > n) {
	  while (i < m && c == 1) {
	     d = A[i] + c;
	     if (d == BETA) {
		d = 0;
		c = 1; }
	     else
		c = 0;
	     A[i] = d;
	     i++; }
	  if (c == 1) {
	     A[m] = 1;
	     k = m + 1; }
	  else
	     k = m; }
       else if (m < n) {
	  while (i < n) {
	     d = c - B[i];
	     if (d == BETA) {
		d = 0;
		c = 1; }
	     else
		c = 0;
	     A[i] = d;
	     i++; }
	  if (c == 1) {
	     A[n] = 1;
	     k = n + 1; }
	  else
	     k = n; }
       goto Return;

Step5: /* A negative and B positive. */
       k = minm(m,n);
       c = 0;
       for (i = 0; i < k; i++) {
	  d = A[i] - B[i] + c;
	  if (d <= -BETA) {
	     d += BETA;
	     c = -1; }
	  else
	     c = 0;
	  A[i] = d; }
       if (m == n) {
	  if (c == -1) {
	     A[m] = -1;
	     k = m + 1; } }
       else if (m > n) {
	  while (i < m && c == -1) {
	     d = A[i] + c;
	     if (d == -BETA) {
		A[i] = 0;
		c = -1; }
	     else
		c = 0;
	     A[i] = d;
	     i++; }
	  if (c == -1) {
	     A[m] = -1;
	     k = m + 1; }
	  else
	     k = m; }
       else if (m < n) {
	  while (i < n) {
	     d = c - B[i];
	     if (d == -BETA) {
		d = 0;
		c = -1; }
	     else
		c = 0;
	     A[i] = d;
	     i++; }
	  if (c == -1) {
	     A[n] = -1;
	     k = n + 1; }
	  else
	     k = n; }
       goto Return;

Step6: /* Same signs. */

       /* Determine sign r of A - B. */
       if (m == n) {
	  i = m;
	  do {
	     i--;
	     d = A[i] - B[i]; }
	  while (d == 0 && i > 0);
	  if (d == 0) {
	     A[0] = 0;
	     k = 0;
	     goto Return; }
	  else
	     r = SIGN(d); }
       else
	  if (m < n)
	     r = -t;
	  else
	     r = s;

       /* Compute difference. */
       k = minm(m,n);
       c = 0;
       if (r > 0)
	  for (i = 0; i < k; i++) {
	     d = A[i] - B[i] + c;
	     if (d < 0) {
		d += BETA;
		c = -1; }
	     else
		c = 0;
	     A[i] = d; }
       else
	  for (i = 0; i < k; i++) {
	     d = A[i] - B[i] + c;
	     if (d > 0) {
		d -= BETA;
		c = 1; }
	     else
		c = 0;
	     A[i] = d; }
       if (m > n) {
	  A[i] += c;
	  i++; }
       else if (m < n) {
	  A[i] = -B[i] + c;
	  i++;
	  while (i < n) {
	     A[i] = -B[i];
	     i++; } }
       i--;
       while (A[i] == 0)
	  i--;
       k = i + 1;

Return: /* Prepare for return. */
       *k_ = k;
       return;
}
