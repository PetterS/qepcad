/*======================================================================
                      modIBPRRIOAPSF(M,I,B,p,k, J_,L_)

Integral bivariate polynomial real root isolation over an algebraic
point - software floating point version (This is modified so that it
keeps track of fail intervals.)

Inputs
   A : the minimal integral polynomial of an algebraic number
       \alpha.
   I : a logarithmic open standard isolating interval for \alpha.
   B : an integral bivariate
       polynomial of degree less than n.
   p : a positive beta integer, the precision of the software
       arithmetic to be employed.
   k : if k is NIL, only root isolation is performed.  Otherwise, k
       is the target precision of refinement - i.e. we try to refine
       isolating intervals to a width of 1/2^k.

Outputs
   J : a logarithmic open standard isolating interval for \alpha that
       is a subinterval of I, the smallest that could be obtained
       with precision p arithmetic.
   L : If L = 0 then root isolation failed, otherwise L is a list  
       (I_1,...,I_m) of strongly disjoint intervals, each of which has
       logarithmic binary rational endpoints and is either open
       or one-point, and that are isolating intervals for the
       real roots of B(alpha,y).
======================================================================*/
#include "lift2d.h"

void modIBPRRIOAPSF(Word M, Word I, Word B, Word p, Word k, BDigit *J_, BDigit *L_)
{
	BDigit *Mp,*bp,*c,i,m,n,q1,q2,S,s,t;
	Word a,b,Bp,I1,I2,J,K,L,Ls,Lp,T,Jp,Js,Ld;

Step1: /* Convert the minimal polynomial to a software interval
          polynomial. */
        n = PDEG(M);
        q1 = p + 3;
        q2 = q1 + q1;
        S = (n + 1) * q2 + 1;
        Mp = GETARRAY(S);
        IPSIP(M,p,Mp);

Step2: /* Compute the trend of \alpha. */
	b = SECOND(I);
	bp = GETARRAY(q1);
	t = LBRNFEC(b,p,bp);
	J = I;
        L = 0;
	if (t == 0) {
	   FREEARRAY(bp);
	   goto Return; }
	t = SIPES(Mp,bp);
	FREEARRAY(bp);
	if (t == NIL)
	   goto Return;

Step3: /* Refine the isolating interval for \alpha. */
        J = SIPIR(Mp,I,t,- (p * ZETA));
        FREEARRAY(Mp);

Step4: /*  Isolate the real roots of each basis polynomial. */
	L = NIL;
	m = PDEG(B);
	s = (m + 1) * q2 + 1;
	c = GETARRAY(s);
	IBPELBRISIPR(B,J,p,c);
	L = modSIPRRID(c);
	if (L == 0)
	  goto Step8;
	t = c[s - q2 + 1];
	if (EVEN(m))
	  t = -t;

Step5: /* Refine roots? */
	if (k == NIL)
	  goto Return;
	Ls = NIL;
	for(Lp = L; Lp != NIL; Lp = RED(Lp))
        { 
	  Jp = FIRST(Lp);
	  FIRST2(Jp,&a,&b);

	  /* For now I ignore the possibility that this
	     might be a "don't know" interval, and I just
	     don't try to refine such an interval. */
	  if (LBRNCOMP(a,b) == 0 || -LSILW(Jp) >= k) {
	    /* Don't Refine */
	    Ls = COMP(Jp,Ls); }
	  else {/* Refine! */
	    /***** EXACTLY ONE ROOT ***********/
	    if (THIRD(Jp) == 0) {
	      Js = SIPIR(c,Jp,t,-k);
	      Jp = LIST3(FIRST(Js),SECOND(Js),THIRD(Jp));
	      Ls = COMP(Jp,Ls); }
	    else {/***** DON'T KNOW HOW MANY ROOTS **/
	      /* This is horribly inefficient, but I'm going to
		 isolate and refine all the roots of the the 
		 derivative of B w.r.t. y over alpha, and if only 
		 one root is in (a,b), it must be my double root.
		*/
	      IBPRRIOAPSF(M,I,IPPGSD(2,IPDER(2,B,2)),p,k,&I,&Ld);
	      if (Ld != 0) {
		while(LBRNCOMP(SECOND(FIRST(Ld)),a) <= 0)
		  Ld = RED(Ld);
		if (LBRNCOMP(FIRST(FIRST(Ld)),a) >= 0 && 
		    LBRNCOMP(SECOND(FIRST(Ld)),b) <= 0 &&
		    (RED(Ld) == NIL || LBRNCOMP(FIRST(SECOND(Ld)),b) >= 0))
		  Js = FIRST(Ld); 
		Jp = LIST3(FIRST(Js),SECOND(Js),THIRD(Jp));
	      }
	      Ls = COMP(Jp,Ls);
	    }
	  }
	  
	  /* Update trend! */
	  if (THIRD(Jp) == 0)
	    t = -1*t; /* note the assumption that a "don't know" interval contains an even multiplicity of roots! */
	}
	L = CINV(Ls);

Step8: /* Free arrays. */
	FREEARRAY(c);
	  
Return: /* Return J and L. */
	*J_ = J;
	*L_ = L;
	return;
}

