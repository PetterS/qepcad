/*======================================================================
                      L <- SIMPLIFYSYS(r,S,RC,A)

Simplify System

Inputs
 r : a positive BDigit
 S : a list of irreducible r-variate SACLIB polynomials
 RC: a (possibly empty) list of SACLIB polynomials of the form 
     A x_i + B, where A,Z \in Z and 1 <= i <= r.  No two elements of
     this list should have the same x_i.  These are the "rational
     coordinates" of the system.  RC should be NIL on the initial call
     to SIMPLIFYSYS.
  A : a QEPCAD formula representing assumptions.  Can be normalized or
      unnormalized.

Outputs
 L : a list of lists of irreducible r-variate SACLIB polynomials.  The
     union of systems in L is equivalent to S, but hopefully "simpler".
     SIMPLIFYSYS identifies rational coordinates implicit in the
     system and evaluates the system at those coordinates.

     For example:
     (2 x_1 x_3 + x_2, x_2) -- x_2=0 --> (2 x_1 x_3) --> ((x_2,x_1),(x_2,x_3))
======================================================================*/
#include "qepcad.h"

Word SIMPLIFYSYS(BDigit r, Word S, Word RC, Word A)
{
      Word L,i,Sp,P,Pp,rp,t,R,Lp, Lpi, g, Si,Sip;

Step1: /* Separate into levels */
      L = NIL;
      for(i = 1; i <= r; i++)
      L = COMP(NIL,L);
      for(Sp = S; Sp != NIL; Sp = RED(Sp))
      {
	P = FIRST(Sp);
	PSIMREP(r,P,&rp,&Pp);
	if (rp == 0) { SWRITE("Error 1 in SIMPLIFYSYS!!!\n"); }
	SLELTI(L,rp,COMP(Pp,LELTI(L,rp)));
      }
      
Step2: /* Remove duplicates */
      for(i = 1; i <= r; i++)
	SLELTI(L,i,RMDUP(LELTI(L,i)));

Step3: /* All pols are irreducible, so only one 1-level is allowed! */
      if (LENGTH(LELTI(L,1)) > 1)
      {
	L = 1;
	goto Return;
      }

Step4: /* Look for simple "sums of squares" that are unsatisfiable 
	i.e. with positive coefficients and a non-zero constant term. 
	This is assuming that factoring these pols has normalized them
	to positive leading groundfield coefficient! */
      for(Lp = L, i = 1; Lp != NIL; Lp = RED(Lp), i++)
	for(Lpi = FIRST(Lp); Lpi != NIL; Lpi = RED(Lpi))
	  if (VERIFYCONSTSIGN(i,FIRST(Lpi),1,A))
	  {
	    L = 1;
	    goto Return;
	  }
      
Step5: /* Evaluate at any rational coordinates */
      FINDRATCOORD(L,&t,&R,&g);
      if (t != 0)
      {
	/* Record the coordinate */
	RC = COMP(RVSPTSVSP(t,g,r),RC);

	/* Evaluate assumptions formula */
	Word Ap = ASSUMPTIONSRATVEVAL(A,t,R,r);
	if (Ap == FALSE) {
	  L = 1;
	  goto Return; }

	/* Evaluate each element of L at x_t = R */
	L = EVALSYS(L,t,R);
	if (L == 1)
	  goto Return;

	/* After evaluation, factoring might split the system again! */
	L = LBMIPL(L,r);
	Lp = LOSETSBF(L,r);
	L = NIL;
	while(Lp != NIL) {
	  ADV(Lp,&Si,&Lp);
	  Sip = SIMPLIFYSYS(r,Si,RC,Ap);
	  if (Sip != 1)
	    L = CCONC(Sip,L);
	}
	if (L == NIL)
	  L = 1;
	goto Return;
      }
	      
Step6: /* Prepare to return by restoring to a single list of r-variate polynomials */
	L = LBMIPL(L,r);
	L = CCONC(L,RC);
	L = LIST1(L);	

Return: /* Return! */      
      return L;
}
