/*======================================================================
                     Ap <- ASSUMPTIONSRATVEVAL(A,i,R,r)

Assumptions rational value evaluate.

Inputs
  A : a QEPCAD formula ... normalized or unnormalized doesn't matter.
  i : a BDigit
  R : a rational number
  r : a BDigit

      
Outputs
  Ap: an unnormalized QEPCAD formula in which all polynomials are
      r-variate that is equivalent to A with the substitution 
      x_i = R.
======================================================================*/
#include "qepcad.h"

Word ASSUMPTIONSRATVEVAL(Word A, BDigit i, Word R, BDigit r)
{
       Word Ap;
       if (A == TRUE || A == FALSE) {
	 Ap = A;
	 goto Return; }

//Step1: /* NOT OP */
       if (FIRST(A) == NOTOP)
       {
	 Word t = ASSUMPTIONSRATVEVAL(SECOND(A),i,R,r);
	 if      (t == TRUE)  Ap = FALSE;
	 else if (t == FALSE) Ap = TRUE;
	 Ap = LIST2(NOTOP,t);
       }

//Step2: /* Disjunction. */
       else if (FIRST(A) == OROP)
       {
	 Ap = NIL;
	 for(Word L = CINV(RED(A)); L != NIL; L = RED(L))
	 {
	   Word S = ASSUMPTIONSRATVEVAL(FIRST(L),i,R,r);
	   if (S == TRUE) {
	     Ap = TRUE;
	     goto Return; }
	   else if (S != FALSE)
	     Ap = COMP(S,Ap);
	 }
	 if (Ap == NIL)
	   Ap = FALSE;
	 else
	   Ap = COMP(OROP,Ap);
	 goto Return;
       }

//Step3: /* Conjunction. */
       else if (FIRST(A) == ANDOP)
       {
	 Ap = NIL;
	 for(Word L = CINV(RED(A)); L != NIL; L = RED(L))
	 {
	   Word S = ASSUMPTIONSRATVEVAL(FIRST(L),i,R,r);
	   if (S == FALSE) {
	     Ap = FALSE;
	     goto Return; }
	   else if (S != TRUE)
	     Ap = COMP(S,Ap);
	 }
	 if (Ap == NIL)
	   Ap = TRUE;
	 else
	   Ap = COMP(ANDOP,Ap);
	 goto Return;
       }

//Step4: /* Tarski Atomic formula! */
       else if (FIRST(A) != IROOT)
       {
	 Word T_A,P_A,k_A,s,rp,Pp,P,a,T;
	 FIRST3(A,&T_A,&P_A,&k_A);
	 if (i > k_A) {
	   Ap = A;
	   goto Return; }

	 /* Evaluate poly, make integral, change relop if needed */
	 Word Prn = IPRNEVAL(k_A,P_A,i,R);
	 IPSRP(k_A,Prn,&a,&P);
	 if (RNSIGN(a) < 0) {
	   if (T_A == LEOP) T = GEOP;
	   else if (T_A == GEOP) T = LEOP;
	   else if (T_A == LTOP) T = GTOP;
	   else if (T_A == GTOP) T = LTOP;
	   else T = T_A;
	 }
	 else
	   T = T_A;

	 PSIMREP(k_A,P,&rp,&Pp);
	 if (rp > 0) {
	   Ap = LIST4(T,RVSPTSVSP(k_A,P,r),r,NIL);
	   goto Return; }
	 if (P == 0)
	   s = 0;
	 else
	   s = ISIGNF(PLBCF(rp,Pp));
	 switch (T)
         {
         case LTOP: if (s < 0)  Ap = TRUE; else Ap = FALSE; break;
         case LEOP: if (s <= 0) Ap = TRUE; else Ap = FALSE; break;
         case GTOP: if (s > 0)  Ap = TRUE; else Ap = FALSE; break;
         case GEOP: if (s >= 0) Ap = TRUE; else Ap = FALSE; break;
         case EQOP: if (s == 0) Ap = TRUE; else Ap = FALSE; break;
         case NEOP: if (s != 0) Ap = TRUE; else Ap = FALSE; break;
         }
	 goto Return;
       }
       
//Step5: /* Extended Tarski Atomic formula! */
       else {
	 /* I might address this later! For now I do nothing! */
	 Ap = A;
	 goto Return;
       }

Return: /* Prepare for return. */
       return Ap;
}


/*======================================================================
                     Ap <- ASSUMPTIONSRATVEVAL(A,C,r)

Assumptions rational values evaluate.                      

Inputs
  A : a QEPCAD formula ... normalized or unnormalized doesn't matter.
  r : a BDigit
  C : a (possibly empty) list of SACLIB polynomials of the form 
      A x_i + B, where A,Z \in Z and 1 <= i <= r.  No two elements of
      this list should have the same x_i. 

Outputs
  Ap: an unnormalized QEPCAD formula in which all polynomials are
      r-variate that is equivalent to A with the rational substitutions
      from the list C.
======================================================================*/
#include "qepcad.h"
// Word ASSUMPTIONSRATVEVAL(Word A, Word C, BDigit r)
// {
//   Word S, Cp, rp, P;

//  Step1: /* Find list of substitutions as (i,A/B) pairs */
//   S = NIL;
//   for(Cp = C; Cp != NIL; Cp = RED(Cp))
//   {
//     PSIMREP(r,FIRST(Cp),&rp,&P);
//     A = PLBCF(rp,P);
//     B = PTBCF(rp,P);
//     S = COMP(LIST2(rp,RNRED(B,A)));
//   }

// Step2: /* Make substitutions */
  
// }
