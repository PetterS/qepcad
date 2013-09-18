/*======================================================================
                     CSORCELLTR(c,Pp,PpO,PpN)

Construct stack over RCell: total rebuild.

Inputs
  c  : An RCell which is not of the highest level.
  Pp : will be the level k+1 projection factors, given as PpO, PpN.
  PpO: will be the original k+1 projection factors.
  PpN: PpN will be the new k+1 level projection factors.

Side Effects
  A stack is constructed over c.  The information from INCELL is only
  used for truth value assignments, not to help build the stack.
  
======================================================================*/
#include "qepcad.h"
#include "newpols.h"

void QepcadCls::CSORCELLTR(Word c, Word Pp, Word PpO, Word PpN)
{
      Word f,s,sh,M,K,C,Pps,L,T,B,E,I,A,a,b,k;

      k = LELTI(c,LEVEL);

Step1: /* Raise stack over root. */
      if (k > 0) goto Step2;
      SLELTI(c,DEGSUB,PLDEG(Pp));
      if (Pp != NIL) I = IPLRRI(Pp); else I = NIL;
      EC1(c,I,Pp);
      SIGNP1(c,Pp,I);
      goto Step5;

Step2: /* Raise stack over non-root cell c. */
      s = LELTI(c,SAMPLE);
      sh = CONVERT(s,k);
      SLELTI(c,SAMPLE,sh);
      FIRST3(sh,&M,&K,&C);
      if (PDEG(M) == 1) {

Step3: /* Rational sample point. */
	C = RCFAFC(C);
	Pps = SUBSTR(c,k,C,Pp); /* Pps = SUBSTR(k,C,Pp); */
	SLELTI(c,DEGSUB,PLDEG(Pps));
	IPLSRP(Pps,&s,&T);
	IPFSBM(1,T,&B,&E);
	if (B != NIL) I = IPLRRI(B); else I = NIL;
	ECR(c,I,E,B);
	SIGNPR(c,k,B,I,E,s); }

      else {
Step4: /* Irrational sample point. */
	Pps = SUBST(c,k,M,C,Pp); /* Pps = SUBST(k,M,C,Pp); */
	SLELTI(c,DEGSUB,PLDEG(Pps));
	AFUPLM(M,Pps,&L,&T);
	AFCSBMDB(M,T,&B,&E);
	if (B != NIL) I = AFUPBRI(M,K,B); else I = NIL;
	EC(c,I,E,B);
	SIGNP(c,k,B,I,E,L); }

Step5: /* Add two new fields to each cell to make it an RCell. */
      T = NIL;
      for(A = LELTI(c,CHILD); A != NIL; A = RED(A)) {
	T = COMP(CCONC(FIRST(A),LIST2(NIL,NIL)),T); }
      SLELTI(c,CHILD,CINV(T));
      
Step6: /* Add truth values and other information. */
      A = LELTI(c,CHILD);               /* Stack with more cells, i.e. new.  */
      B = LELTI(LELTI(c,INCELL),CHILD); /* Stack with fewer cells, i.e. old. */
      ADV(B,&b,&B);
      ADV(A,&a,&A);
      while (B != NIL) {
	SLELTI(a,INCELL,b); 
	SLELTI(a,TRUTH,LELTI(b,TRUTH)); 
	SLELTI(a,HOWTV,LELTI(b,HOWTV));
	ADV(A,&a,&A);
	if (BZWAZ(FIRST(B),a)) ADV(B,&b,&B);
	SLELTI(a,INCELL,b); 
	SLELTI(a,TRUTH,LELTI(b,TRUTH)); 
	SLELTI(a,HOWTV,LELTI(b,HOWTV));
	ADV(A,&a,&A);
	if ( EVEN(LAST(LELTI(b,INDX))) ) ADV(B,&b,&B); }
      while ( A != NIL ) {
	SLELTI(a,INCELL,b);
	SLELTI(a,TRUTH,LELTI(b,TRUTH));
	SLELTI(a,HOWTV,LELTI(b,HOWTV));
	ADV(A,&a,&A); }
      SLELTI(a,INCELL,b);
      SLELTI(a,TRUTH,LELTI(b,TRUTH));
      SLELTI(a,HOWTV,LELTI(b,HOWTV));

Return: /* */
      return;
}

/*======================================================================
                   t <- BZWAZ(a,b)

B zero where A is zero.

Inputs
  a : A section cell.
  b : A section cell.
Note: If s_1,...,s_n is the signiture of a on polynomials p_1,...,p_n ,
      then the first n entries of the signiture of b must be the
      signiture of b on p_1,...,p_n.
  t : is 1 if a and b are both sections of the same polynomial, and
      zero otherwise. 
======================================================================*/

Word BZWAZ(Word a, Word b)
{
      Word A,B,t;

Step1: /* Check the first zero entry of a's signiture on b. */
      A = FIRST(LELTI(a,SIGNPF));
      B = FIRST(LELTI(b,SIGNPF));
      while (FIRST(A) != 0) {
	A = RED(A);
	B = RED(B); }
      t = ( FIRST(B) == 0 );

      return (t);
}
