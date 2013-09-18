/*======================================================================
                      IBPRRIOAP(M,I,B,k; L,t)

Integral bivariate polynomial real root isolation over an algebraic point

Inputs
   M : the minimal integral polynomial of an algebraic number
       \alpha.
   I : an open standard logarithmic isolating interval for \alpha.
   B : a bivariate polynomial such that B(alpha,y) is squarefree
   k : if k is NIL, only root isolation is performed.  Otherwise, k
       is the target precision of refinement - i.e. we try to refine
       isolating intervals to a width of 1/2^k.
Outputs
   L : If t = 0, L is a list  (I_1,...,I_m)
       of strongly disjoint intervals, each of which has
       logarithmic binary rational endpoints and is either open
       or one-point, and that are isolating intervals for the
       real roots of B(alpha,y).
   t : 0, 1 or 2.  If t = 1, the program failed to produce an
       isolation list L because of exponent limitation.  If t = 2, 
       the failure was due to mantissa limitation.
======================================================================*/
#include "lift2d.h"

void IBPRRIOAP(Word M,Word I,Word B,Word k, Word *L_,BDigit *t_)
{
        Word L,CFP,Bp,Ls,Lp;
	BDigit t,n,n1,n2,np,u,s,e,i,j,t1,tc,c;
	ieee F1,F2;
	double p,w1,w2;
	interval *A,K,*Q,*HICFP,J;

Step1: /* Convert the isolating interval for \alpha to a
          hardware interval. */
	L = NIL;
	LBRNIEEEE(FIRST(I), &t,&F1,&n1);
	if (t != 0)
	   goto Return;
	w1 = F1.num;
	LBRNIEEEE(SECOND(I), &t,&F2,&n2);
        if (t != 0)
           goto Return;
	w2 = F2.num;
	np = MIN(n1,n2);

Step2: /* Convert the minimal polynomial to a hardware interval
          polynomial and refine the hardware interval. */
	FPCATCH();
	IUPHIP(M,&A,&t);
	if (t == 0) {
	   t = 1;
	   goto Return; }
	n = PDEG(M);
	t = HIPFES(n,A,w2);
	if (FPCHECK() == 1) {
	   t = 1;
	   goto Return; }
	if (t == NIL) {
	   t = 2;
	   goto Return; }
	u = 0;
	while (u == 0 && np > 0) {
	   p = (w1 + w2) / 2.0;
	   s = HIPFES(n,A,p);
	   if ((FPCHECK() == 1) || (s == NIL))
	      u = 1;
	   else if (s == t)
	      w2 = p;
	   else if (s == -t)
	      w1 = p;
	   else {
	      w1 = p;
	      w2 = p; }
	   np = np - 1; }
	K.left = w1;
	K.right = w2;

Step3: /* Isolate the roots of B(alpha,y) */
	/* Get hardware interval array to store B(alpha,y) (init to zero) */
	Q = GETHIPARRAY(PDEG(B));
	for(i = 0; i < PDEG(B) + 1; i++)
	  IHI(0,&(Q[i]),&t); /* this can't fail! */

	/* Compute B(alpha,y) and store in Q */
	for(Bp = B; Bp != NIL; Bp = RED2(Bp)) {
	  FIRST2(Bp,&e,&CFP);
	  IUPHIP(CFP,&HICFP,&c);
	  Q[e] = HIPIEVAL(PDEG(CFP),HICFP,K); }

	/* Check leading coefficient */
	s = HISIGN(Q[PDEG(B)]);
	if (s == NIL) {
	  t = 3;
	  goto Return; }
	
	/* get trend of first root */
	if (PDEG(B) % 2 == 0 && s == 1 || PDEG(B) % 2 == 1 && s == -1)
	  t1 = -1;
	else
	  t1 = 1;

	/* Isolate the roots of B(alpha,y) */
	HIPRRID(PDEG(B),Q, &L,&t);
	if (t != 0)
	  goto Return;

 Step4: /* Refine roots? */
	if (k == NIL)
	  goto Return;
	Ls = NIL;
	for(Lp = L, tc = t1; Lp != NIL; Lp = RED(Lp), tc *= -1)
	{
	  LBRIHI(FIRST(Lp),&J,&t); /* Can this fail? */ 
	  if (LBRNCOMP(FIRST(FIRST(Lp)),SECOND(FIRST(Lp))) != 0) {
	    /* Open interval! */
	    j = -LSILW(FIRST(Lp));
	    HIPIR(PDEG(B),Q,J,tc,j,k,&J,&j);
	    Ls = COMP(HILBRI(J),Ls); }
	  else {
	    /* 1-Point interval! */
	    Ls = COMP(FIRST(Lp),Ls); }
	}
	L = CINV(Ls);
	t = 0;
	  
Return: /* Return L and t. */
	*L_ = L;
	*t_ = t;
	return;
}
