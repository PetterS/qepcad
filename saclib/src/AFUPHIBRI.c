/*======================================================================
                      AFUPHIBRI(M,I,B; L,t)

Algebraic number field univariate polynomial hardware interval basis 
real root isolation.

Inputs
   M : the minimal integral polynomial of an algebraic number
       \alpha.
   I : an open standard logarithmic isolating interval for \alpha.
   B : a non-empty list of univariate polynomials over Q(\alpha).
       B is a squarefree basis. Each element of B has its
       nonzero coefficients represented by a pair (r,a) where
       r is a rational number and a is a univariate integral 
       polynomial of degree less than n.

Outputs
   L : If t = 0, L is a a list (I_1,B_1,...,I_m,B_m).  (I_1,...,I_m)
       is a list of strongly disjoint intervals, each of which has
       logarithmic binary rational endpoints and is either open
       or one-point, and that are isolating intervals for the
       real roots of B.  I_1 < I_2 < ... < I_m and each I_i is an
       isolating interval for a root of B_i.
   t : 0, 1 or 2.  If t = 1, the program failed to produce an
       isolation list L because of exponent limitation.  If t = 2, 
       the failure was due to mantissa limitation.
======================================================================*/
#include "saclib.h"

void AFUPHIBRI(M,I,B, L_,t_)
	Word M,I,B;
	Word *L_;
	BDigit *t_;
{
	Word a1,a2,B1,B2,Bp,*D,I1,Ip,L,L1,Lp,Lp1,*N,*T,*X;
	BDigit h,i,j,k,m,n,n1,n2,np,q,r,s,s1,t,t1,u,x,i1,is3;
	interval *A,*Bp1,Is,It,*J,K,**P;
	ieee F1,F2;
	double p,w1,w2;

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
	  FREEARRAY(A);
	  t = 1;
	  goto Return; }
	if (t == NIL) {
	  FREEARRAY(A);
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
	FREEARRAY(A);

Step3: /* Convert the basis polynomials to hardware interval polynomials;
	isolate and count their roots. */
	L = NIL;
	m = LENGTH(B);
	P = GETAHIA(m);
	D = GETARRAY(m);
	r = 0;
	Bp = B;
	i = 0;
	while (Bp != NIL) {
	   ADV(Bp, &B1,&Bp);
	   AFPHIP(K,B1, &Bp1,&t);
	   n1 = PDEG(B1);
	   D[i] = n1;
	   P[i] = Bp1;
	   HIPRRID(n1,Bp1, &L1,&t);
	   if (t != 0) {
	     for(i1 = 0; i1 <= i; ++i1) {
	       FREEARRAY(P[i1]); }
	     FREEARRAY(P);
	     FREEARRAY(D);
	     L = NIL;
	     goto Return; }
	   r = r + LENGTH(L1);
	   L = COMP(L1,L);
	   i = i + 1; }
	is3 = i;
	L = INV(L);
	if (r == 0) {
	  for(i1 = 0; i1 < is3; ++i1) {
	    FREEARRAY(P[i1]); }
	  FREEARRAY(P);
	  FREEARRAY(D);
	  L = NIL;
	  goto Return;
	}

Step4: /* Convert the isolating intervals to hardware intervals; store
	their indices, trends and numbers of trailing zero bits. */

	J = GETHIPARRAY(r);
	X = GETARRAY(r);
	N = GETARRAY(r);
	T = GETARRAY(r);
	Bp = B;
	Lp = L; 
	i = 0;
	j = 0;
	while (Bp != NIL) {
	   ADV(Bp, &B1,&Bp);
	   ADV(Lp, &L1,&Lp);
	   n1 = PDEG(B1);
	   s1 = ISIGNF(PLDCF(B1));
	   if ((EVEN(n1) && s1 > 0) || (ODD(n1) && s1 < 0))
	      t1 = -1;
	   else
	      t1 = +1;
	   Lp1 = L1;
	   while (Lp1 != NIL) {
	      ADV(Lp1, &I1,&Lp1);
	      FIRST2(I1, &a1,&a2);
	      LBRNIEEEE(a1, &t,&F1,&n1);
	      if (t != 0) 
	         goto Step7;
	      LBRNIEEEE(a2, &t,&F2,&n2);
	      if (t != 0)
	         goto Step7;
	      n = MIN(n1,n2);
	      J[j].left = F1.num;
	      J[j].right = F2.num;
	      X[j] = i;
	      T[j] = t1;
	      N[j] = n;
	      t1 = - t1;
	      j = j + 1; }
	   i = i + 1; }
	   
Step5: /* Bubble-sort the isolating intervals, refining as necessary. */
     q = r;
     do {
        i = -1;
	for (j = 0; j < q - 1; j++) {
	   while (!(J[j].right < J[j+1].left) && !(J[j+1].right < J[j].left)) {
	      w1 = J[j].right - J[j].left;
	      w2 = J[j + 1].right - J[j + 1].left;
	      if (w1 > w2)
	         h = j;
	      else
	         h = j + 1;
	      if (N[h] <= 0) {
	         t = 2;
	         goto Step7; }
	      p = (J[h].right + J[h].left) / 2.0;
	      k = X[h];
	      s = HIPFES(D[k],P[k],p);
	      if (s == NIL) {
	         t = 2;
	         goto Step7; }
	      if (FPCHECK() == 1) {
	         t = 1;
	         goto Step7; }
	      if (s == T[h])
	         J[h].right = p;
	      else if (s == - T[h])
	         J[h].left = p;
	      else {
	         J[h].left = p;
	         J[h].right = p; }
	      N[h] = N[h] - 1; }
	   if (J[j + 1].right < J[j].left) {
	      K = J[j];
	      J[j] = J[j + 1];
	      J[j + 1] = K;
	      x = X[j];
	      X[j] = X[j + 1];
	      X[j + 1] = x;
	      t = T[j];
	      T[j] = T[j + 1];
	      T[j + 1] = t;
	      n = N[j];
	      N[j] = N[j + 1];
	      N[j + 1] = n;
	      i = j + 1; } }
	q = i; }
     while (q > 0);

Step6: /* Convert the isolating intervals to binary rational and
	match each with a basis polynomial. */
	L = NIL;
	for (i = r - 1; i >= 0; i--) {
	   j = X[i];
	   B1 = LELTI(B,j + 1);
	   I1 = HILBRI(J[i]);
	   L = COMP2(I1,B1,L); }
	t = 0;

Step7: /* Free arrays. */
	for(i1 = 0; i1 < is3; ++i1) {
	  FREEARRAY(P[i1]); }
	FREEARRAY(P);
	FREEARRAY(D);
	FREEARRAY(J);
	FREEARRAY(N);
	FREEARRAY(T);
	FREEARRAY(X);

Return: /* Return L and t. */
	*L_ = L;
	*t_ = t;
	return;
}
