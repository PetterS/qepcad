/*======================================================================
                      Jp <- GROUPSAMEPJ(r,J)

Group the same projection polynomials.

\Input
  \parm{r} is the positive BETA-integer.
  \parm{J} is a list of polynomial in r variables.

\Output
  \parm{J'} is the list such that same elements are grouped.
======================================================================*/
#include "qepcad.h"

/* Projection point equal */
BDigit PRJPNTEQUAL(Word A, Word B)
{
  if (LENGTH(A) != LENGTH(B))
    return 0;

  /* Both primitive */
  Word a = FIRST(A), b = FIRST(B);
  if (ISPRIMIT(a) && ISPRIMIT(b)) {
    Word aC,aK,ac,bC,bK,bc;
    FIRST3(a,&aC,&aK,&ac);
    FIRST3(b,&bC,&bK,&bc);
    if (!EQUAL(aC,bC)) return 0;
    if (EQUAL(FIRST(aK),SECOND(aK)) && EQUAL(aK,bK)) return 1;
    if (EQUAL(FIRST(aK),SECOND(aK)) && EQUAL(FIRST(bK),SECOND(bK)) && !EQUAL(aK,bK)) return 0;
    if (RNCOMP(SECOND(aK),FIRST(bK)) <= 0 || RNCOMP(FIRST(aK),SECOND(bK)) >= 0) return 0;
    return EQUAL(ac,bc);
  }

  /* Both Not Primitive */
  if (!ISPRIMIT(a) && !ISPRIMIT(b)) {
    if (!PRJPNTEQUAL(LIST1(SECOND(A)),LIST1(SECOND(B)))) return 0;
    Word aC,aK,aM,aI,ac,bC,bK,G,Af,Bf;
    FIRST5(a,&aC,&aK,&aM,&aI,&ac);
    FIRST2(b,&bC,&bK);
    if (EQUAL(FIRST(aK),SECOND(aK)) && EQUAL(FIRST(bK),SECOND(bK)) && !EQUAL(aK,bK)) return 0;
    if (RNCOMP(SECOND(aK),FIRST(bK)) <= 0 || RNCOMP(FIRST(aK),SECOND(bK)) >= 0) return 0;
    if (EQUAL(aC,bC)) return 1;
    AFUPGC(aM,aC,bC,&G,&Af,&Bf);
    if (PDEG(G) < 1) return 0;
    Word KL = LIST2(FIRST(aK),LIST2(1,1));
    Word KR = LIST2(SECOND(aK),LIST2(1,1));
    Word sL = AFSIGN(aM,aI,AFPEMV(1,aM,G,KL));
    Word sR = AFSIGN(aM,aI,AFPEMV(1,aM,G,KR));
    return EQUAL(KL,KR) && sL == 0 || sL == 1 && sR == -1 || sL == -1 && sR == 1;
  }

  /* One primitive, the other not */
  if (ISPRIMIT(a) != ISPRIMIT(b)) {
    SWRITE("This condition not implemented in PRJPNTEQUAL!\n");
    FAIL("PRJPNTEQUAL","Incomplete Implementation Error!");
  }

  return -1;
}

Word GROUPSAMEPJ(Word r, Word J)
{
       Word J1,Jp,Js,t, Js1, Jt, J2, Jt2, i;

Step1: /* Group. */
       Jp = NIL; Js = J;
       i = 0;
       while (Js != NIL)
       {
         ADV(Js,&J1,&Js);
         Js1 = LELTI(J1,PO_POLY);
	 Jt = Jp;
         t = 0;
         while (Jt != NIL)
	 {
           ADV(Jt,&J2,&Jt);
           Jt2 = LELTI(J2,PO_POLY);
           if (LELTI(J1,PO_TYPE) == PO_POINT && LELTI(J2,PO_TYPE) == PO_POINT
	       && PRJPNTEQUAL(Js1,Jt2) || 
	       LELTI(J1,PO_TYPE) != PO_POINT && LELTI(J2,PO_TYPE) != PO_POINT
	       && EQUAL(Js1,Jt2))
	   {
             SLELTI(J2,PO_PARENT,CONC(LELTI(J2,PO_PARENT),LELTI(J1,PO_PARENT)));
             t = 1;
             break;
	   }
	 }
         if (t == 0)
	 {
           i = i + 1;
           SLELTI(J1,PO_LABEL,LIST3(LFS("J"),r,i));
           Jp = COMP(J1,Jp);
	 }
       }
       Jp = INV(Jp);
       
Return: /* Prepare for return. */
       return(Jp);
}
