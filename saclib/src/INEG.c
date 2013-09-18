/*===========================================================================
				B <- INEG(A)

Integer negation.  

Inputs
  A : in Z.

Outputs
  B : -A.
===========================================================================*/
#include "saclib.h"

Word INEG(A)
       Word A;
{
       Word Ap,B,Bp,Bpp,b;

Step1: /* A single-precision. */
       if (A < BETA) {
	  B = -A;
	  goto Return; }

Step2: /* A multiple-precision. */
       Ap = A;
       if (AVAIL == NIL)
	  GC();
       B = AVAIL;
       Bpp = B;
       do {
	  Bp = Bpp;
	  b = - FIRST(Ap);
	  Ap = RED(Ap);
	  SFIRST(Bp,b);
	  Bpp = RED(Bp);
	  if (Bpp == NIL) {
	     AVAIL = NIL;
	     GC();
	     Bpp = AVAIL; 
	     SRED(Bp,Bpp); } }
       while (Ap != NIL);
       AVAIL = Bpp;
       SRED(Bp,NIL);

Return: /* Prepare for return. */
       return(B);
}
