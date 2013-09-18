/*======================================================================
		SIPIIS(A1,I1,t1,A2,I2,t2; J1,J2,s)

Software interval polynomial isolating interval separation.

Inputs
   A1, A2 : software interval polynomials of positive degrees and
            the same precision.
   I1, I2 : isolating logarithmic binary rational intervals for
            real roots alpha1 and alpha2 of A1 and A2 respectively.
            Each is either open and standard or one-point.
   t1, t2 : the trends of alpha1 and alpha2 respectively.

Outputs
   J1, J2 : J_i is an isolating logarithmic binary rational interval
            for alpha_i that is either open and standard or one-point
            and is a subinterval of I_i.
   s      : if s = -1, J1 < J2; if s = +1, J1 > J2.  In either of
            these cases, J1 and J2 share an endpoint only if both
            are open.  Otherwise s = 0, in which case these conditions
            do not hold, but neither J1 nor J2 could be further refined
            using p-precision arithmetic, where p is the common
            precision of A1 and A2.
======================================================================*/
#include "saclib.h"

void SIPIIS(A1,I1,t1,A2,I2,t2, J1_,J2_,s_)
	BDigit *A1;
	Word I1;
	BDigit t1,*A2;
	Word I2;
	BDigit t2,*J1_,*J2_,*s_;
{
	BDigit *F,p,s,t,u,w1,w2;
	Word f,J1,J2;

Step1: /* Initialize. */
	p = A1[3];
	J1 = I1;
	J2 = I2;
	if (LBRIW(J1) == 0)
	   w1 = BETA1;
	else
	   w1 = - LSILW(J1);
	if (LBRIW(J2) == 0)
	   w2 = BETA1;
	else
	   w2 = - LSILW(J2);
	F = GETARRAY(p + 3);

Step2: /* Refinement step. */
	u = LBRNCOMP(SECOND(J1),FIRST(J2));
	if (u < 0 || (u == 0 && LBRNCOMP(FIRST(J1),FIRST(J2)) < 0 && w1 != BETA1 && w2 != BETA1)) {
	   s = -1;
	   goto Step3; }
	u = LBRNCOMP(SECOND(J2),FIRST(J1));
	if (u < 0 || (u == 0 && LBRNCOMP(FIRST(J2),FIRST(J1)) < 0 && w1 != BETA1 && w2 != BETA1)) {
           s = +1;
           goto Step3; }
	if (w1 <= w2) {
	   if (w1 == BETA1) {
	      s = 0;
	      goto Step3; }
	   f = LSIM(FIRST(J1),SECOND(J1));
	   t = LBRNFEC(f,p,F);
	   if (t == 0) {
	      s = 0;
	      goto Step3; }
	   t = SIPES(A1,F);
	   if (t == NIL) {
	      s = 0;
	      goto Step3; }
	   if (t == 0) {
	      J1 = LIST2(f,f);
	      w1 = BETA1; }
	   else if (t == t1) 
	      J1 = LIST2(FIRST(J1),f);
	   else
	      J1 = LIST2(f,SECOND(J1));
	   w1 = w1 + 1; }
	else {
           f = LSIM(FIRST(J2),SECOND(J2));
           t = LBRNFEC(f,p,F);
	   if (t == 0) {
	      s = 0;
	      goto Step3; }
           t = SIPES(A2,F);
           if (t == NIL) {
              s = 0;
              goto Step3; }
           if (t == t2) 
              J2 = LIST2(FIRST(J2),f);
           else
              J2 = LIST2(f,SECOND(J2)); 
           w2 = w2 + 1; }
	goto Step2;

Step3: /* Free array F. */
	FREEARRAY(F);

Return: /* Return J1, J2 and s. */
	*J1_ = J1;
	*J2_ = J2;
	*s_ = s;
	return;
}
