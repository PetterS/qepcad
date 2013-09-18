/*======================================================================
                             IEEEROUND(F,s,d; F',t)

IEEE round.

Inputs
   F : IEEE double.
   s : in {-3,-2,-1,0,1,2,3}
       The pair (F,s) represents a number F' that is located
          more than half a unit to the left  of F if s = -3,
          exactly   half a unit to the left  of F if s = -2,
          less than half a unit to the left  of F if s = -1,
          exactly  at F if s =  0,
          less than half a unit to the right of F if s =  1,
          exactly   half a unit to the right of F if s =  2,
          more than half a unit to the right of F if s =  3.
   d  : rounding direction:
           d = -1 round down,
           d =  0 round to nearest, 
           d =  1 round up.

Outputs
   Fp : IEEE double.  Fp is obtained by rounding F to F-, F or F+,
        depending on s and the rounding mode d.
   t  : If t = 0, the program failed and F' is undefined.
        Otherwise t = 1.
======================================================================*/
#include "saclib.h"

void IEEEROUND(F,s,d,Fp_,t_)

        ieee F;
	BDigit s,d;
	ieee *Fp_;
	BDigit *t_;
{
        ieee Fp;
	BDigit t;

Step1: /* Initialize. */
       Fp = F;

Step2: /* Round down. */
       if (d == -1) {
         if (s < 0) {
	   IEEENEIGH(F,-1,&Fp,&t);
	   if (t == 0)
	      goto Return; }
         goto Return; }

Step3: /* Round up. */
       if (d == 1) {
         if (s > 0) {
	   IEEENEIGH(F,1,&Fp,&t);
	   if (t == 0)
	      goto Return; }
         goto Return; }

Step4: /* Round to nearest. */
	if (s == -3 || (s == -2 && ODD(F.rep.mant_l))) {
	   IEEENEIGH(F,-1,&Fp,&t);
	   if (t == 0)
	      goto Return; }
	else if (s ==  3 || (s ==  2 && ODD(F.rep.mant_l))) {
	   IEEENEIGH(F,1,&Fp,&t);
	   if (t == 0)
	      goto Return; }

Return: /* Return F' and t. */
        *Fp_ = Fp;
	*t_ = t;
	return;
}
