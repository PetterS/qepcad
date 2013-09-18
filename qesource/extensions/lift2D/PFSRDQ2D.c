/*
Projection factor simple root of discriminant query 2D

t <- PFSRRQ2D(p;L)

p : a projection factor

Outputs:
t TRUE if ???? else FALSE
L a list (P_1, P_2 ....) of QEPCAD projection factors,
  where p is a factor of multiplicity
  one of the discriminant of 2-level polynomials P_i.

 */
#include "lift2d.h"

/* Takes a QEPCAD polynomial and returns its level. */
static Word PFLEVEL(Word p)
{
  return SECOND(LELTI(p,PO_LABEL));
}

/* 
Projection factor simple root of discriminant query 2D

takes a QEPCAD projection factor p and returns TRUE if it only parentage
involving 2-level polynomials is as a multiplicity 1 factor of
a discriminant. */
Word PFSRDQ2D(Word p,Word *L_)
{
  Word H,L,t,Hp,h,hp,T,M,f;
  
  /* set H to PARENT(p) */
  H = LELTI(p,PO_PARENT);
  L = NIL;
  
  for(t = TRUE; t && H != NIL; H = RED(H)) {
    /* set h to next parentage in H */
    h = FIRST(H);
    FIRST3(h,&T,&M,&f);
    if (T != PO_FAC) { FAIL("PFSRDQ2D","Logic is hosed!"); }
    
    
    for(Hp = LELTI(f,PO_PARENT); Hp != NIL; Hp = RED(Hp)) {
      hp = FIRST(Hp);
      switch(FIRST(hp)) {
      case PO_RES:
	if (PFLEVEL(FOURTH(hp)) == 2) { t = FALSE; goto Return; }
	break;
      case PO_DIS:
	if (PFLEVEL(FOURTH(hp)) == 2)
	  if (M > 1)
	    { t = FALSE; goto Return; }
	else
	  L = COMP(FOURTH(hp),L);
	break;
      case PO_LCO:
	if (PFLEVEL(THIRD(hp)) == 2) { t = FALSE; goto Return; }
	break;
      default:
	FAIL("PFSRDQ2D","I never expected to get here!");
	break;
      }
    }
  }
  
  *L_ = L;
 Return:
  return t;
}

