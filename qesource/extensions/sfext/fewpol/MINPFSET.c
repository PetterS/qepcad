/*======================================================================
                     Q <- MINPFSET(P,S,D,N)

Minimum projection factor set.

Inputs
 P  : The projection factor data structure.
 S  : A pruned projection factor data structure.
 D  : The partial CAD data structure.
 N  : the number of variables  - i.e. level of P,S, and D
Outputs
 Q  : Q is a pruned projection factor data structure representing a
      minimum cardinality subset of P which 1) contains S and 2) suffices
      for solution formula construction.
      If P does not suffice for solution formula construction, Q = 0.
======================================================================*/
#include "qepcad.h"


Word MINPFSET(Word P, Word S, Word D, Word N)
{
      Word **P2,P1,k,r,i,L,a,*V,*Vt,**A,T,s,j,t,S_r,Sp,R,C,O,Q,p,Cp,f;

Step1: /* Initialization. */
      TDTOD(P,N,&P2,&P1,&k);
      C = NIL; S_r = NIL;

Step2: /* Loop over each level in D. */
      for(r = 1; r <= N; r++) {

Step3: /* Allocate memory for an array rep. of the signitures
	  of the level r cells. */
	k = 0; for(i = 1; i <= r; i++) { k += P2[i][0]; }
	L = CADCL(D,r);
	a = LENGTH(L);
	V = (Word*)GETARRAY(a*(k+2));
	Vt = V;
	A = (Word**)GETARRAY(a*(sizeof(Word*)/sizeof(Word))); /* ASSUMES THIS / IS EXACT! */
	V += 2;
	for(i = 0; i < a; i++) {
	  A[i] = V;
	  V += k+2; }

Step4: /* Write signiture information. */
	for(i = 0; L != NIL; i++) {
	  ADV(L,&T,&L);
	  A[i][-1] = LELTI(T,TRUTH);
	  A[i][-2] = CATV(T);
	  s = CINV(LELTI(T,SIGNPF));
	  j = 0;
	  while (s != NIL) {
	    for(ADV(s,&t,&s);t != NIL; t = RED(t))
	      A[i][j++] = FIRST(t);  } }

Step5: /* Get a list of known necessary pol's which are of level
	  at most r.  The list will be their 1-D indicies. */
	for(Sp = LELTI(S,r); Sp != NIL; Sp = RED(Sp)) {
	  R = RED(LELTI(FIRST(Sp),PO_LABEL));
	  S_r = COMP(P2[FIRST(R)][SECOND(R)],S_r); }

Step6: /* Sort cell signitures on S_r, and list conflict resolving
	  polynomials for each pair of conflicting cells in the same
	  class. */
	CSORTSS(A,a,S_r);
	for(i = 0;i < a; i = j) {
	  for(j = i + 1; (j < a) && ( SIGEQUALOL(A[i],A[j],S_r));j++);
	  Cp = ICSIGDIFFL(A+i,j-i,k);
	  C = CCONC(C,Cp);

StepE: /* If there are any lists in Cp of length 1, then take that pol. */
	  f = 0;
	  while (Cp != NIL) {
	    ADV(Cp,&t,&Cp);
	    if (LENGTH(t) == 1) {
	      f = 1;
	      SUNION(S_r,t); } }
	  if (f) CSORTSS(A+j,a-j,S_r); }

StepC: /* Deallocate memory. */
	FREEARRAY(Vt);
	FREEARRAY(A); }

Step7: /* Get a min-hit-set and translate list of 1-D indicies to an
	  actual list of polynomials. */
      O = MINHITSETSR(C,-1);
      if ( ISATOM(O) ) { Q = 0; goto Return; }
      Q = NIL;
      for(t = N; t > 0; t--) Q = COMP(NIL,Q);
      while (O != NIL) {
	R = LELTI(P1,FIRST(O)+1);
	FIRST2(RED(R),&i,&j);
	p = POLFLAB(R,P);
	t = LELTI(Q,i);
	SLELTI(Q,i,COMP(p,t));
        O = RED(O); }

Step8: /* Merge the given polynomials from S with the chosen polynomials. */
      for(i = 1; i <= LENGTH(Q); i++) {
	t = PFSUNION(LELTI(Q,i),LELTI(S,i));
	SLELTI(Q,i,t); }

Step9: /* Deallocate memory. */
      for(r = N;r > 0;r--) FREEARRAY(P2[r]);
      FREEARRAY(P2);

Return: /* Prepare to return. */
      return (Q);
}

