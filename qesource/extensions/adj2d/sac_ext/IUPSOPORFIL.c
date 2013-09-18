/*======================================================================
                       L <- IUPSOPOR(A,B,R)


Integral univariate polynomial signs of polynomial on roots from 
isolation list.

Inputs
   A : a primitive squarefree univariate integral polynomial.
   B : a univariate integral polynomial, A and B relatively prime.
   R : a list of isolating (logarithmic standard) intervals for
       roots of A.

Outputs                          
   L : a list (L_1,L_2,...,L_n), where L_i = (s_i,I_i).  (I_1,...,I_n)
       is a list of standard logarithmic isolationg intervals for the
       roots of A isolated in R.
       B has constant sign
       in each I_i, and s_i is the sign of B in I_i, and thus 
       specifically at the root of A in I_i.
======================================================================*/
#include "sac_ext.h"

Word IUPSOPORFIL(Word A, Word B, Word R)
{
     Word L,Bp,Lp,J,j1,j2,t,j,tp,s;

Step1: /* Initialize. */
     L  = R;
     Bp = IPPGSD(1,B);
  
Step2: /* Loop over each interval in L. */
     Lp = NIL;
     while(L != NIL) {
       ADV(L,&J,&L);
       FIRST2(J,&j1,&j2);
       t = LBRNSIGN(IUPLBREVAL(A,j2));
       if (t != 0) {

Step3: /* Refine (j1,j2) until Bp has no zeros. */
	 do {
	   j = LSIM(j1,j2);
	   tp = LBRNSIGN(IUPLBREVAL(A,j));
	   if (tp == t)
	     j2 = j;
	   else 
	     j1 = j;
	 }while(IUPVSI(Bp,LIST2(j1,j2)) != 0);
       }

Step4: /* Compute the sign of B in (j1,j2) and add to Lp. */
       s = LBRNSIGN(IUPLBREVAL(B,LSIM(j1,j2)));
       Lp = COMP(LIST2(s,LIST2(j1,j2)),Lp);
     }

Return: /* Prepare to return; */     
     L = INV(Lp);
     return L;
    
}
