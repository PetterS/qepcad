/*======================================================================
                      IPLCPP(r,A; C,P)

Integral polynomial list of contents and primitive parts.

Inputs
  r : a BETA-digit, r > 0. 
  A : a list (A1,...,An), n >= 0, of polynomials in Z[X1,...,Xr].

Outputs
  C : a list (C1,...,Cs), 0 <= s <= n, of elements of Z[X1,...,X_{r-1}]
      such that
      for 1 <= i <= n, content(Ai) = Cj for some j, 1 <= j <= s,
      if and only if content(Ai) has positive degree in some variable.
  P : a list (P1,...,Pm), 0 <= m <= n, of polynomials in Z[X1,...,Xr]
      such that for 1 <= i <= n, primitive_part(Ai) = Pj for some j,
      1 <= j <= m, if and only if primitive_part(Ai) has positive degree
      in its main variable.
======================================================================*/
#include "saclib.h"

void IPLCPP(r,A, C_,P_)
       Word r,A, *C_,*P_;
{
       Word A1,Ap,C,C1,P,P1,rp,s;
       /* hide A1,Ap,rp,s; */

Step1: /* Compute. */
       C = NIL;
       P = NIL;
       Ap = A;
       rp = r - 1;
       while (Ap != NIL)
         {
         ADV(Ap,&A1,&Ap);
         IPSCPP(r,A1,&s,&C1,&P1);
         if (!PCONST(rp,C1))
           C = COMP(C1,C);
         if (PDEG(P1) > 0)
           P = COMP(P1,P);
         }
       C = INV(C);
       P = INV(P);

Return: /* Prepare for return. */
       *C_ = C;
       *P_ = P;
       return;
}
