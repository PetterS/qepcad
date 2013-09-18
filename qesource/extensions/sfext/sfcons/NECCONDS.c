/*======================================================================
                 SF <- NECCONDS(L_T,L_F,L_A,P)

Necessary Conditions

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

Word NECCONDS(Word L_T, Word L_F, Word L_A, Word P)
{
     Word SF,Lp,N,a,t,Fp,SFp,A,n,S,f,S_f,T,I,i,Ap,L;

Word t1,t2,t3;
t1 = ACLOCK();

Step1: /* Construct N, the list of necessary conditions. */
     for(Lp = CINV(L_A), N = NIL; Lp != NIL; Lp = RED(Lp)) {
       a = FIRST(Lp);
       for(t = TRUE,T = L_T; t == TRUE && T != NIL; T = RED(T))
	 t = FMACELLEVAL(a,FIRST(T),P);
       if (t == TRUE)
	 N = COMP(a,N); }

Step2: /* Construct Fp, the list of false cells satisfying N. */
     for(Lp = CINV(L_F), Fp = NIL; Lp != NIL; Lp = RED(Lp))
       if (FMACELLEVAL(COMP(ANDOP,N),FIRST(Lp),P) != FALSE)
	 Fp = COMP(FIRST(Lp),Fp);

t1 = ACLOCK() - t1;
t2 = ACLOCK();

Step3: /* Construct formula for simplified problem. */
     SFp = NAIVESF(L_T,Fp,L_A,P);

t2 = ACLOCK() - t2;
t3 = ACLOCK();

Step4: /* Construct Fp, the list of false cells satisfying SFp. */
     for(Lp = CINV(L_F), Fp = NIL; Lp != NIL; Lp = RED(Lp))
       if (FMACELLEVAL(SFp,FIRST(Lp),P) != FALSE)
	 Fp = COMP(FIRST(Lp),Fp);
     if (Fp == NIL) {
       SF = SFp;
       goto Return; }

Step5: /* Construct the minimum hitting set problem. */
     A = CINV(N);
     n = LENGTH(A);
     for(S = NIL; Fp != NIL; Fp = RED(Fp)) {
       f = FIRST(Fp);
       S_f = NIL;
       for(i = n, Ap = A; Ap != NIL; i--,Ap = RED(Ap))
         if (FMACELLEVAL(FIRST(Ap),f,P) == FALSE)
           S_f = COMP(i,S_f);
       S = COMP(S_f,S); }

Step6: /* Get the hitting set. */
     T = MINHITSETSR(S,-1);

Step7: /* Convert hitting set to a formula. */
     T = LBIBMS(T);
     for(I = NIL, L = N, i = 1; T != NIL; i++, L = RED(L))
       if (i == FIRST(T)) {
         T = RED(T);
         I = COMP(FIRST(L),I); }
     if (LENGTH(I) == 1)
       I = FIRST(I);
     else
       I = COMP(ANDOP,INV(I));

Step8: /* Join I and SFp. */
     SF = LIST3(ANDOP,I,SFp);

Return: /* Prepare to return. */

t3 = ACLOCK() - t3;
if (PCVERBOSE) {
SWRITE("\nNECCONDS: t1 = ");IWRITE(t1);SWRITE(" t2 = ");
IWRITE(t2);SWRITE(" t3 = ");IWRITE(t3);SWRITE("\n\n"); }
     return SF;     
}


