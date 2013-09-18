/*======================================================================
                     CSORCELLTR_MOD(c,Pp,PpO,PpN,P)

Construct stack over RCell: total rebuild - Modified to work right
with equational constraints.

Inputs
  c  : An RCell which is not of the highest level.
  Pp : will be the level k+1 projection factors, given as PpO, PpN.
  PpO: will be the original k+1 projection factors.
  PpN: PpN will be the new k+1 level projection factors.
  P  : The projection factor set defining the CAD in which c
       resides, or the projection factor set defining the CAD
       in which LELTI(c,RNCELL) resides.

Side Effects
  A stack is constructed over c.  The information from INCELL is only
  used for truth value assignments, not to help build the stack.
  
======================================================================*/
#include "qepcad.h"
#include "newpols.h"
static Word ISCSOPP(Word c,Word M);
static Word LLPFZC(Word c,Word P);

void QepcadCls::CSORCELLTR_MOD(Word c, Word Pp, Word PpO, Word PpN, Word P)
{
      Word f,s,sh,M,K,C,Pps,L,T,B,E,I,A,a,b,k;
      Word PP,NP,L_P,TP,i,ta,t;

Step0:
      k = LELTI(c,LEVEL);
      s = LELTI(c,SAMPLE);
      sh = CONVERT(s,k);
      SLELTI(c,SAMPLE,sh);

      /* Trick CONSTRUCT into working for us by wrapping the elements of
	 Pp (which are SACLIB polynomials) in a dummy QEPCAD projection
	 polynomial/factor data structure. */
      Word PpM = NIL;
      for(Word PpR = CINV(Pp),j=LENGTH(Pp); PpR != NIL; PpR = RED(PpR),--j)
	PpM = COMP( LIST5(FIRST(PpR),LIST3(LFS("P"),k+1,j),0,PO_FAC,0) ,PpM);
      CONSTRUCT(c,k,GVNFV,PpM,GVNIP);

Step5: /* Add two new fields to each cell to make it an RCell. */
      T = NIL;
      for(A = LELTI(c,CHILD); A != NIL; A = RED(A)) {
	T = COMP(CCONC(FIRST(A),LIST2(NIL,NIL)),T); }
      SLELTI(c,CHILD,CINV(T));
      
Step6: /* Add truth values and other information. */
       
       /* Get mask for pivot pol's, i.e. a list of
	  1's and zeros corresponding to PpO, where
	  the non-pivot pol positions are 1, and
	  the pivot pol positions are zero. */

      SEPPIVNONPIV(LELTI(P,k+1),k+1,&PP,&NP); /* Get list of pivot pol's for this level. */
      if ( (NP != NIL) && SINTER(LELTI(GVPIVOT,k+1),LLPFZC(c,P)) != NIL ) {
	PP = LELTI(P,k+1); NP = NIL; }

      L_P = NIL;
      ta = FIRST(LELTI(FIRST(LELTI(c,CHILD)),SIGNPF)); /* signiture of a sector on level 
							  k+1 pols. */
      for(TP = LELTI(P,k+1); TP != NIL; TP = RED(TP)) {
	  /* Subtle point:  a pivot pol might vanish identically in this stack,
	     which would mess everything up.  If this pol does vanish identically
	     in the stack, don't include it in the mask! */
	ADV(ta,&i,&ta); /* sign of current pol in a sector: if 0 then pol vanishes in stack. */
	if ( PFPIPFL(FIRST(TP),PP) &&  i ) {
	  L_P = COMP(0,L_P); }
	else
	  L_P = COMP(1,L_P); }
      L_P = INV(L_P);

      A = LELTI(c,CHILD);               /* Stack with more cells, i.e. new.  */
      B = LELTI(LELTI(c,INCELL),CHILD); /* Stack with fewer cells, i.e. old. */
      ADV(B,&b,&B);
      ADV(A,&a,&A);

      while (A != NIL) {

	SLELTI(a,INCELL,b); 
	SLELTI(a,TRUTH,LELTI(b,TRUTH)); 
	SLELTI(a,HOWTV,LELTI(b,HOWTV));
	ADV(A,&a,&A);
	if (LELTI(b,MULSUB) != NIL)
	  ADV(B,&b,&B); /* i.e. if b is a section. */
	if ( ISCSOPP(a,L_P) ) {
	  do{
	    ADV(B,&b,&B);
	  } while( ! ISCSOPP(b,L_P) ); } }
	  

      SLELTI(a,INCELL,b);
      SLELTI(a,TRUTH,LELTI(b,TRUTH));
      SLELTI(a,HOWTV,LELTI(b,HOWTV));

Return: /* */
      return;
}

/*======================================================================
Is cell a section of a pivot pol?

c : a cell.
M : the mask.
======================================================================*/

static Word ISCSOPP(Word c,Word M)
{
      Word S,L,s,l,t;

Step1: /* Check the first zero entry of a's signiture on b. */
      S = FIRST(LELTI(c,SIGNPF));
      L = M;
      t = 0;
      while( L != NIL ) {
	ADV(L,&l,&L);
	ADV(S,&s,&S);
	if ( s == 0 && l == 0 ) {
	  t = 1; break; } }

      return (t);
}



/*======================================================================
List of all labels of all proj fac's which are zero in cell.
======================================================================*/

static Word LLPFZC(Word c,Word P)
{
      Word S,N,L,S_i,P_i,i,s,p;

      S = LELTI(c,SIGNPF);
      N = LENGTH(S);
      L = NIL;
      for(i = N; i > 0; i--) {
	S_i = LELTI(S,N - i + 1);
	P_i = LELTI(P,i);
	while( P_i != NIL ) {
	  ADV(S_i,&s,&S_i);
	  ADV(P_i,&p,&P_i);
	  if (s == 0)
	    L = COMP(p,L); } }
       
      return (L);

}

