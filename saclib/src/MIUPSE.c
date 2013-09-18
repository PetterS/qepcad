/*===========================================================================
                         MIUPSE(M,A,B,S,T,C; U,V)

Modular integral univariate polynomial, solution of equation.

Inputs
  M   : in Z, M > 0.
  A,B,S,T : in Z/(M)[X], ldcf(A) a unit, deg(T) < deg(A),
            and A*S + B*T = 1.
  C   : in Z/(M)[X].

Outputs
  U,V : in Z/(M)[X], U and V are unique elements such that A*U + B*V = C,
        and deg(V) < deg(A).
===========================================================================*/
#include "saclib.h"

void MIUPSE(M,A,B,S,T,C, U_,V_)
       Word M,A,B,S,T,C, *U_,*V_;
{
       Word J,K,L,Q,U,V,Y,h,k,m,n;

Step1: /* Compute. */
       n = PDEG(C);
       h = PDEG(A);
       k = PDEG(B);
       m = MAX(n - h + 1,k);
       Y = MIPPR(1,M,T,C);
       MIUPQR(M,Y,A,&Q,&V);
       J = IUPTPR(m,S,C);
       K = IUPTPR(m,B,Q);
       L = IPSUM(1,J,K);
       U = MIPHOM(1,M,L);

Return: /* Prepare for return. */
       *U_ = U;
       *V_ = V;
       return;
}
