/*===========================================================================
                      R <- IPRESQE(r,A,B)

Integral polynomial resultant, QE version.

Inputs
   r : a BETA-digit, r > 0.
 A,B : in Z[X1,...,Xr], A and B non-zero, deg(A) >= deg(B).

Outputs
  R : the resultant of A and B, computed using the 
      (non-modular) subresultant prs algorithm.

Note:  The method used to compute the resultant is defined by the 
       global variable PCRESALG which should have one of the following
       values:  MODULAR, SUBRES.
===========================================================================*/
#include "qepcad.h"

#include "db/CAPolicy.h"

Word IPRESQE(Word r, Word A, Word B)
{
       Word R;

       R = GVCAP->IPRES(r,A,B);
       goto Return;

Step1: /* Determine method to use. */
       switch (PCRESALG) {
         case MODULAR: R = IPRES(r,A,B); break;
         case SUBRES:  R = IPRESPRS(r,A,B); break; 
         case BEZOUT:  R = IPRESBEZ(r,A,B); break; }

Return: /* Prepare for return. */
       return(R);
}
