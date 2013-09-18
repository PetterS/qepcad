/*======================================================================
                 X <- MINCOVBF(L_C,L_F,P)

Minimum cover by formulas.

Inputs
 L_C : a list of cells (PCAD or ESPCAD, depending on L_F)
 L_F : a list of FMA formulas
 P   : the projection factor set upon which the signitures of the
       elements of L_C are based.
Output
 X   : a sublist of L_F comprising a minimum length cover of L_C.  If
       such does not exist, X is zero.  Note that X = NIL if L_C = NIL.
======================================================================*/
#include "qepcad.h"

Word MINCOVBF(Word L_C, Word L_F, Word P)
{
     Word X,F,n,S,T,C,c,S_c,i,Fp,L;

Step1: /* Initialize. */
     if (L_C == NIL) {
       X = NIL;
       goto Return; }
     if (L_F == NIL) {
       X = 0;
       goto Return; }
     if (LENGTH(L_F) == 1) {
       X = L_F;
       goto Return; }
     F = CINV(L_F);
     n = LENGTH(F);
     S = NIL;

Step2: /* Construct the minimum hitting set problem. */
     for(C = L_C; C != NIL; C = RED(C)) {
       c = FIRST(C);
       S_c = NIL;
       for(i = n, Fp = F; Fp != NIL; i--,Fp = RED(Fp))
	 if (FMACELLEVAL(FIRST(Fp),c,P) == TRUE)
	   S_c = COMP(i,S_c);
       S = COMP(S_c,S); }
	
Step3: /* Get the hitting set. */
     T = MINHITSETSR(S,-1);
     if (!ISLIST(T)) {
       X = 0;
       goto Return; }

Step4: /* Convert hitting set to a cover by formulas. */
     T = LBIBMS(T);
     for(X = NIL, L = L_F, i = 1; T != NIL; i++, L = RED(L))
       if (i == FIRST(T)) {
	 T = RED(T);
	 X = COMP(FIRST(L),X); }
     X = INV(X);
  
Return: /* Prepare to return. */
     return X;
}
