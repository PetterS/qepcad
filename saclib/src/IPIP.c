/*==========================================================================
                           C <- IPIP(r,a,B)

Integral polynomial integer product.  

Inputs
   r : a BETA-digit, r >= 0, the number of variables.
   a : in Z;
   B : in Z[x_1,...,x_r].

Outputs
   C : in Z[x_1,...,x_r], C = a * B.
==========================================================================*/
#include "saclib.h"

Word IPIP(r,a,B)
       Word r,a,B;
{
       Word C,Bp,rp,e,b,c;

Step1: /* C = 0. */
       if (a == 0 || B == 0) { 
	  C = 0;  
	  goto Return; }

Step2: /* r = 0 */
       if (r == 0) { 
	  C = IPROD(a,B); 
	  goto Return; }

Step3: /* General case. */  
       Bp = B;  
       C = NIL;  
       rp = r - 1;  
       do { 
	  ADV2(Bp,&e,&b,&Bp);  
	  if (rp == 0)
	     c = IPROD(a,b);
	  else
	     c = IPIP(rp,a,b);
	  C = COMP2(c,e,C); }
       while (Bp != NIL);
       C = INV(C);

Return: /* Return C. */
       return(C);
}
