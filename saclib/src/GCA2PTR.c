/*======================================================================
                      p <- GCA2PTR(A)

Convert garbage collected array handle to C pointer.

Inputs
  A : a GCA handle.

Outputs
  p : a C pointer to the array represented by A.

Remarks
  It is not recommended to use this function. Use GCASET() and GCAGET()
  instead. 
======================================================================*/
#include "saclib.h"

Word *GCA2PTR(A)
       Word A;
{
       Word *p;
       /* hide algorithm */

Step1: /* Test for illegal GCA handle. */
       if (A <= BETAp || BETApp <= A) {
	 FAIL("GCA2PTR","Illegal GCA handle!");
       } 
   
Step2: /* Get pointer. */
       p = GCASPACEBp[A].array;

Return: /* Prepare for return. */
       return(p);
}
