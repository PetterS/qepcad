/*===========================================================================
                         Bs <- AFUPSFBA(M,A,B)

Algebraic number field univariate polynomial squarefree basis
augmentation.

Inputs
  M : in Z[x], the minimal polynomial for an algebraic number alpha.
  A : in Q(alpha)[x],  A monic, squarefree, of positive degree.  
  B : a list (B1,...,Bs), s >= 0, of polynomials in Q(alpha)[x].
      B is a squarefree basis.

Outputs
  Bs : a list of polynomials in Q(alpha)[x], a coarsest squarefree 
       basis for (A,B1,...,Bs).
===========================================================================*/
#include "saclib.h"

Word AFUPSFBA(M,A,B)
       Word M,A,B;
{
       Word Bs;
       Word Bp,B1,Ap,C,Abp,Bb1;

Step1:
       Ap = A;
       Bp = B;
       Bs = NIL;
       while (Bp != NIL && PDEG(Ap) > 0) {
	 ADV(Bp,&B1,&Bp);
	 AFUPGC(M,Ap,B1,&C,&Abp,&Bb1);
	 if (PDEG(C) > 0)
	   Bs = COMP(C,Bs);
	 if (PDEG(Bb1) > 0)
	   Bs = COMP(Bb1,Bs);
	 Ap = Abp; }
       if (PDEG(Ap) > 0)
	 Bs = COMP(Ap,Bs);
       while (Bp != NIL) {
	 ADV(Bp,&B1,&Bp);
	 Bs = COMP(B1,Bs); }
       goto Return;

Return: /* Prepare for return. */
       return(Bs);
}
