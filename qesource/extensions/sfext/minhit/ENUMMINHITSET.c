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

/*  NOTE:  COMMENTS ARE ALL WRONG !!!!!!!! */

Word ENUMMINHITSET(Word A, Word B, Word P)
{
      Word L,As,C,Cp,p,Ap,T,s,Pp,t;

Step1: /* Quick decisions. */
      if (A == NIL) return (LIST1(NIL));
      if ((B == 0) || (FIRST(A) == NIL)) return (MC_FAIL);

Step2: /* Initialize loop. */
      L = USDIFF(FIRST(A),P);
      As = RED(A);
      C = MC_FAIL; 

Step3: /* Loop over the elements of L, looking for a min. hit set of A. */
      while (L != NIL) {
        ADV(L,&p,&L);
	t = IPROD(IQ(p - 1,3),3);
	Pp = CCONC(P,LIST3(t+1,t+2,t+3));
	Pp = CCONC(Pp,L);

Step4: /* Eliminate from A all sets hit by p, call this Ap. */
        Ap = NIL; T = As;
        while ( T != NIL) {
          ADV(T,&s,&T);
          if (! MEMBER(p,s)) {
            Ap = COMP(s,Ap); } }
        Ap = INV(Ap);

Step5: /* Recurse: Look for a cover of Ap of at most B-1 columns. */
         Cp = ENUMMINHITSET(Ap,B-1,Pp);
         if ( Cp != MC_FAIL ) {
	   if (C == MC_FAIL) C = NIL;
	   while (Cp != NIL) {
	     C = COMP( COMP(p,FIRST(Cp)) , C );
	     Cp = RED(Cp); } } }

Return: /* Loop complete.  Return. */
      return (C);
}
