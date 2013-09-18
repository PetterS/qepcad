/*======================================================================
                      L <- IPRRILBRI(A,I)

Integral polynomial real root isolation in logarithmic binary rational
interval.

Inputs
  A  : in Z[X], squarefree and primitive.
  I  : an open or one-point logarithmic binary rational interval.

Outputs
  L  : a list (I1,...,Ir) of isolating intervals for the real roots
       of A in I. Each interval is an open or one-point standard
       interval in logarithmic representation. Let (a_j,b_j) denote
       the endpoints of I_j.  Then a_1 <= b_1 <= ... <= a_r <= b_r.
======================================================================*/
#include "sac_ext.h"

Word IPRRILBRI(Word A, Word I)
{
       Word i1,i2,L,L1,L2,D,d,k,h,a,b,c,i,j,j1,j2,j3,j1p,j3p;

Step1: /* I is a one point interval. */
       FIRST2(I,&i1,&i2);
       if (LBRNCOMP(i1,i2) == 0) {
	 L = NIL;
	 if (IUPLBREVAL(A,i2) == 0)
	   L = COMP(i2,L);
	 goto Return; }

Step2: /* Cover I by two adjacent standard intervals. */
       D = LBRNDIF(i2,i1);
       FIRST2(D,&d,&k);
       h = -(ILOG2( IDIF(d,1) ) - k);
       
       if (i1 == 0) {
	 b = 0;
	 i = 0; }
       else
	 FIRST2(i1,&b,&i);
       if (i2 == 0) {
	 c = 0;
	 j = 0; }
       else
	 FIRST2(i2,&c,&j);
  
Step3: /* Construct j1,j2, and j3 s.t. (j1,j2) and (j2,j3) define 
standard intervals which cover (i1,i2). */
       if (i1 <= h)
	 a = IMP2(b,h-i);
       else {
	 if (b == 0)
	   a = 0;
	 else {
	   if (ISIGNF(b) > 0 || IORD2(b) > i - h)
	     a = IDP2(b,i-h);
	   else
	     a = IDIF(IDP2(b,i-h),1); } }
       j1 = LBRNFIE(a,-h);
       j2 = LBRNFIE(ISUM(a,1),-h);
       j3 = LBRNFIE(ISUM(a,2),-h);


       L1 = NIL; L2 = NIL;
       if (LBRNCOMP(i2,j2) <= 0)
	 L2 = IPRRISI(A,LIST2(j1,j2));
       else {

	 /* Trim (j1,j2) and (j2,j3) if possible. */
	 j1p = LSIM(j1,j2);
	 if (LBRNCOMP(j1p,i1) <= 0)
	   j1 = j1p;
	 j3p = LSIM(j2,j3);
	 if (LBRNCOMP(i2,j3p) <= 0)
	   j3 = j3p;

	 /* Construct L1 & L2 so that they contain all roots in (i1,i3). */
	 L1 = IPRRISI(A,LIST2(j1,j2));
	 L2 = IPRRISI(A,LIST2(j2,j3));
	 if (IUPLBREVAL(A,j2) == 0)
	   L2 = COMP(LIST2(j2,j2),L2);
       }
       
Step4: /* Remove all roots of A in L1 which are left of i1. */
       while (L1 != NIL && RRLBRNCOMP(A,FIRST(L1),i1,2) <= 0)
	 L1 = RED(L1);
       
Step5: /* Remove all roots of A in L2 which are right of i2. */
       L2 = INV(L2);
       while (L2 != NIL && RRLBRNCOMP(A,FIRST(L2),i2,2) >= 0)
	 L2 = RED(L2);
       L2 = INV(L2);
       
Step6: /* Construct L, the roots of A in I. */
       L = CONC(L1,L2);
       
Return: /* Prepare to return. */
       return L;
}
