/*======================================================================
                      AFUPMPR(M,I,B,J,L; Js,j)

Algebraic number field univariate polynomial minimal polynomial of a real
root.

Inputs
  M  : in Z[x], the minimal polynomial of an algebraic number alpha.  
  I  : an acceptable isolating interval for alpha.  
  J  : a Binary rational interval which is either left-open and right-closed
       or a one-point interval.
  B  : in Q(alpha)[x]. B has a unique root beta of odd multiplicity 
       in J.  
  L  : is a nonempty list (L1,...,Lt) of positive irreducible elements of
       Z[x]. Exactly one Li has beta as a root.

Outputs
  Js : a Binary rational interval. Js is a subinterval of J which is an
       isolating interval for beta as a root of Lj. Js is either left-open
       and right-closed or a one-point interval.
  j  : a BETA-digit. Lj is the unique element of L having beta as a root.
======================================================================*/
#include "saclib.h"

void AFUPMPR(M,I,B,J,L, Js_,j_)
       Word M,I,B,J,L, *Js_,*j_;
{
       Word Js,j,Bb;
       /* hide j; */

Step1: /* Compute similar polynomial in Z[alpha,x]. */
       Bb = AMPSAFP(1,B);

Step2: /* Find minimal polynomial. */
       AMUPMPR(M,I,Bb,J,L,&Js,&j);

Return: /* Prepare for return. */
       *Js_ = Js;
       *j_ = j;
       return;
}
