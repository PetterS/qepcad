/*===========================================================================
			   IPTERMREAD(r,V; A,t)

Integral polynomial term read.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list of r distinct variables.
  
Outputs
  A : in Z[x_1,...,x_r], with variables in V.
  t : 1 if successful, 0 otherwise.
===========================================================================*/
#include "saclib.h"

void IPTERMREAD(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,A1,C,s,t;

Step1: /* Setup. */
       t = 1;
       A = PFBRE(r,1);

Step2: /* Read in the optional sign. */
       C = CREADB();
       if (C == '+')
	  s = 1;
       else if (C == '-')
	  s = -1;
       else {
	  s = 1;
	  BKSP(); }
       if (s == -1)
	  A = IPNEG(r,A);

Step3: /* Read in powers. */
       do {
	  IPPOWREAD(r,V,&A1,&t);
	  if (t == 0)
	     goto Return;
	  A = IPPROD(r,A,A1);
	  C = CREADB();
	  BKSP(); }
       while (DIGIT(C) || LETTER(C) || C == '(');

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
