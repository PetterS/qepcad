/*======================================================================
                      C <- MINWEIGHTHITSET(A,B)

Minimum hitting set. (Minimum with respect to some weighting.)

Inputs
  A  : A list (l_1, ..., l_n), each l_i is a list of pairs (a_i,b_i),
       bot BETA-digits, where a_i is the element and b_i is the
       weight.  It is required that a_i = a_j ==> b_i = b_j.  It is
       not required, but would be helpful to performance if the
       elements of l_i were listed in ascending order by weight.
  B  : A BETA-Digit.

Output
  C  : A Word.  If B is negative, then C is zero if no hitting set
       exists and is otherwise a list of integers which comprise
       a minimum (with respect to weight) hitting set.  If B 
       is non-negative, then C is zero if no hitting set with weight 
       at most B exists, and is otherwise a list of integers which 
       comprise a minimum hitting set.
======================================================================*/
#include "qepcad.h"
#define MC_FAIL 0

Word MINWEIGHTHITSET(Word A, Word B)
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
	if (B < 0 || B >= SECOND(p)) {

Step4: /* Eliminate from A all sets hit by p, call this Ap. */
	  Ap = NIL; T = As;
	  while ( T != NIL) {
	    ADV(T,&s,&T);
	    if (! MEMBER(p,s)) {
	      Ap = COMP(s,Ap); } }
	  Ap = INV(Ap);

Step5: /* Recurse: Look for a cover of Ap with weight at most B-w(p). */
	  Cp = MINWEIGHTHITSET(Ap,B-SECOND(p));
	  if ( Cp != MC_FAIL ) {
	    C = COMP(p,Cp);
	    for(B = SECOND(p) - 1; Cp != NIL; Cp = RED(Cp)) 
	      B += SECOND(FIRST(Cp)); } } }

Return: /* Loop complete.  Return. */
      return (C);
}
