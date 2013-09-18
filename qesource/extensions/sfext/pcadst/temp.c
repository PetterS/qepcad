/* Cells comprising pruned CAD cell. */
#include "qepcad.h"

Word CELLSCPCELL(Word C)
{
      Word c,A,i,L,N,Ps_N,Lp,l,S,s,k,Z,r;

Step1: /* Initialize. */
      FIRST3(C,&c,&A,&i);
      L = CELLSCPCELL(A,P,Ps);
      N = LELTI(c,LEVEL);
      Ps_N = LELTI(Ps,N);

Step2: /* Loop over all the cells that form the projection of C. */
      Lp = NIL;
      while (L != NIL) {
	l = FIRST(L);
	S = LELTI(l,CHILD);
  
Step3: /* Set s to the first child of l which lies in C. */
	ADV(S,&s,&S);
	for(k = 1; k < i; S = RED(S)) {
	  s = FIRST(S);
	  if ( EVEN(k) )
	    k++;
	  else {
	    Z = LPFZC(s,P);
	    if ( LPFSETINTERSECT(Z,Ps_N) != NIL )
	      k++; } }

Step4: /* Continue adding cells from S until they no longer lie in C. */
	if ( EVEN(i) )
	  Lp = COMP(s,Lp);
	else {
	  Lp = COMP(s,Lp);
	  
	  while ( S != NIL ) {
	    ADV2(S,&s,&r);
	    Z = LPFZC(s,P);
	    if ( LPFSETINTERSECT(Z,Ps_N) == NIL ) {
	      Lp = COMP(s,Lp);
	      Lp = COMP(r,Lp); }
	    else
	      break; } } }

Return: /* Return. */
      return (Lp);
}
       
