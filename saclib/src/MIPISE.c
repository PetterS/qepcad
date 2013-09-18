/*======================================================================
                      MIPISE(r,M,D,A,B,S,T,C; U,V)

Modular integral polynomial mod ideal, solution of equation.

Inputs
  r : a BETA-digit, r >= 1.
  M : in Z, M > 0.
  D : a list (d1,...,d_{r-1}), with di BETA-digits, di >= 0.
  A,B,S,T : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),
      with A monic, deg_Y(A) > 0, and A*S + B*T = 1.
  C : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),

Outputs
  U,V : in Z/(M)[X1,...,X_{r-1},Y]/(X1^d1,...,X_{r-1}^d_{r-1}),such
        that A*U+B*V = C, and deg_Y(V) < deg_Y(A).
======================================================================*/
#include "saclib.h"

void MIPISE(r,M,D,A,B,S,T,C, U_,V_)
       Word r,M,D,A,B,S,T,C, *U_,*V_;
{
       Word Q,U,V,W,Y,Z;

Step1: /* Compute. */
       W = MIPIPR(r,M,D,T,C);
       MMPIQR(r,M,D,W,A,&Q,&V);
       Y = MIPIPR(r,M,D,S,C);
       Z = MIPIPR(r,M,D,B,Q);
       U = MIPSUM(r,M,Y,Z);

Return: /* Prepare for return. */
       *U_ = U;
       *V_ = V;
       return;
}
