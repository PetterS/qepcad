/*======================================================================
                           IHI(A; I,u)

Integer to hardware interval.

Inputs
   A : in Z

Outputs
   I : the hardware floating point interval of minimal width
       containing A.
   u : If u = 0, the program failed because of exponent overflow.
       Otherwise u = 1.
======================================================================*/
#include "saclib.h"

void IHI(A, I_,u_)
        Word A;
	interval *I_;
	BDigit *u_;
{
        BDigit t,u;
        ieee a,b;
        interval I;

Step1:  /* Round towards zero. */
        IIEEET(A,&a,&t,&u);

Step2: /* Test for overflow. */
	if (u == 0)
	   goto Return;

Step3:  /* Construct the other endpoint. */
        if (t == 0) {
           I.left = a.num;
           I.right = a.num; }
        else {
           if (a.rep.sign == 0) {
              I.left = a.num;
	      IEEENEIGH(a,1,&b,&u);
	      if (u == 0)
	         goto Return;
	      else I.right = b.num; }
           else {
              I.right = a.num;
	      IEEENEIGH(a,-1,&b,&u);
	      if (u == 0)
	         goto Return;
	      else
	         I.left = b.num; } }

Return: /* Return I and u. */
	*I_ = I;
	*u_ = u;
	return;
}
