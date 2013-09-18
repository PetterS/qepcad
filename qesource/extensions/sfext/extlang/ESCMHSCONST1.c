/*

L  : a list of i-level conflicting pairs above the i-1 level cell C.  
     Each conflicting pair is given as a pair of k-level
     cells over distinct i-level cells.  The first element should be
     below the second in the i-level stack.
C  : see above.
i  : see above.

Output
Q  : a list (q_1, ..., q_n) corresponding to conflicting pairs 
     (l_1, ..., l_n), such that q_m gives all sections between
     the pair l_m (inclusive) as a pair (s,t) meaning the t_th
     section of the s_th i-level polynomial.

 */
#include "extlang.h"

Word ESCMHSCONST1(Word L, Word C, Word i)
{
  Word Sp,Lp,Q,c1,c2,i1,i2,S,I,c,s,j,q,k;

Step1: /* Loop over each conflicting pair (c1,c2). */
  Sp = LELTI(C,SC_CDTV); Lp = L;
  for(Q = NIL; Lp != NIL; Lp = RED(Lp)) {
    FIRST2(FIRST(Lp),&c1,&c2);
    
Step2: /* List of pol's with zeros between c1 and c2. */
    i1 = LELTI(LELTI(LELTI(c1,SC_REP),INDX),i);
    i2 = LELTI(LELTI(LELTI(c2,SC_REP),INDX),i);
    S = Sp; I = NIL;
    S = REDI(S,i1-1);
    do {
      ADV(S,&c,&S);
      for(j = 1, s = LELTI(c,SC_SIGN); s != NIL; s = RED(s),j++) {
	if (FIRST(s) == ZERO)
	  I = SUNION(LIST1(j),I); }
    }while (LELTI(c,SC_INX) != i2);

Step3: /* List of polynomial sections between c1 and c2. */
    for(q = NIL; I != NIL; I = RED(I)) {
      j = FIRST(I);
      k = 0; S = Sp;
      do {
	ADV(S,&c,&S);
	if (LELTI(LELTI(c,SC_SIGN),j) == 0) {
	  k++;
	  if (LELTI(c,SC_INX) >= i1) {
	    q = COMP(LIST2(j,k),q); } }
      }while (LELTI(c,SC_INX) != i2); }
    Q = COMP(q,Q); }

Return: /* Prepare to return. */
  return Q;
}
		  
