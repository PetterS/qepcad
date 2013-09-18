/*======================================================================
                      t <- IPFZT1(r,A)

Integral polynomial finitely many common zeros test, one variable.    
A = (A_1(x_1,...,x_r),...,A_n(x_1,...,x_r)), n >= 0, is a list of 
nonzero integral polynomials in r variables, r >= 1.  T = 1 if it 
has been determined that the common zeros of A_1,...,A_n have only 
finitely many distinct x_1 coordinates.  T = 0 if either A eq (), or 
if it has not been determined how many distinct x_1 coordinates the 
common zeros of A_1,...,A_n have, or if it has been determined that
they have infinitely many distinct x_1 coordinates.
======================================================================*/
#include "qepcad.h"

Word IPFZT1(Word r, Word A)
{
       Word A1,Ap,B1,C,I,L,L1,Lp,P,P1,P2,R,R1,S,b,c,rp,s,t;
       /* hide A1,Ap,B1,L1,b,c,rp,s,t; */

Step1: /* A = () or r=1. */
       t = 1; 
       if (A == NIL) { t = 0; goto Return; }
       if (r == 1) goto Return;

Step2: /* Factor each A_i. */ 
       rp = r - 1; S = NIL; Ap = A; 
       do
         { 
         ADV(Ap,&A1,&Ap); IPFACDB(r,A1,&s,&c,&L); Lp = NIL; 
         while (L != NIL) 
           { ADV(L,&L1,&L); Lp = COMP(SECOND(L1),Lp); }
         Lp = INV(Lp); S = COMP(Lp,S); 
         } while (!(Ap == NIL));
        S = PAIR(S,S);

Step3: /* Test tuples of factors. */ 
       C = NIL; P = NIL; CPLEXN(S,&I,&S); 
       do 
         { 
         ADV(I,&B1,&I); 
         if (PDEG(B1) == 0) C = COMP(PLDCF(B1),C); else P = COMP(B1,P); 
         } while (!(I == NIL));
       R = NIL; 
       if (P != NIL) ADV(P,&P1,&P); 
       while (P != NIL)
         { 
         ADV(P,&P2,&P); R1 = IPRES(r,P1,P2); s = PUNT(rp,R1);
         if (s == 2 && R1 != 0) goto Return; 
         if (s == 1) { if (S != NIL) goto Step3; else goto Return; }
         if (R1 != 0) R = COMP(R1,R); 
         } 
       L = CONC(C,R);
       b = IPFZT1(rp,L); 
       if (b == 0) { t = 0; goto Return; }
       if (S != NIL) goto Step3; 
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
