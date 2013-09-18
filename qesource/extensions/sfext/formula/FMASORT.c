/*===========================================================================
ForMulA sort
===========================================================================*/
#include "espcad.h"

static Word comparison(Word A, Word B) { return ICOMP(FMALEVEL(A),FMALEVEL(B)); }

/* This simply sorts by formula level. */
Word FMASORT(Word F)
{
  Word f,L,Fp;

  f = FIRST(F);
  switch (f)
  {
    /* Constants. */
  case TRUE: 
  case FALSE:
    Fp = F;
    break;

    /* AND and OR. */
  case ANDOP: 
  case OROP:
    L = CINV(RED(F));
    for(Fp = NIL; L != NIL; L = RED(L))
      Fp = COMP(FMASORT(FIRST(L)),Fp);
    Fp = GMSL(Fp,comparison);
    Fp = COMP(f,Fp);
    break;

    /* Atomic Formulas. */
  default:
    Fp = F;
    break;
  }
  
  return Fp;
}

static Word comparison2(Word A, Word B) 
{ 
  Word t,tA,tB,jA,jB,oA,oB;
  /* Sort by level first. */
  t = ICOMP(FMALEVEL(A),FMALEVEL(B));
  if (t != 0)
    return t;

  tA = FTYPEINFO(A);
  tB = FTYPEINFO(B);
  if (tA != tB)
    return ICOMP(tA == NIL ? 2 : tA, tB == NIL ? 2 : tB);
  else {
    switch (tA) {
    case (NIL) : /* Atomic Formulas. */
      jA = SECOND(FIRST(A));
      jB = SECOND(FIRST(B));
      if (jA != jB) return ICOMP(jA,jB);
      oA = SECOND(A);
      oB = SECOND(B);
      if (ISLIST(oA) && ISLIST(oB)) {
	if (FIRST(oA) == FIRST(oB))
	  return ICOMP(SECOND(oA),SECOND(oB));
	else 
	  return ICOMP(FIRST(oA),FIRST(oB)); }
      else
	return ICOMP(oA,oB);
      break;
    case (ANDOP) :
    case (OROP) :
      if (LENGTH(A) == 1 || LENGTH(B) == 1)
	return ICOMP(LENGTH(A),LENGTH(B));
      t = comparison2(SECOND(A),SECOND(B));
      if (t != 0)
	return t;
      else
	return comparison2(COMP(FIRST(A),RED2(A)),COMP(FIRST(B),RED2(B)));
      break;
    default:
      return 0;
    }
  }
}

Word FMASORT2(Word F)
{
  Word f,L,Fp;

  f = FIRST(F);
  switch (f)
  {
    /* Constants. */
  case TRUE: 
  case FALSE:
    Fp = F;
    break;

    /* AND and OR. */
  case ANDOP: 
  case OROP:

    for(Fp = NIL, L = RED(F); L != NIL; L = RED(L))
      Fp = COMP(FMASORT2(FIRST(L)),Fp);

    L = GMSL(Fp,comparison2);
    Fp = COMP(f,Fp);
    break;

    /* Atomic Formulas. */
  default:
    Fp = F;
    break;
  }
  
  return Fp;
}
