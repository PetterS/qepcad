/*======================================================================
                      L <- IPPSCT(r,A,B,S)

Integral polynomial principal subresultant coefficients test.

Inputs:
 A, B  : in Z[x1,...,xr], r >= 2, of positive degree in xr. 
 S     : (S1,...,Sn), n >= 0, where Si in Z[x1,...,x{r-1}].

Outputs:
 L     : (psc_(A,B),psc_1(A,B),...,psc_k(A,B)), where 0 <= k < min(deg(A),deg(B)).  
         Either k is minimal such that psc_0(A,B),...,psc_k(A,B) 
         and the polynomials of S are known to have at most finitely 
         many common zeros, or k = min(deg(A),deg(B))-1.
======================================================================*/
#include "qepcad.h"

Word QepcadCls::IPPSCT(Word r, Word A, Word B, Word S)
{
       Word L,M,N,Sp,t;

Step1: /* Compute it. */
       M = IPPSC(r,A,B); 
       L = NIL; 
       Sp = S; 
       do 
         { 
         ADV(M,&N,&M);
         L = COMP(N,L); 
         Sp = COMP(N,Sp); 
         t = IPFZT(r - 1,Sp); 
         }
       while (!(t == 1 || M == NIL)); 
       L = INV(L); 

Return: /* Prepare for return. */
       return(L);
}
