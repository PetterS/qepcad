/*======================================================================
                     TDTOD(P,P2,N,P1,k)

Two dimensional to one dimensional.

Inputs:
 P : The projection factor set data structure;
 N : The number of free variables.

Outputs:
 P2: A 2D array.  P2[i][0] is the number of level i projection factors.
 P1: A 1D list.
 k : The number of projection factors of level at most N.

Note:  The following holds between P1 and P2:  for each i,j such that
       the projection factor with label (i,j) is in P

       LELTI(P1,P2[i][j] + 1) = the label for P_i,j.

======================================================================*/
#include "qepcad.h"

void TDTOD(Word P, Word N, Word ***P2_, Word *P1_, Word *k_)
{
      Word **P2,Pp,i,pp,n,k,m,j,P1,I,l;

Step1: /* Allocate P2. At the end of the loop k is # of pf's in P. */
      P2 = (Word**)GETARRAY((N+1)*(sizeof(Word*)/sizeof(Word))); /* ASSUMES THIS / IS EXACT! */
      Pp = P; k = 0;
      for(i = 1; i <= N; i++) {
	ADV(Pp,&pp,&Pp);
	n = LENGTH(pp);
	k += n;

       /* Finds I, the largest index in pp. */
	for(I = 0; pp != NIL; pp = RED(pp))
	  I = IMAX(THIRD(LELTI(FIRST(pp),PO_LABEL)),I);

	P2[i] = (Word*)GETARRAY(I+1);
	P2[i][0] = n; }

Step2: /* Construct P1. */
      P1 = NIL; m = k - 1;
      Pp = NIL;
      for(i = N; i > 0; i--) { Pp = COMP(LELTI(P,i),Pp); }
      for(Pp = INV(Pp); Pp != NIL; Pp = RED(Pp)) {
	for(pp = CINV(FIRST(Pp)); pp != NIL; pp = RED(pp)) {
	  l = LELTI(FIRST(pp),PO_LABEL);
	  FIRST2(RED(l),&i,&j);
	  P2[i][j] = m--;
	  P1 = COMP(l,P1); } }

Return: /* Prepare to return. */
      *P2_ = P2;
      *P1_ = P1;
      *k_  = k;
      return;
}
