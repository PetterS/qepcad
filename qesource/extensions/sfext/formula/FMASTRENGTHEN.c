/*
  formula strengthen inequalities

  F : an FMA formula
  L : list of true cells from an ESPCAD
  P : the projection factor set to which everything refers  
Output:
  The formula F may be modified by strenghening inequalities.
  However, all elements of L will still satisfy F.

*/
#include "qepcad.h"

/* F must not be or contain constants! */
static Word AFLIST(Word F)
{
  Word L = NIL;
  Word T = FIRST(F);
  if (ISLIST(T)) { L = COMP(F,L); return L; }
  if (T == TRUE || T == FALSE) { return L; }
  for(Word Fp = RED(F); Fp != NIL; Fp = RED(Fp))
    L = CCONC(AFLIST(FIRST(Fp)),L);
  return L;
}

Word FMALISTOFCELLSEVAL(Word F, Word L, Word P)
{
  Word f = TRUE;
  for(Word Lp = L; Lp != NIL && f == TRUE; Lp = RED(Lp))
    f = FMACELLEVAL(F,FIRST(Lp),P);
  return f;
}

void FMASTRENGTHEN(Word F, Word L, Word P)
{
  /* Make a list of list handles of all atomic formulas in the formula! */
  for(Word A = AFLIST(F); A != NIL; A = RED(A))
  {
    /* For each element of the list, see if that atom can be strengthened
       and still have the formula eval to TRUE on every cell in the list.
       If a strengthening works, make the change permenant! */
    
    Word a = FIRST(A), a1, a2;
    FIRST2(a,&a1,&a2);

    if (ISATOM(a2)) { /* TARSKI ATOMIC FORMULA */
      Word op = a2;
      if (op == GEOP) {
	SLELTI(a,2,GTOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,EQOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,GEOP);
      }
      else if (op == LEOP) {
	SLELTI(a,2,LTOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,EQOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LEOP);
      }
      else if (op == NEOP) {
	SLELTI(a,2,GTOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LTOP);
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,NEOP);
      }
    }
    else { /* EXTENDED TARSKI ATOMIC FORMULA */
      Word op,k;
      FIRST2(a2,&op,&k);
      if (op == GEOP) {
	SLELTI(a,2,LIST2(GTOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(EQOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(GEOP,k));
      }
      else if (op == LEOP) {
	SLELTI(a,2,LIST2(LTOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(EQOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(LEOP,k));
      }
      else if (op == NEOP) {
	SLELTI(a,2,LIST2(GTOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(LTOP,k));
	if (FMALISTOFCELLSEVAL(F,L,P) == TRUE) continue;
	SLELTI(a,2,LIST2(NEOP,k));
      }
    }    
  }

  return;
}
