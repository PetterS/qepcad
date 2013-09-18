/*======================================================================
                           RHI(a,b; I,t)

Ratio to hardware interval.

Inputs
   a : a nonzero integer.
   b : a positive integer.

Outputs
   I : If t = 1, I is a hardware interval, nearly the smallest,
       containing a / b.  Otherwise t = 0 and I is undefined
       because of exponent limitation.
   t : 0 or 1.
======================================================================*/
#include "saclib.h"

void RHI(a,b,I_,t_)
	Word a,b;
	interval *I_;
	BDigit *t_;
{
	BDigit e,e1,e2,f,g,m01,m02,m11,m12,s1,s2,t,t1,t2;
	ieee F1,F2,G1,G2;
        interval F,G,I;
	BDigit c;

Step1: /* Apply ISEM  to both a and b. */
	ISEM(a,&s1,&e1,&m11,&m01,&t1);
	ISEM(b,&s2,&e2,&m12,&m02,&t2);

Step2: /* Adjust exponents. */
	e = MAX(e1,e2);
	f = MIN(e1,e2);
	if (e - f > 2000) {
	   t = 0;
	   goto Return; }
	else
	   t = 1;
	g = (e + f) / 2;
	e1 = e1 - g + BIAS;
	e2 = e2 - g + BIAS;

Step3: /* Construct IEEE doubles. */
	F1.rep.sign = s1;
	F1.rep.exp = e1;
	F1.rep.mant_h = m11;
	F1.rep.mant_l = m01;
	G1.rep.sign = s2;
	G1.rep.exp = e2;
	G1.rep.mant_h = m12;
	G1.rep.mant_l = m02;
	if (t1 == 0)
	   F2 = F1;
	else {
	   IEEENEIGH(F1,+1,&F2,&t);
	   if (t == 0)
	      goto Return; }
	if (t2 == 0)
	   G2 = G1;
	else {
	   IEEENEIGH(G1,+1,&G2,&t);
	   if (t == 0)
	      goto Return; }

Step4: /* Divide to get endpoints. */
	F.left = F1.num;
	F.right = F2.num;
	G.left = G1.num;
	G.right = G2.num;
	FPCATCH();
	I = HIQUOT(F,G);
	if (FPCHECK() == 1) {
           t = 0;
           FPCATCH(); }

Return: /* Return I and t. */
	*I_ = I;
	*t_ = t;
	return;
}
