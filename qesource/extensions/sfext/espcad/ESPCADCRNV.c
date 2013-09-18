/*======================================================================
                      ESPCADCRNV(D)

ESPCAD root number vector.

Inputs:
 D : a ESPCAD cell.

Output:
 v : 0 if D is a root cell, otherwise a list of BETA-digits.  Suppose
     D is of level j. Then if s_k is the entry in the signiture list of 
     some child of D corresponding to  projection factor p, then v_k is 
     the number of real roots of p over D.

======================================================================*/
#include "espcad.h"

Word ESPCADCRNV(Word D)
{

      Word L,v,S,N,*A,i;

Step1: /* Case: D is a leaf cell. */
      L = LELTI(D,SC_CDTV);
      if (ISATOM(L)) {
	v = 0;
	goto Return; }
  
Step2: /* Case: There are no projection factors at the next level. */
      S = LELTI(FIRST(L),SC_SIGN);
      N = LENGTH(S);
      if (N == 0) {
	v = NIL;
	goto Return; }

Step3: /* Allocate and initialze array. */
      A = GETARRAY(N);
      for(i = 0; i < N; S = RED(S), i++)
	if (FIRST(S) == 0)
	  A[i] = -1;
	else
	  A[i] = 0;

Step4: /* Count roots in stack. */
      for(L = RED(L); L != NIL; L = RED2(L)) {
	S = LELTI(FIRST(L),SC_SIGN);
	for(i = 0; i < N; S = RED(S), i++)
	  if (FIRST(S) == 0 && A[i] != -1)
	    A[i]++; }

Step5: /* Convert array A to list v. */
      for(v = NIL; N-- > 0; v = COMP(A[N],v));
      FREEARRAY(A);

Return: /* */
      return v;
}
