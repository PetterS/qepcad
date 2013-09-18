/*======================================================================
                      t <- VERIFYCONSTSIGN(r,P,s)

Verify constant sign.

Inputs
 P : an r-variate integral saclib poly with deg_{xr}(P) > 0
 s : 1 or 0
 A : the assumptions formula

Output
 t : true if the procedure is able to verify that the
     polynomial is everywhere positive if s = 1 and
     everywhere non-negative if s = 0.  This is just supposed to
     be a quick test!
======================================================================*/
#include "qepcad.h"

BDigit VERIFYPOSITIVITY(Word A, BDigit r);

BDigit VERIFYCONSTSIGN(BDigit r, Word P, BDigit s, Word A)
{
  BDigit t;

  bool x_r_POS = r != 0 && VERIFYPOSITIVITY(A,r);
  
  if (P == 0)
    t = (s == 0) || x_r_POS;
  else if (r == 0)
    t = (ISIGNF(P) >= s);
  else if (PDEG(P) == 0)
    t = VERIFYCONSTSIGN(r-1,PLDCF(P),s,A);
  else if (!x_r_POS && PDEG(P) % 2 == 1)
    t = 0;
  else 
    t = VERIFYCONSTSIGN(r-1,PLDCF(P),0,A) && VERIFYCONSTSIGN(r,PRED(P),s,A);

  return t;
}

/*======================================================================
                   d <- VERIFYPOSITIVITY(A,r)

Verify positivity. [Currently this is done naively - i.e. pessimisticly]

Inputs:
 A: a normalized QEPCAD formula
 r: a level

Output:
 d: 1 if it can be determined that A implies x_r > 0,
    0 otherwise.
 ======================================================================*/

BDigit VERIFYPOSITIVITY(Word A, BDigit r)
{
  BDigit d = 0;
  if (A == TRUE || A == FALSE || A == NIL) { goto Return; }

//Step1: /* NOT OP: This case not implemented. */
  if (FIRST(A) == NOTOP)  { goto Return; }

//Step2: /* Disjunction. */
  else if (FIRST(A) == OROP) {
    d = 1;
    for(Word L = CINV(RED(A)); d == 1 && L != NIL; L = RED(L)) {
      d = VERIFYPOSITIVITY(FIRST(L),r); }
    goto Return; }

//Step3: /* Conjunction. */
  else if (FIRST(A) == ANDOP)  {
    for(Word L = CINV(RED(A)); d == 0 && L != NIL; L = RED(L)) {
      d = VERIFYPOSITIVITY(FIRST(L),r); }
    goto Return; }
  
//Step4: /* Tarski Atomic formula! Only checks if formula is x_r > 0 */
  else if (FIRST(A) != IROOT)
  {
    /* atomic formula is "P_A T_A 0", where P_A is of level k_A. */
    Word T_A,P_A,k_A,s,rp,Pp,P,a,T;
    FIRST3(A,&T_A,&P_A,&k_A);
    if (r != k_A) { goto Return; }
    
    /* check if P_A = x_r and T_A = > */
    if (T_A == GTOP && EQUAL(PMONSV(r,1,r,1),P_A)) { d = 1; goto Return; }

    /* would be nice to deduce x_r > 0 from other kinds of atomic formulas. */ 
  }
       
//Step5: /* Extended Tarski Atomic formula! */
  else {
    /* I might address this later! For now I do nothing! */
    goto Return;
  }

Return: /* Prepare for return. */
  return d;
}



