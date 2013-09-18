
/*
  Lifts over cell c in CAD D with projection factor set P.
  c must satisfy CELLSRRQ2D, and both siblings of c must
  already have their child stacks in place.
   Return 1 if successfull, otherwise 0
 */

#include "lift2d.h"

//#define _PRE_ 22
#define _PRE_ 80

/* Sorts intervals.  If one is contained in another, the containing interval comes first! 
This relies on the containing properties of Standard Intervals, this, L1 and L2 must
consist of Logarithmic binary rational standard intervals!
*/
static Word _MERGE(Word L1, Word L2)
{
  Word t;
  if (L1 == NIL)
    return L2;
  if (L2 == NIL)
    return L1;
  t = LSICOMP(FIRST(L1),FIRST(L2));
  if (t == -1 || t == 1)
    return COMP(FIRST(L2),_MERGE(L1,RED(L2)));
  else
    return COMP(FIRST(L1),_MERGE(RED(L1),L2));
}

void debWRITEINTERVAL(Word I) {
  RNWRITE(FIRST(I));
  SWRITE(", ");
  RNWRITE(SECOND(I));
}


Word LIFTSRR2D(Word c, Word D, Word P)
{
  Word S_L,S_R,s_L,s_R,S,i,c_L,c_R,cp,flag,m_L,m_R,so,mo,m,s,j;
  Word M,I,P2,Rp,t,R,Rs,Rt,SP,r,k,c1,c2,prev,Sp,sor,next,s2,nextc,X;
  Word OC, OT,count;

  /* Initialization */
  S_L = LELTI(CELLLEFTSIB(c,D),CHILD); 
  S_R = LELTI(CELLRIGHTSIB(c,D),CHILD);
  S = NIL;
  if (LENGTH(S_L) != LENGTH(S_R)) FAIL("LIFTSRR2D","Assumption false!");

  /* Get coordinate info for c: M the min pol, I the interval */
  FIRST2(LELTI(c,SAMPLE),&M,&I);


  /* Isolating the roots of all 2-level projection factors over c. 
     Note:  I know this is inefficient! */
  OC = NIL; /* Just for overlap checking! */
  R = NIL;
  for(P2 = LELTI(P,2); P2 != NIL; P2 = RED(P2)) {
    //    IBPRRIOAP(M,BRILBRI(I),LELTI(FIRST(P2),PO_POLY), _PRE_,&Rp,&t);
    t = 1; //DEBUG
    if (t) {
      //      IBPRRIOAPSF(M,BRILBRI(I),LELTI(FIRST(P2),PO_POLY),8, _PRE_,&t,&Rp); 
      IBPRRIOAPSF(M,BRILBRI(I),LELTI(FIRST(P2),PO_POLY),80, _PRE_,&t,&Rp); // DEBUG
      if (Rp == 0) {
	X = 0;
	goto Return; }
    }
    
    OC = _MERGE(Rp,OC);
    for(Rs = Rp, Rt = NIL; Rs != NIL; Rs = RED(Rs))
      Rt = COMP(LBRIBRI(FIRST(Rs)),Rt);
    R = COMP(CINV(Rt),R); }
  R = CINV(R);


  /* Hack for overlaps!!!! I'm too lazy for real refinement techniques! */
  count = 0;
  while(OC != NIL && RED(OC) != NIL)
  {
    //    SWRITE("DEB: "); debWRITEINTERVAL(FIRST(OC)); SWRITE(" : "); debWRITEINTERVAL(SECOND(OC)); SWRITE("\n");
    OT = LSICOMP(FIRST(OC),SECOND(OC));
    if (OT == 2 || OT == 0) {/* first contains second */
      count++;
      OC = COMP(FIRST(OC),RED2(OC)); }
    else if (OT == -2)
      OC = RED(OC);
    else
      FAIL("LIFTSRR2D","Failed logic in my refinement hack!");
  }
  if (count > 1) { /* Just repeat the above, but all in floating point! */
    R = NIL;
    for(P2 = LELTI(P,2); P2 != NIL; P2 = RED(P2)) {
      IBPRRIOAPSF(M,BRILBRI(I),LELTI(FIRST(P2),PO_POLY),8, _PRE_ + 10,&t,&Rp); 
      if (Rp == 0) {
	X = 0;
	goto Return; }
      t = 0;
      for(Rs = Rp, Rt = NIL; Rs != NIL; Rs = RED(Rs))
	Rt = COMP(LBRIBRI(FIRST(Rs)),Rt);
      R = COMP(CINV(Rt),R); }
    R = CINV(R);
  }
  /* End of *really* ugly hack! */


  /**************************************/
  /* Go through the neighboring stacks! */
  /**************************************/
  i = 0;
  flag = FALSE;
  for(S = NIL; S_L != NIL; S_L = RED(S_L), S_R = RED(S_R)) {

    c_L = FIRST(S_L);
    c_R = FIRST(S_R);

    if (EQUAL(FIRST(LELTI(c_L,SIGNPF)),FIRST(LELTI(c_R,SIGNPF)))) {
      /************************************************************
       ** NO CROSSINGS HERE!
       ************************************************************/
      i++;
      /* Set up sample point correctly */
      SP = NIL;
      s_L = FIRST(LELTI(c_L,SIGNPF));
      for(k = 1; s_L != NIL; s_L = RED(s_L), k++) {
	if (FIRST(s_L) == 0) {
	  r = LELTI(R,k);
	  SP = LIST5(LELTI(LELTI(LELTI(P,2),k),PO_POLY),FIRST(r),LIST2(0,LIST2(RNINT(1),LIST2(1,1))),0,0); /* SP */
	  SLELTI(R,k,RED(r)); } }

	/* CONSTRUCT CELL */
	cp = LIST10(FIRST(c_L),NIL,THIRD(c_L),UNDET,SP,
		  CCONC(LELTI(c,INDX),LIST1(i)),COMP(FIRST(LELTI(c_L,SIGNPF)),LELTI(c,SIGNPF)),
		  NOTDET,
		  LELTI(c_L,DEGSUB),LELTI(c_L,MULSUB));
      S = COMP(cp,S);
      flag = FALSE; }

    else {
      /************************************************************
       ** CROSSINGS HERE!
       ************************************************************/
      i++;

      /* Contruct and add SIGNPF and SAMPLEPOINT and MULT*/
      SP = NIL;
      m = NIL;
      s_L = FIRST(LELTI(c_L,SIGNPF));
      s_R = FIRST(LELTI(c_R,SIGNPF));
      so = FIRST(LELTI(FIRST(S),SIGNPF));
      for(s = NIL, k = 1; s_L != NIL; s_L = RED(s_L), s_R = RED(s_R), so = RED(so), k++) {
	if (FIRST(s_L) == 0 || FIRST(s_R) == 0) {
	  r = LELTI(R,k);

	  /* Define sample point if not already defined or if this version has a smaller isolating interval! */
	  if (SP == NIL || RNCOMP(RNDIF(SECOND(FIRST(r)),FIRST(FIRST(r))),RNDIF(SECOND(SECOND(SP)),FIRST(SECOND(SP)))) < 0)
	    SP = LIST5(LELTI(LELTI(LELTI(P,2),k),PO_POLY),FIRST(r),LIST2(0,LIST2(RNINT(1),LIST2(1,1))),0,0); /* SP */

	  SLELTI(R,k,RED(r));
	  s = COMP(0,s);
	  m = COMP(LIST2(k,1),m);
	}
	else
	  s = COMP(FIRST(so),s); }
      s = COMP(CINV(s),LELTI(c,SIGNPF));
      m = CINV(m);

      cp = LIST10(FIRST(c_L),NIL,THIRD(c_L),UNDET,SP,
		  CCONC(LELTI(c,INDX),LIST1(i)),s,NOTDET,
		  LELTI(c_L,DEGSUB),m);
      
      S = COMP(cp,S);
      S_L = RED2(S_L);
      S_R = RED2(S_R);
    } }
  

  /***********************************/
  /* Refine further if needed? *******/
  /***********************************/

  /***********************************/
  /* Add in sector sample points! ****/
  /***********************************/
  S = CINV(S);
  prev = NIL;
  Sp = S;
  //  SWRITE("DEBUG>>>\n");
  while(Sp != NIL) {
    ADV(Sp,&sor,&Sp);
    if (Sp == NIL) {
      next = NIL;
      //      SWRITE("DEBUG: NIL\n"); 
    }
    else {
      ADV(Sp,&nextc,&Sp);
      next = FIRST(SECOND(LELTI(nextc,SAMPLE))); 
      //      SWRITE("DEBUG: "); RNWRITE(FIRST(SECOND(LELTI(nextc,SAMPLE)))); SWRITE(", "); RNWRITE(SECOND(SECOND(LELTI(nextc,SAMPLE)))); SWRITE("\n"); 

    }
    s2 = CSSP(prev,next);

    // set it!
    c1 = LIST2(RNINT(1),LIST2(1,1)); //ANF element alpha
    c2 = LIST2(s2,LIST2(0,1)); // ANF element s2
    SLELTI(sor,SAMPLE,LIST3(M,I,LIST2(c1,c2)));

    if (Sp != NIL)
      prev = SECOND(SECOND(LELTI(nextc,SAMPLE)));
  }
  //  SWRITE(">>>DEBUG\n");


  

  SLELTI(c,CHILD,S);
  X = 1;

Return:
  return X;
}

