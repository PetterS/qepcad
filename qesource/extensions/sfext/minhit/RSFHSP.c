/*======================================================================
                  S <- RSFHSP(A;Ab)

Remove singletons from hitting set problem.

Inputs
  A  : A list (l_1, ..., l_n), each l_i is a list of BETA-digits,
       given in ascending order.

Output
  S  : A list representing the union of all elements of A of size 1.
  Ab : A list of all elements of A not hit by S.
======================================================================*/
#include "qepcad.h"

Word RSFHSP(Word A, Word *Ab_)
{
       Word n,Ap,*V,i,k,a,L,S,Ab;
 
Step1: /* Get largest value appearing in any member of A. */
       n = 0;
       for(Ap = A; Ap != NIL; Ap = RED(Ap))
	 n = MAX(LAST(FIRST(Ap)),n);

Step2: /* Initialize characteristic vector V. */
       V = GETARRAY(n + 1);
       for(i = 1; i <= n; i++)
	 V[i] = 0;

Step3: /* If a set has size 1, add that index to V. */
       for(Ap = A; Ap != NIL; Ap = RED(Ap)) {
	 ADV(FIRST(Ap),&k,&a);
	 if (a == NIL)
	   V[k] = 1; }

Step4: /* Create S, the union of all singleton sets in A. */
       S = NIL;
       for(i = n; i > 0; i--)
	 if (V[i] == 1)
	   S = COMP(i,S);

Step5: /* Create Ab, the list of all sets in A not hit by S. */
       Ab = NIL;
       for(Ap = A; Ap != NIL; Ap = RED(Ap)) {
	 for(L = FIRST(Ap); L != NIL && V[FIRST(L)] == 0; L = RED(L));
	 if (L == NIL)
	   Ab = COMP(FIRST(Ap),Ab); }

Return: /* Prepare to return. */
       FREEARRAY(V);
       *Ab_ = Ab;
       return S;
}
