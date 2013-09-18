/*======================================================================
                      EXTRACTS(F,A; Ap)

Extract polynomials from a quantifier--free formula, Subalgorithm.
 
\Input
  \parm{F} is a non--constant normalized quantifier-free formula.
  \parm{A} is a list~$(A_1,\ldots,A_r)$ where each $A_i$ is
           the list of all the $i$--level polynomials found
           util the call to this algorithm was made.
\Output
  \parm{A'} is the list~$(A'_1,\ldots,A'_r)$ where each $A'_i$ is
           obtained by appending to $A_i$ all the $i$--level
           polynomials in $F$ if there are not there yet.

\SideEffect
   \parm{F} is modified in that each polynomial is assigned to
           an index.
   \parm{A} is modified.
======================================================================*/
#include "qepcad.h"
static void ADD2A(Word P, BDigit k, Word *A_, Word *L_);

void EXTRACTS(Word F, Word A, Word *Ap_)
{
        Word T,P,k,I,L,j,Pp,Ap,Fp,F_i,X;

Step1: /* Non-constant normalized atomic formula. */
        if (!ISATOMF(F)) goto Step3;
	if (FIRST(F) == IROOT) goto Step2;
        FIRST4(F,&T,&P,&k,&I);
	if (k == 0) { Ap = A; goto Return; }
	ADD2A(P,k,&A,&L);
	SLELTI(F,4,L);
        Ap = A;
        goto Return;

Step2: /* Normalized atomic Extended Tarski formula */
	FIRST6(F,&X,&T,&j,&P,&k,&I);
	I = NIL;
	for(Pp = CINV(P); Pp != NIL; Pp = RED(Pp))
	{
	  ADD2A(FIRST(Pp),k,&A,&L);
	  I = COMP(L,I);
	}
	SLELTI(F,6,I);
	Ap = A;
	goto Return;

Step3: /* Other. */
        Ap = A; Fp = RED(F);
        while (Fp != NIL) { ADV(Fp,&F_i,&Fp); EXTRACTS(F_i,Ap,&Ap); }
        goto Return;

Return: /* Prepare for return. */
       *Ap_ = Ap;
       return;
}

/*======================================================================
                      ADD2A(P,k;A,L)

Add to "A"
 
\Input
  P : a k-variate saclib polynomial
  k : the level of P (as well as its "variate-ness")
  A : the list of polynomials extracted from the input formula thus far

\SideEffect
  A : is modified if P does not already appear in it
  L : L is set to the label (i.e. pair (i,j) ) of P in A
======================================================================*/
void ADD2A(Word P, BDigit k, Word *A_, Word *L_)
{
        Word A,A_k,As_k,n,i,As_k_i,Ap,L,Q,Ap_k;

Step1: /* Initialize */
        A = *A_;
        A_k = LELTI(A,k);

Step2: /* Search A for P */
        As_k = A_k; n = LENGTH(A_k);
        for (i = 1; i <= n; i++)
	{
          ADV(As_k,&As_k_i,&As_k);
          if (EQUAL(P,LELTI(As_k_i,PO_POLY)))
	  { 
	    L = LIST2(k,i); 
	    Ap = A; 
	    goto Return; 
	  }
	}

Step3: /* P not found in A */
        L = LIST2(k,n + 1); 
        Q = MPOLY(P,LIST3(LFS("A"),k,n+1),NIL,PO_OTHER,PO_KEEP);
        Ap_k = SUFFIX(A_k,Q); 
        SLELTI(A,k,Ap_k); 
        Ap = A;
        goto Return;

Return: /* Prepare to return */
	*A_ = Ap;
	*L_ = L;
	return;
}
