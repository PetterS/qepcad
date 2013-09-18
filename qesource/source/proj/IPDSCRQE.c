/*===========================================================================
                      D <- IPDSCRQE(r,A)

Integral polynomial discriminant, QE version.

Inputs
  r : a BETA-digit, r > 0.
  A : in Z[X1,...,Xr], of degree greater than or equal to two in its
      main variable.

Outputs
  D : in Z[X1,...,X_{r-1}], the discriminant of A.

Note:  The method used to compute the resultant is defined by the 
       global variable PCRESALG which should have one of the following
       values:  MODULAR, SUBRES.
===========================================================================*/
#include "qepcad.h"

#include "db/CAPolicy.h"

Word IPDSCRQE(Word r, Word A)
{
       Word D;

       D = GVCAP->IPDSCR(r,A);
       goto Return;

Step1: /* Determine method to use. */
       switch (PCRESALG) {
         case MODULAR: D = IPDSCR(r,A); break;
         case SUBRES:  D = IPDSCRPRS(r,A); break; 
         case BEZOUT:  D = IPDSCRBEZ(r,A); break; }

Return: /* Prepare for return. */
       return(D);
}
