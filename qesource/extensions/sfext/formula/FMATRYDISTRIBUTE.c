/*======================================================================
This file is all about the FMATRYDISTRIBUTE function, which tries to
pretty-up formulas that carry some undesirable artifacts of the 
NECCONDS method of solution formula construction.

F is an FMA formula
C is an FMA atomic formula
======================================================================*/
#include "extlang.h"

/*
Number of Atoms

Input:
 F : an FMA formula (possibley in the extended language)

Output:
 n : the number of atomic formulas in F

 */
BDigit NUMATOMS(Word F)
{
  Word f, L;
  ADV(F,&f,&L);
  if (f == TRUE || f == FALSE || ISLIST(f))
    return 1;
  else if (L == NIL)
    return 0;
  else
    return NUMATOMS(FIRST(L)) + NUMATOMS(COMP(ANDOP,RED(L)));
}

/*
FMA Distribute

Inputs:
F : an FMA formula (possibley in the extended language)
C : an FMA atomic formula (")

Outputs:
Fp: the conjunction of C and F.  The function tries to
    distribute C in F, unless doing so acutally increases
    the formula size.
*/
Word FMADISTRIBUTE(Word F, Word C)
{

  Word Fp, f, L, flag, fp,gp,I,X,X_C, I_C, op, A, Ap;
  f = FIRST(F);

  switch(f)
  {
  /* CONSTANTS */
  case TRUE:  Fp = C; break;
  case FALSE: Fp = F; break;

  /* OR */
  case OROP:
    L = NIL;
    for(Fp = CINV(RED(F)); Fp != NIL; Fp = RED(Fp))
    {      
      fp = FIRST(Fp);
      gp = FMADISTRIBUTE(FIRST(Fp),C);
      L = COMP(gp,L);
    }
    Fp = COMP(f,L);
    break;

    /* AND */
  case ANDOP:
    L = NIL;
    flag = FALSE;
    for(Fp = CINV(RED(F)); Fp != NIL; Fp = RED(Fp))
    {      
      A = FIRST(Fp);
      Ap = FMADISTRIBUTE(A,C);
      if (NUMATOMS(Ap) <= NUMATOMS(A)) {
	L = COMP(Ap,L); flag = TRUE; }
      else
	L = COMP(A,L);
    }
    if (!flag)
      L = COMP(C,L);
    Fp = COMP(ANDOP,L);
    break;

     
  /* ATOMIC FORMULAS - first element is a list!*/
  default:
    FIRST2(F,&I,&X);
    FIRST2(C,&I_C,&X_C);
    if (!EQUAL(I,I_C) || ISLIST(X) || ISLIST(X_C))
    {
      Fp = LIST3(ANDOP,C,F);
      break;
    }
    op = X & X_C;
    if (op == 0)
      Fp = LIST1(FALSE);
    else
      Fp = LIST2(I,op);
    break;
  }

Return: /* Prepare to return! */
  return Fp;
}



/*
FMA try to distribute in order to simplify.

Input:
F:  an FMA formula (possibley in the extended language)
    F is assumed to be a conjunction, F = (ANDOP,f_1,...,f_k)
Output:
Fp: a formula that is no larger and possibly smaller than
    F, which is constructed by trying to distribute the
    atomic formulas in f_1,...,f_k through to the other
    componant pieces.
*/
Word FMATRYDISTRIBUTE(Word F)
{
  Word L, A, Q, f, Ap, a, Qp, Fp;

  /* Make sure we've got a conjunction! */
  if (FIRST(F) != ANDOP) return F;

  /* Separate atomic formulas (A) from others (Q) */
  L = RED(F);
  A = NIL;
  Q = NIL;
  while(L != NIL)  {
    ADV(L,&f,&L);
    if (!ISLIST(FIRST(f)))
      Q = COMP(f,Q);
    else
      A = COMP(f,A); }
  Q = COMP(ANDOP,Q);

  /* Try distributing each of the atomic formulas in the
     conjunction to see whether they can be absorbed without
     increasing the size of the formula */
  Ap = NIL;
  while(A != NIL) {
    ADV(A,&a,&A);
    Qp = FMADISTRIBUTE(Q,a);
    if (NUMATOMS(Qp) <= NUMATOMS(Q) + 1)
      Q = Qp;
    else
      Ap = COMP(a,Ap); }
      
  /* Prepare to return */
  Fp = COMP(ANDOP,CCONC(Ap,RED(Q)));
  if (LENGTH(Fp) == 2)
    Fp = SECOND(Fp);
  return Fp;
}
