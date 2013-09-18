/*
F : a formula in DNF form (formally speaking!) involving k-level p.f.'s
S : a set of cells in k-1 space.  F is a formula for the children of the
    elements of S.
P : the projection factor set on which the signitures of cells are based.
Fs: a list of disjuncts that are satisfied for some element above each cell
    in S.

Output
L : a list of pairs (S_i,F_i), the S_i represent a partition of S.  Over 
    each cell in S_i there is a child cell satisfying F_i.  F_i is in
    DNF form (formally speaking!).
 */
#include "qepcad.h"
#include "espcad.h"

Word GEOPARTII(Word F, Word S, Word P, Word Fs)
{
  Word L,f,Fp,St,Sf,Sp,Lt,Lf;

  /* Base Case. */
  if (FMADMQ(COMP(OROP,Fs),S,1,P)) {
    L = LIST1(LIST2(S,COMP(OROP,Fs)));
    goto Return; }
  if (LENGTH(F) == 1) { /* i.e. (OROP). */
    L = LIST1(LIST2(S,CCONC(F,Fs)));
    goto Return; }
  
  /* f is the first disjunct, Fp is the formula with f removed. */
  f = SECOND(F);
  Fp = COMP(OROP,RED2(F));
  
  /* Partition S into St and Sf, elt's  with a child that 
     satisfies f and those without. */
  for(St = NIL, Sf = NIL, Sp = S; Sp != NIL; Sp = RED(Sp)) 
    if (FMACELLEXQ(f,FIRST(Sp),P))
      St = COMP(FIRST(Sp),St);
    else
      Sf = COMP(FIRST(Sp),Sf);

  /* If needed, decompose St. */
  if (St == NIL)
    Lt = NIL;
  else
    Lt = GEOPARTII(Fp,St,P,COMP(f,Fs));

  /* If needed, decompose Sf. */
  if (Sf == NIL)
    Lf = NIL;
  else
    Lf = GEOPARTII(Fp,Sf,P,Fs);

  /* Merge the two decompositions. */
  L = CCONC(Lt,Lf);

Return: /* Prepare to return. */
  return L;
}
