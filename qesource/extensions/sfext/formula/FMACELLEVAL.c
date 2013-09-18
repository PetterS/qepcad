/*===========================================================================
                             t <- FMACELLEVAL(F,C,P)

Formula in cell evaluation.

Inputs
  F : an FMA formula.
  C : an ESPCAD cell.
  P : the projection factor set to which C's signiture refers.

Outputs
  t : TRUE, FALSE, or UNDET --- the truth value of F in C.
===========================================================================*/
#include "espcad.h"

Word FMACELLEVAL(Word F, Word C, Word P)
{
  Word t,L,i,j,k,op,s,S,ip,c,v,cp,n,t1,A1,A2,U_FLAG;

  switch(FIRST(F)) {
    
  case (TRUE) : t = TRUE;  break;

  case (FALSE): t = FALSE; break;

  case (NOTOP): 
    t = FMACELLEVAL(SECOND(F),C,P);
    if (t == TRUE)
      t = FALSE;
    else if (t == FALSE)
      t = TRUE;
    break;

  case (ANDOP):
    U_FLAG = 0;
    for(L = RED(F), t = TRUE; t != FALSE && L != NIL; L = RED(L)) {
      t = FMACELLEVAL(FIRST(L),C,P);
      if (t == UNDET)
	U_FLAG = 1; }
    if (t == TRUE && U_FLAG)
      t = UNDET;
    break;

  case (OROP):
    U_FLAG = 0;
    for(L = RED(F), t = FALSE; t != TRUE && L != NIL; L = RED(L)) {
      t = FMACELLEVAL(FIRST(L),C,P);
      if (t == UNDET)
	U_FLAG = 1; }
    if (t == FALSE && U_FLAG)
      t = UNDET;
    break;

  case (RIGHTOP):
    FIRST3(F,&op,&A1,&A2);
    t1 = FMACELLEVAL(A1,C,P);
    t = UNDET;
    if (t1 == FALSE)
      t = TRUE;
    else if (t1 == TRUE) 
      t = FMACELLEVAL(A2,C,P);
    else if (FMACELLEVAL(A2,C,P) == TRUE)
      t = TRUE;
    break;

  case (LEFTOP):
    FIRST3(F,&op,&A2,&A1);
    t1 = FMACELLEVAL(A1,C,P);
    t = UNDET;
    if (t1 == FALSE)
      t = TRUE;
    else if (t1 == TRUE) 
      t = FMACELLEVAL(A2,C,P);
    else if (FMACELLEVAL(A2,C,P) == TRUE)
      t = TRUE;
    break;

  case (EQUIOP):
    FIRST3(F,&op,&A1,&A2);
    t1 = FMACELLEVAL(A1,C,P);
    t = UNDET;
    if (t1 != UNDET) {
      t = FMACELLEVAL(A2,C,P);
      if (t != UNDET) { t = (t == t1) ? TRUE : FALSE; } }
    break;

  default: /* In this case F is an atom. */
    FIRST2(FIRST(F),&i,&j);
    j = POLINDEX2SIGINDEX(LELTI(P,i),j);
    ip = LELTI(LELTI(C,SC_REP),LEVEL) - i;
    for(c = C; ip > 0; ip--)
      c = LELTI(c,SC_PAR);
    if (ip < 0)
      t = UNDET;
    else {
      op = SECOND(F);

      if (ISLIST(op)) { /* Involves the extended language. */
	FIRST2(op,&op,&k);
	cp = LELTI(c,SC_PAR);
	n = LELTI(LELTI(cp,SC_RRNV),j);
	if (IABSF(k) > n) { /* Not enough roots. */
	  t = FALSE;
	  goto Return; }
	if (k > 0)
	  s = LELTI(LELTI(c,SC_EXTS),j) - 2*k; 
	else
	  s = LELTI(LELTI(c,SC_EXTS),j) - 2*(n + 1 + k); }

      else { /* Does not involve the extended language. */
	S = LELTI(c,SC_SIGN);
	s = LELTI(S,j); }

      switch (op) {
      case (LTOP) : t = (s <  0); break;
      case (EQOP) : t = (s == 0); break;
      case (GTOP) : t = (s >  0); break;
      case (GEOP) : t = (s >= 0); break;
      case (NEOP) : t = (s != 0); break;
      case (LEOP) : t = (s <= 0); break; } }
    break;
  }

Return:
  return t;
}


