/*======================================================================
                 I <- IMPCONS(c,L_F,L_A,P)

Implicant construction.

Input
 c   :  a cell (PCAD or ESPCAD)
 L_F :  a list of cells (PCAD or ESPCAD)
 L_A :  a list of FMA formulas
 P   :  the projection factor set upon which the signitures of the
        elements of L_C are based.
Output
 I   :  a minimum length conjunction of the elements of L_A that
        are satisfied c, such that I is satisfied by none of L_F.
======================================================================*/
#include "qepcad.h"

Word IMPCONS(Word c, Word L_F, Word L_A, Word P)
{
     Word I,A,n,S,F,f,S_f,Ap,i,T,L;

Step1: /* Initialize. Set A to the sublist of L_A stasified by c. */
     if (L_F == NIL) {
       I = LIST1(TRUE);
       goto Return; }
     for(A = NIL, L = L_A; L != NIL; L = RED(L))
       if (FMACELLEVAL(FIRST(L),c,P) == TRUE)
	 A = COMP(FIRST(L),A);
     n = LENGTH(A);
     S = NIL;

Step2: /* Construct the minimum hitting set problem. */
     for(F = L_F; F != NIL; F = RED(F)) {
       f = FIRST(F);
       S_f = NIL;
       for(i = n, Ap = A; Ap != NIL; i--,Ap = RED(Ap))
	 if (FMACELLEVAL(FIRST(Ap),f,P) == FALSE)
	   S_f = COMP(i,S_f);
       S = COMP(S_f,S); }
	
Step3: /* Get the hitting set. */
     T = MINHITSETSR(S,-1);
     if (!ISLIST(T)) {
       I = 0;
       goto Return; }

Step4: /* Convert hitting set to an implicant. */
     T = LBIBMS(T);
     for(I = NIL, L = INV(A), i = 1; T != NIL; i++, L = RED(L))
       if (i == FIRST(T)) {
	 T = RED(T);
	 I = COMP(FIRST(L),I); }
     if (LENGTH(I) == 1)
       I = FIRST(I);
     else
       I = COMP(ANDOP,INV(I));
  
Return: /* Prepare to return. */
     return I;
}
