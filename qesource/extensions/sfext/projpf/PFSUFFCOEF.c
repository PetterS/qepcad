/*======================================================================
                      L <- PFSUFFCOEF(q,P,J)

Projection factors of sufficient coefficients.

Inputs:
 q : a projection factor.
 P : the structure containing all projection factors.
 J : the structure containing all projection polynomials.

Output:
 L : a list of all projection factors which are factors of some
     polynomial in a set of coefficients of of q which suffice to
     ensure degree invariance.

Side Effects:
     P and J are altered to include the new projection polynomials and
     factors.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::PFSUFFCOEF(Word q, Word P, Word J)
{
      Word i,h,C,L,Q,k,T,c,CL,cl;

Step1: /* See if the coefficients have already been computed. */
      i = SECOND(LELTI(q,PO_LABEL));
      h = LIST3(PO_LCO,0,q);
      C = PPWITHHIST(J,i-1,h);

Step2: /* Compute it if it hasn't, get a list of its factors if it has. */
      if (! C) {
	L = NIL; Q = LELTI(q,PO_POLY); k = 0; T = NIL;
	do {
	  c = PLDCF(Q);
	  if (PCONST(i - 1,c)) break;
	  ADD2PROJPOLS(i-1,c,LIST3(PO_LCO,k,q),J,P,&C,&CL);
	  L = PFSUNION(L,CL);
	  if (i == 2) break;
	  Q = PRED(Q); k++;
	  T = COMP(c,T);
	} while (!IPFZT(i - 1,T) && Q != 0); }
      else {
	CL = LIST1(C); k = 1;
	while ( (C = PPWITHHIST(J,i--,LIST3(PO_LCO,k++,q))) ) {
	  CL = COMP(C,CL); }
	L = NIL;
	while (CL != NIL) {
	  ADV(CL,&cl,&CL);
	  L = PFSUNION(L,LIST_OF_FACS(cl,P)); } }

Return:/* Return. */
      return (L);
}
