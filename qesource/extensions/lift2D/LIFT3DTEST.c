
#include "lift2d.h"


/* Projection Polynomial Derivation as Level, Type
   p: a QEPCAD polynomial,i a level, pt a parentage type, i.e.
   PO_RES,PO_DIS, etc. pt and i can be NIL as a wildcard.
   returns true if p has a derivation of type pt from a level
   i projection factor. */
Word PPDLT(Word p, Word i, Word pt)
{
  Word t,H,h,A;

  t = 0;

Step1: /* Loop over each derivation h and check h against i and pt */
  for(H = LELTI(p,PO_PARENT); H != NIL && !t; H = RED(H))
  {
    h = FIRST(H);
    if (FIRST(h) == PO_RES || FIRST(h) == PO_DIS)
      A = LELTI(h,4);
    else
      A = LELTI(h,3);
    if ((pt == NIL || FIRST(h) == pt) && 
	(i == NIL || SECOND(LELTI(A,PO_LABEL)) == i))
      t = 1;
  }

Return: /* Prepare to return */
  return t;
}

Word LIFT3DTEST(Word c, Word D, Word P, Word J)
{
  Word t;
  
  /***************************************************/
  /* Determine whether I'm eligable, if not return 0 */
  /***************************************************/

  /* c is a 2-level 0-dimensional cell */
  if (LELTI(c,LEVEL) != 2 || CELLDIM(c) != 0) { t = 0; goto Return; }

  /* c is a section of exactly one 2-level projection factor */
  M = LELTI(c,MULSUB);
  if (LENGTH(M) > 1) { t = 0; goto Return; }  

  /* set p to the 2-level projection factor of which c is a section */
  j = FIRST(FIRST(M));
  for(P_2 = LELTI(P,2); p = FIRST(P_2) && 
	j != THIRD(LELTI(p,PO_LABEL)); P_2 = RED(P_2));

  /* p must be a multiplicity 1 factor of the discrim of a 3-level p.f. 
     and nothing else!! */
  H = LELTI(p,PO_PARENT);
  FIRST3(h,&T,&m,&q); /* T better be PO_FAC!!!! */
  if (LENGTH(H) != 1 || m > 1) { t = 0; goto Return; }
  hq = LELTI(q,PO_PARENT);
  if (LENGTH(H) != 1 || FIRST(hq) != PO_DIS || PFLEVEL(FOURTH(hq)) != 3) 
  { t = 0; goto Return; }
  
  /* get g, the 1-level p.f. of which c's parent is a section */
  g = FIRST(LPFZC(LIST1(FIRST(LELTI(c,INDX))),P));
  f = 0;
  for(H = LELTI(g,PO_PARENT); H != NIL && !f; H = RED(H))
  {
    FIRST3(g,&T,&m,&q); /* T better be PO_FAC!!!! */
    if (PPDLT(q,3,NIL) || (PPDLT(q,2,PO_DIS) && m > 1))
      f = 1;
  }
  if (f) { t = 0; goto Return; }
  

  /***************************************************/
  /* Isolate Roots of PFs */
  /***************************************************/
  np = 8; /* np is the software precision of computations */

  /* Get refined intervals for each coordinate */
  C = SPGRI(); /* Sample Point Get Refined Intervals */

  /* loop over each P.F. A */
  for(P_3 = LELTI(P,3); P_3 != NIL; P_3 = RED(P_3))
  {
    /* get Sftwre Intrvl Pol As for A eval'd @ coords */
    n = PDEG(A);
    As = GETARRAY((n+1)*(2*p+6)+1);
    IPEVLBRIUSIPR(A,V,np,As); /* Integral polynomial evaluation at vector of LBR Intervals, SIPoly result */

    /* isolate roots of As */
    if (SISIGN(As[n]) == NIL) /* too little precision! do something!*/;
    L = modSIPRRID(As);
    /* Deal with the many ways this may fail! */
    FREEARRAY(As);
  }

  /***************************************************/
  /* Compute Adjacency Info */
  /***************************************************/

  /***************************************************/
  /* Use stack over adjacent cell to construct new stack */
  /***************************************************/

Return: /* Return! */
  return t;
}
