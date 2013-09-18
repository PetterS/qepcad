/*===========================================================================
		       F <- AFUPFAC(M,B)

Algebraic number field univariate polynomial factorization.

Inputs
  M : in Z[t], the minimal polynomial of an algebraic number alpha.
  B : in Q(alpha)[x].  B is squarefree and deg(B) >= 1.

Outputs
  F : a list (F_1,...,F_r) of the monic factors of F.
===========================================================================*/
#include "saclib.h"

Word AFUPFAC(M,B)

       Word M,B;
{
       Word F,Fs,Fs1,Fb1,F1,G,Bt,Sp,t;

Step1: /* deg(B) = 1. */
       if (PDEG(B) == 1) {
	  F = LIST1(AFPMON(1,M,B));
	  goto Return; }

Step2: /* Compute factors of squarefree norm. */
       AFUPSFN(M,B,&t,&Bt,&Fs);

Step3: /* Check if irreducible. */
       if (LENGTH(Fs) == 1) {
	  F = LIST1(AFPMON(1,M,B));
	  goto Return; }

Step4: /* Sort by degrees. */
       LPBSD(Fs);

Step5: /* Obtain factors of B over Q(alpha)[x]. */
       F = NIL;
       G = Bt;  
       Sp = PBIN(PMON(1,0),1,PMON(t,1),0);
       Sp = RPFIP(2,Sp);  
       Sp = AFPCR(1,Sp);
       while (RED(Fs) != NIL) {
	  ADV(Fs,&Fs1,&Fs); 
	  Fs1 = AFPFIP(1,Fs1);
	  AFUPGC(M,G,Fs1,&F1,&G,&Fb1);
	  if (t != 0)
	     F1 = AFPCMV(1,M,F1,Sp);
	  F = COMP(F1,F); }
       F1 = AFPMON(1,M,G);
       if (t != 0)
	  F1 = AFPCMV(1,M,F1,Sp);
       F = COMP(F1,F);

Return: /* Prepare for return. */
       return(F);
}
