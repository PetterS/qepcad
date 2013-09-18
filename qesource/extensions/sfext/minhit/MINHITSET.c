/*======================================================================
                      C <- MINHITSET(A,B)

Minimum hitting set. (Minimum with respect to cardinality.)

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
======================================================================*/
#include "qepcad.h"
#define MC_FAIL 0

Word MINHITSET(Word A, Word B)
{
      Word L,As,C,Cp,p,Ap,T,s;

Step1: /* Quick decisions. */
      if (A == NIL) return (NIL);
      if ((B == 0) || (FIRST(A) == NIL)) return (MC_FAIL);

Step2: /* Initialize loop. */
      L = FIRST(A);
      As = RED(A);
      C = MC_FAIL; 

Step3: /* Loop over the elements of L, looking for a min. hit set of A. */
      while ( (L != NIL) && (B != 0) ) {
	ADV(L,&p,&L);

Step4: /* Eliminate from A all sets hit by p, call this Ap. */
	Ap = NIL; T = As;
	while ( T != NIL) {
	  ADV(T,&s,&T);
	  if (! MEMBER(p,s)) {
	    Ap = COMP(s,Ap); } }
	Ap = INV(Ap);

Step5: /* Recurse: Look for a cover of Ap of at most B-1 columns. */
         Cp = MINHITSET(Ap,B-1);
         if ( Cp != MC_FAIL ) {
           C = COMP(p,Cp);
           B = LENGTH(Cp); } }

Return: /* Loop complete.  Return. */
      return (C);
}
