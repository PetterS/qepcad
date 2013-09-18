/*======================================================================
                      C <- MINHITSETSR(A,B)

Minimum hitting set. (Minimum with respect to cardinality.)  Sort
rows by size first.

Inputs
  A  : A list (l_1, ..., l_n), each l_i is a list of BETA-digits,
       given in ascending order.
  B  : A BETA-Digit.

Output
  C  : A Word.  If B is negative, then C is zero if no hitting set
       exists and is otherwise a list of integers which comprise
       a minimum (with respect to cardinality) hitting set.  If B 
       is non-negative, then C is zero if no hitting set with at most 
       B elements exists, and is otherwise a list of integers which 
       comprise a minimum hitting set.
Note:  The point is that sorting the list of subsets so that short
       subsets come first improves the performance of MINHITSET.
======================================================================*/
#include "qepcad.h"
#define BDCOMP(a,b)  ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#define MC_FAIL 0

static Word comp(Word a, Word b) { return BDCOMP(LENGTH(a),LENGTH(b)); }
     
Word MINHITSETSR(Word A, Word B)
{
      Word n,*N,i,Ap,L;

Step1: /* Quick decisions. */
      if (A == NIL) return (NIL);
      if ((B == 0) || (FIRST(A) == NIL)) return (MC_FAIL);

Step2: /* Sort Rows. */
      n = LENGTH(A);
      N = GETARRAY(n);
      i = 0;
      for(L = A; L != NIL; L = RED(L))
	N[i++] = FIRST(L);
      GMS(N,n,comp);
      
Step3: /* Reconstruct list. */
      Ap = NIL;
      for(i = n - 1; i >= 0; i--)
	Ap = COMP(N[i],Ap);

Return: /* Return. */
      FREEARRAY(N);
      return (MINHITSET(Ap,B));
}
