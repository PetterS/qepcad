/*======================================================================
                 SF <- NAIVESF(L_T,L_F,L_A,P)

Niave solution formula construction.

Inputs
 L_T :  a list of true cells
 L_F :  a list of false cells
 L_A :  a list of atomic formulas
 P   :  the projection factor set to which the signitures of the
        elements of L_T and L_F refer.

Outputs
 SF  :  a solution formula in the atoms from L_A

Note : The cells can be PCAD or ESPCAD cells. The elements of L_A must
       be FMA atomic formulas.  If elements of L_A are in the extended
       language, L_T and L_F must consist of ESPCAD cells.
======================================================================*/
#include "qepcad.h"
Word IMPCONS(Word,Word,Word,Word);
Word MINCOVBF(Word,Word,Word);

Word NAIVESF(Word L_T, Word L_F, Word L_A, Word P)
{
     Word SF,I,X,L,c;

Step0: /* Special cases. */
     if (L_F == NIL) {
       SF = LIST1(TRUE);
       goto Return; }
     if (L_T == NIL){
       SF = LIST1(FALSE);
       goto Return; }

Step1: /* Construct I, a set of implicants covering L_T. */
     I = NIL;
     for(L = L_T; L != NIL; L = RED(L)) {
       c = FIRST(L);
       if (FMACELLEVAL(COMP(OROP,I),c,P) != TRUE)
	 I = COMP(IMPCONS(c,L_F,L_A,P),I); }

Step2: /* Choose small subset of I that covers L_T. */
     X = MINCOVBF(L_T,I,P);
     if (!ISLIST(X))
       SF = 0;
     else if (X == NIL)
       SF = LIST1(TRUE);
     else if (LENGTH(X) ==1)
       SF = FIRST(X);
     else
       SF = COMP(OROP,X);

Return: /* Prepare to return. */
     return SF;     
}


