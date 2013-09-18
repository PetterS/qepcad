/*======================================================================
               IPIIS(A1,A2,I1,I2,t1,t2; J1,J2,s)

Integral polynomial isolating interval separation.

Inputs
   A1,A2 : integral univariate polynomials.
   I1,I2 : standard logarithmic isolating intervals for 
           simple real roots alpha_1 and alpha_2 of A1
           and A2 respectively, alpha_1 /= alpha_2.
   t1,t2 : the trends of I1 and I2 with respect to
           A1 and A2 respectively.
Outputs
   J1,J2 : disjoint standard logarithmic subintervals
           of I1 and I2.
   s     : s = -1 if J1 < J2 and s = +1 otherwise.
======================================================================*/
#include "saclib.h"

void IPIIS(A1,A2,I1,I2,t1,t2,J1_,J2_,s_)
        Word A1,A2,I1,I2,t1,t2,*J1_,*J2_,*s_;
{
        Word a1,a2,b1,b2,c,J1,J2,r,s,u,u1,u2,w1,w2;


Step1: /* Get the interval endpoints. */

	FIRST2(I1,&a1,&b1);
        FIRST2(I2,&a2,&b2);

Step2: /* Case that the intervals are already disjoint. */

	if (LBRNCOMP(b1,a2) <= 0) {
           J1 = I1;
           J2 = I2;
           s = -1;
           goto Return; }
        else if (LBRNCOMP(b2,a1) <= 0) {
           J1 = I1;
           J2 = I2;
           s = 1;
           goto Return; }
        else
           s = 0;

Step3: /* Compute the logarithms of the interval widths. */
	if (EQUAL(a1,b1))
           w1 = -BETA;
        else
           w1 = LSILW(I1);
        if (EQUAL(a2,b2))
           w2 = -BETA;
        else
           w2 = LSILW(I2);

Step4: /* If one interval properly contains the other, bisect
	it until separation is achieved or the intervals are
	the same.  Note that if the larger interval is 
	bisected, then the smaller interval is contained in
	one of the two open halves (unless the smaller
	interval is a point. */

	while (w1 > w2 && s == 0) {
	   c = LSIM(a1,b1);
	   r = LBRNCOMP(c,a2);
	   u = IUPBRES(A1,c);
	   if (u == 0) {
	      a1 = c;
	      b1 = c;
	      if (r <= 0)
	         s = -1;
	      else
	         s = 1; }
	   else {
	      w1 = w1 - 1;
	      if (u == t1) {
	         if (r <= 0)
	            s = -1; }
	      else {
	         if (r >= 0)
	            s = 1; } } }

	while (w2 > w1 && s == 0) {
	   c = LSIM(a2,b2);
	   r = LBRNCOMP(c,a1);
	   u = IUPBRES(A2,c);
	   if (u == 0) {
	      a2 = c;
	      b2 = c;
	      if (r <= 0)
	         s = 1;
	      else
	         s = -1; }
	   else {
	      w2 = w2 - 1;
	      if (u == t2) {
	         if (r <= 0)
	            s = 1; }
	      else {
	         if ( r >= 0)
	            s = -1; } } }

Step5: /* If now the intervals are identical, bisect each 
	until separation is achieved. */

	while (s == 0) {
           c = LSIM(a1,b1);
           u1 = IUPBRES(A1,c);
           if (u1 == 0) {
              a1 = c;
              b1 = c; }
           else if (u1 == t1)
              b1 = c;
           else
              a1 = c;
           u2 = IUPBRES(A2,c);
	   if (u2 == 0) {
              a2 = c;
              b2 = c; }
           else if (u2 == t2)
              b2 = c;
           else
              a2 = c;
           if (u1 != -t1 && u2 != t2)
              s = -1;
           if (u1 != t1 && u2 != -t2)
              s = 1; }

Step6: /* Compose the output intervals. */
	J1 = LIST2(a1,b1);
        J2 = LIST2(a2,b2);

Return: /* Return J1, J2 and s. */
        *J1_ = J1;
        *J2_ = J2;
        *s_ = s;
        return;
}
