/*======================================================================
                 L_A <- LISTOTA(P,i)

List of Tarski Atoms.

Inputs
 P   : a projection factor set structure
 i   : i a level in P

Ouptut
 L_A : a list of all Tarski atoms formed from the elements of P.  The
       order in this list is as follows:

       [ P_j,k sigma 0 ] before [ P_m,n gamma 0 ] if:
       
       1. j < m, or
       2. j = m and k < n, or
       3. j = m and k = n and sigma is less than gamma, where relational 
          ops are ordered by GEOP < LEOP < GTOP < LTOP < EQOP < NEOP.
======================================================================*/
#include "qepcad.h"

Word LISTOTA(Word P, Word i)
{
  Word L,n,L_A,Lp,I;

Step1: /* Construct list of all projection factors, in reverse order. */
  for(L = NIL, n = 1; n <= i; n++)
    L = CCONC(LELTI(P,n),L);
  L = CINV(L);
  
Step2: /* Add atoms using EQOP and NEOP. */
  for(L_A = NIL, Lp = L; Lp != NIL; Lp = RED(Lp)) {
    I = RED(LELTI(FIRST(Lp),PO_LABEL));
    L_A = COMP2(LIST2(I,EQOP),
		LIST2(I,NEOP),
		L_A); }

Step3: /* Add atoms using other relational ops. */
  for(Lp = L; Lp != NIL; Lp = RED(Lp)) {
    I = RED(LELTI(FIRST(Lp),PO_LABEL));
    L_A = COMP4(LIST2(I,GEOP),
		LIST2(I,LEOP),
		LIST2(I,GTOP),
		LIST2(I,LTOP),
		L_A); }

 Return: /* Prepare to return. */
  return L_A;
}
