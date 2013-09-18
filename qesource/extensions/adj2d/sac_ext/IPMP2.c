/*==========================================================================
                           C <- IPMP2(r,A,h)

Integral polynomial multiplication by power of 2.

Inputs
  r : a BETA-digit, r > 0, the number of variables;
  A : in Z[X1,...,Xr].
  h : a non-negative BETA-integer.

Outputs
  C : in Z[X1,...,Xr], C = 2^h * B.
==========================================================================*/
#include "sac_ext.h"

Word IPMP2(Word r, Word A, Word h)
{
       Word Ap,C,e,a,rp;

Step1: /* Special Cases. */
       if (A == 0 || h == 0) { 
         C = A;  
         goto Return; }

Step2: /* r = 1. */
       Ap = A; C = NIL;
       if (r == 1) { 
	 do { 
	   ADV2(Ap,&e,&a,&Ap);  
	   C = COMP2( IMP2(a,h) , e, C );
	 } while( Ap != NIL );
	 C = INV(C);
         goto Return; }

Step3: /* General case. */  
       rp = r - 1;
       do { 
	 ADV2(Ap,&e,&a,&Ap);  
	 C = COMP2( IPMP2(rp,a,h) , e, C );
       } while( Ap != NIL );
       C = INV(C);

Return: /* Prepare for return. */
       return C;
}
