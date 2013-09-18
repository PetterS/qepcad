/*======================================================================
                     	M = SIPIIRMS(L,C)

Software interval polynomial isolating interval refinement and merge sort.

Inputs
   L : a list of triples T = (i,I,t) where i is the index in the array C
       of a software interval polynomial A, I is a logarithmic standard
       open or one-point isolating interval for a root of A, and t is
       the trend of the isolated root. All the isolated roots are
       distinct.
   C : an array of pointers to software interval polynomials all of
       which are of the same precision.

Output
   M : 0 in case of failure.  Otherwise a list of the same type as L
       for the same roots and polynomials.  But in M the intervals are 
       mutually disjoint and ordered so that I < J if I precedes J in
       the list.  Moreover, two intervals share an endpoint only
       if both intervals are open.
======================================================================*/
#include "saclib.h"

Word SIPIIRMS(L,C)
	Word L;
	BDigit **C;
{
	BDigit *A1,*A2,i,i1,i2,k,n,s,t1,t2;
	Word I1,I2,J1,J2,L1,L2,M,M1,M2,T,T1,T2;

Step1: /* Trivial case. */
	n = LENGTH(L);
	if (n <= 1) {
	   M = L;
	   goto Return; }

Step2: /* Divide L into two lists, L1 and L2. */
	k = n / 2;
	L1 = NIL;
	L2 = L;
	for (i = 1; i <= k; i++) {
	   T = FIRST(L2);
	   L2 = RED(L2);
	   L1 = COMP(T,L1); }
	L1 = INV(L1);

Step3: /* Refine and merge sort L1 and L2. */
	M1 = SIPIIRMS(L1,C);
	if (M1 == 0) {
	   M = 0;
	   goto Return; }
	M2 = SIPIIRMS(L2,C);
        if (M2 == 0) {
           M = 0;
           goto Return; }

Step4: /* Refine and merge M1 and M2. */
	M = NIL;
	while (M1 != NIL && M2 != NIL) {
	   T1 = FIRST(M1);
	   T2 = FIRST(M2);
	   FIRST3(T1, &i1,&I1,&t1);
	   A1 = C[i1];
	   FIRST3(T2, &i2,&I2,&t2);
	   A2 = C[i2];
	   SIPIIS(A1,I1,t1,A2,I2,t2, &J1,&J2,&s);
	   if (s == 0) {
	      M = 0;
	      goto Return; }
	   T1 = LIST3(i1,J1,t1);
	   T2 = LIST3(i2,J2,t2);
	   if (s < 0) {
	      M1 = RED(M1);
	      M = COMP(T1,M);
	      SFIRST(M2,T2); }
	   else {
	      M2 = RED(M2);
              M = COMP(T2,M);
              SFIRST(M1,T1); } }
	while (M1 != NIL) {
	   ADV(M1, &T1,&M1);
	   M = COMP(T1,M); }
	while (M2 != NIL) {
	   ADV(M2, &T2,&M2);
	   M = COMP(T2,M); }
	M = INV(M);

Return: /* Return M. */
	return(M);
}
