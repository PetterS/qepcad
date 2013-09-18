/*======================================================================
                     Q <- MINPFSETNSC(P,S,D)

Minimum projection factor set for necessary and sufficient conditions.

Inputs
 P  : The projection factor data structure.
 S  : A pruned projection factor data structure.
 D  : The partial CAD data structure.
 K  : The list of confilicitng cells computed by CFLCELLLIST.

outputs
 Q  : A projection factor data structure which extends S by adding
      polynomials from P.  The polynomials in S define a minimal
      truth invariant CAD.  If DS is the CAD defined by S, then 
      DS will, in general, have "more" conflicting pairs than D, 
      meaning that there are points which lie in conflicting pairs
      in DS but not D.  S <= Q <= P, such that no pair of points
      exists which lie in conflicing pairs in the CAD defined by
      by Q but do not lie in conflicting pairs in the CAD defined
      by P.
======================================================================*/
#include "qepcad.h"

#define BDCOMP(a,b)       ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))
#define CFLCT 5

static Word comp1(Word a,Word b) {
  Word A,B,t;
  A = RED(a); B = RED(b); t = 0;
  while ( t == 0 && A != NIL ) {
    t = BDCOMP(FIRST(A),FIRST(B));
    A = RED(A); B = RED(B); }
  return (t); }


Word MINPFSETNSC(Word P,Word S,Word D,Word K)
{
      Word C,Sltr,Pltr,r,L_r,Ls_r,L,l,l_t,l_s,ls,Kp,Js,x,Jsp,s_k,sk;
      Word x_s,js,Ls,O,Q,Q_i,Sp,Pp,i,Cp,*V,*Vp,**A,a,N,k,S_r,I,j,p;

Step1: /* Initialization. */
      C = NIL; Sltr = NIL; Pltr = NIL; N = LENGTH(K);

Step2: /* Loop over each level in D. */
      for(r = 1; r <= N; r++) {

Step3: /* Get signiture and truth value for each cell. */
        L_r = CADCL(D,r);
	for(Ls_r = NIL; L_r != NIL; L_r = RED(L_r)) {
	  l = FIRST(L_r);
	  l_t = LELTI(l,TRUTH); l_s = LELTI(l,SIGNPF);
	  for(ls = NIL; l_s != NIL; l_s = RED(l_s)) {
	    ls = CCONC(FIRST(l_s),ls); }
	  ls = COMP(l_t,ls);
	  Ls_r = COMP(ls,Ls_r); }

Step4: /* Get conflict cell signitures. */
	Jsp = NIL;
	for(Kp = LELTI(K,r); Kp != NIL; Kp = RED(Kp)) {
	  k = FIRST(FIRST(Kp));
	  s_k = LELTI(k,SIGNPF);
	  for(sk = NIL; s_k != NIL; s_k = RED(s_k)) {
	    sk = CCONC(FIRST(s_k),sk); }
	  if (! MEMBER(sk,Jsp) )
	    Jsp = COMP(sk,Jsp); }
	for(Js = NIL; Jsp != NIL; Jsp = RED(Jsp)) { 
	  Js = COMP(COMP(CFLCT,FIRST(Jsp)),Js); }

Step5: /* Put lists together, and sort with duplicate removal. */
	Ls = CCONC(Js,Ls_r);
	Ls = GMSDSL(Ls,comp1);
	
Step6: /* Put this all into array representation. */
        a = LENGTH(Ls);
	k = LENGTH(FIRST(Ls)) - 1;
        V = (Word*)GETARRAY(a*(k + 1)); Vp = V;
        A = (Word**)GETARRAY(a*(sizeof(Word*)/sizeof(Word))); /* ASSUMES THIS / IS EXACT! */
        for(i = 0; i < a; i++) {
          A[i] = V + 1;
	  for(ADV(Ls,&ls,&Ls); ls != NIL; ls = RED(ls))
	    *(V++) = FIRST(ls); }

Step7: /* Build S_r. */
	Sltr = CCONC(Sltr,LELTI(S,r));
	Pltr = CCONC(Pltr,LELTI(P,r));
	Sp = CINV(Sltr);
	for(S_r = NIL; Sp != NIL; Sp = RED(Sp)) {
	  i = PFPIPFL(FIRST(Sp),Pltr);
	  S_r = COMP(i - 1,S_r); }

Step8: /* Sort cell signitures on S_r, and list conflict resolving
          polynomials for each pair of conflicting cells in the same
          class. */
        CSORTSS(A,a,S_r);
        for(i = 0;i < a; i = j) {
          for(j = i + 1; (j < a) && ( SIGEQUALOL(A[i],A[j],S_r));j++);
          Cp = ICSIGDIFFLNSC(A+i,j-i,k);
          C = CCONC(C,Cp); }

Step9: /* Deallocate memory. */
	FREEARRAY(Vp);
	FREEARRAY(A); }

Step10:/* Get a min-hit-set */
      O = MINHITSETSR(C,-1);
      O = LMERGE(O,S_r);
      O = LBIBMS(O); Q = NIL;
      for(r = N; r > 0; r--) Q = COMP(NIL,Q);
      while (O != NIL) {
	ADV(O,&k,&O);
	p = LELTI(Pltr,k+1);
	i = LELTI(LELTI(p,PO_LABEL),2);
	Q_i = SUFFIX(LELTI(Q,i),p);
	SLELTI(Q,i,Q_i); }

Return: /* Prepare to return. */
      return (Q);
}
        
