/*=======================================================================
                             AGIQHQ(A; q,h)

Array Gaussian integer quadrant and half quadrant.

Input
   A : a nonzero first quadrant Gaussian integer in array representation.

Outputs
   q : 1,2,3 or 4, the quadrant of A.  (Each quadrant includes the 
       half-axis that is clockwise adjacent to it.)
   h : 1 or 2, the half-quadrant of A.  (In each quadrant,
       half-quadrant 1 is clockwise to the right of half-quadrant 2.)
=======================================================================*/
#include "saclib.h"

void AGIQHQ(A, q_,h_)
	BDigit **A,*q_,*h_;
{
	BDigit *A1,*A2;
	BDigit h,i,m,n,q,s,t,u;

Step1: /* A is on a coordinate axis. */
	A1 = A[0];
	A2 = A[1];
	s = A1[0];
	t = A2[0];
	if (s == 0) {
	   h = 1;
	   if (t > 0)
	      q = 2;
	   else
	      q = 4;
	   goto Return; }
	if (t == 0) {
	   h = 1;
	   if (s > 0)
	      q = 1;
	   else
	      q = 3;
	   goto Return; }

Step2: /* Determine quadrant. */
	if (s > 0) {
	   if (t > 0)
	      q = 1;
	   else
	      q = 4; }
	else {
	   if (t > 0)
	      q = 2;
	   else
	      q = 3; }

Step3: /* Determine half-quadrant. */
	m = A1[1];
	n = A2[1];
	if (m > n)
	   u = 1;
	else if (m < n)
	   u = 2;
	else {
	   i = m + 1;
	   while (i >= 2 && A1[i] == A2[i])
	      i = i - 1;
	   if (i == 1) {
	      h = 2;
	      goto Return; }
	   else {
	      if (A1[i] > A2[i])
	         u = 1;
	      else
	         u = 2; } }
	if (u == 1) {
	   if (q == 1 || q == 3)
	      h = 1;
	   else
	      h = 2; }
	else {
	   if (q == 2 || q == 4)
	      h = 1;
	   else
	      h = 2; }

Return: /* Return q and h. */
	*q_ = q;
	*h_ = h;
	return;
}
