/*======================================================================
                      C <- MINHITSETSR(A,B)

Minimum hitting set. (Minimum with respect to cardinality.)  Sort
rows by size first, with duplicate removal.

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
Note:  The point is that not only sorting the list of subsets so that 
       short subsets come first improve the performance of MINHITSET,
       but removing duplicate rows my improve things further.
======================================================================*/
#include "qepcad.h"
#define BDCOMP(a,b)  ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#define MC_FAIL 0

static Word comp(Word a, Word b) {
      Word ap,bp,t,q;
      ap = a; bp = b;
      t =  BDCOMP(LENGTH(ap),LENGTH(bp));
      while ((t == 0) && (bp != NIL) && (ap != NIL)) { 
	 t = BDCOMP(FIRST(ap),FIRST(bp)); ap = RED(ap); bp = RED(bp); }
      if (t == 0) { t = BDCOMP(ap,bp); }
      return (t); }
     
Word MINHITSETSRDR(Word A, Word B)
{
      Word n,*N,i,L,Ap;

Step1: /* Quick decisions. */
      if (A == NIL) return (NIL);
      if ((B == 0) || (FIRST(A) == NIL)) return (MC_FAIL);

Step2: /* Sort Rows. */
      n = LENGTH(A);
      N = GETARRAY(n);
      i = 0;
      for(L = A; L != NIL; L = RED(L))
	N[i++] = FIRST(L);
      n = GMSDS(N,n,comp);
      
Step3: /* Reconstruct list. */
      Ap = NIL;
      for(i = n - 1; i >= 0; i--)
	Ap = COMP(N[i],Ap);

Return: /* Return. */
      FREEARRAY(N);
      return (MINHITSET(Ap,B));
}
