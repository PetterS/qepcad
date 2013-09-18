/*
Projection factor simple root of resultant query 2D

t <- PFSRRQ2D(p;L)

p : a projection factor

Outputs:
t TRUE if ???? else FALSE
L a list ((P_1,Q_1), ....) where p is a factor of multiplicity
  one of the resultant of 2-level polynomials P_i and Q_i.

 */
#include "lift2d.h"

/* Takes a QEPCAD polynomial and returns its level. */
static Word PFLEVEL(Word p)
{
  return SECOND(LELTI(p,PO_LABEL));
}

/* 
Projection factor simple root of resultant query 2D

takes a QEPCAD polynomial p and returns TRUE if it only parentage
involving 2-level polynomials is as a multiplicity 1 factor of
a resultant. */
Word PFSRRQ2D(Word p,Word *L_)
{
  Word H,L,t,Hp,h,hp,T,M,f;
  
  /* set H to PARENT(p) */
  H = LELTI(p,PO_PARENT);
  L = NIL;
  
  for(t = TRUE; t && H != NIL; H = RED(H)) {
    /* set h to next parentage in H */
    h = FIRST(H);
    FIRST3(h,&T,&M,&f);
    if (T != PO_FAC) { FAIL("PFSRRQ2D","Logic is hosed!"); }
    
    
    for(Hp = LELTI(f,PO_PARENT); Hp != NIL; Hp = RED(Hp)) {
      hp = FIRST(Hp);
      switch(FIRST(hp)) {
      case PO_RES:
	if (PFLEVEL(FOURTH(hp)) == 2)
	  if (M > 1)
	    { t = FALSE; goto Return; }
	  else
	    L = COMP(LIST2(FOURTH(hp),LELTI(hp,6)),L);
	break;
      case PO_DIS:
	if (PFLEVEL(FOURTH(hp)) == 2) { t = FALSE; goto Return; }
	break;
      case PO_LCO:
	if (PFLEVEL(THIRD(hp)) == 2) { t = FALSE; goto Return; }
	break;
      default:
	FAIL("PFSRRQ2D","I never expected to get here!");
	break;
      }
    }
  }
  
  *L_ = L;
 Return:
  return t;
}

