/*===========================================================================
			   IPEXPREADR(r,V; A,t)

Integral polynomial expression read, remove terminating character.

Inputs
  r : a positive BETA-digit.
  V : a non-NIL list (x_1,...,x_r) of r distinct variables.

Outputs
  A : in Z[x_1,...,x_r].  A is read from the input stream.
  t : 1 if A is successfully read in, 0 otherwise.
===========================================================================*/
#include "saclib.h"

void IPEXPREADR(r,V, A_,t_)
       Word r,V, *A_,*t_;
{
       Word A,A1,C,t;

Step1: /* Setup. */
       t = 1;
       A = 0;

Step2: /* Read in terms. */
       do {
	  IPTERMREAD(r,V,&A1,&t);
	  if (t == 0)
	     goto Return;
	  A = IPSUM(r,A,A1);
	  C = CREADB();
	  BKSP(); }
       while (C == '+' || C  == '-');
       CREADB();

Return: /* Prepare for return. */
       *A_ = A;
       *t_ = t;
       return;
}
