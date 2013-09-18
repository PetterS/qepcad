/*======================================================================
                      IPLDWR(V,A)

Integral Polynomial List Distributed Write.

\Input
  \parm{V} is a non-null list of more than $r$ variables.
  \parm{A} is a list $A_1,\ldots,A_r)$ where each $A_i$ is 
           $r$--variate integral polynomial.
======================================================================*/
#include "qepcad.h"

void IPLDWR(Word V, Word A)
{
       Word A1,P,r;

Step1: /* Write. */
       while (A != NIL)
       {
         ADV(A,&A1,&A);
         PLABELWR(A1);
         SWRITE(" = "); 
         r = SECOND(LELTI(A1,PO_LABEL));
         P = LELTI(A1,PO_POLY);
	 
	 if (LELTI(A1,PO_TYPE) == PO_POINT) {
	   SAMPLEWR(r,FIRST(P),4);
	 }
	 else {
	   IPDWRITE(r,P,V); SWRITE("\n");
	 }
       }

Return: /* Prepare for return. */
       return;
}
