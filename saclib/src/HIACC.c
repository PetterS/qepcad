/*======================================================================
				n <- HIACC(I)

Hardware interval accuracy.

Input
   I : a hardware interval.

Output
   n : a beta digit.  If I contains zero then n = 0.  If I < 0 then
       n is the same as for -I.  Assume I = [a,b], a > 0.  If b = a,
       then n = 53.  Otherwise, Let d = b - a, q = d / a.  Then n is
       is the least integer such that 2^{-n-1} <= q.
======================================================================*/
#include "saclib.h"

BDigit HIACC(I)
	interval I;
{
	BDigit n;
	double a,b,d,q,t;
	ieee Q;
	ieee_rep qb;
	unsigned e;
	int eb;

Step1: /* Reduce to the case I = [a,b], a > 0. */
	a = I.left;
	b = I.right;
	if (a > 0)
	   goto Step2;
	else if (b < 0) {
 	   t = a;
	   a = -b;
	   b = -t;
	   goto Step2; }
	else {
	   n = 0;
	   goto Return; }

Step2: /* Compute n. */
	rounddown();
	if (a == b) {
	   n = 53;
           goto Return; }
	d = b - a;
	if (d > a) {
	   n = 0;
	   goto Return; }
	q = d / a;
	Q.num = q;
	qb = Q.rep;
	e = qb.exp;
	eb = (int)e;
	n = 1023 - eb;

Return: /* Return n. */
	return(n);
}
