/*===========================================================================
		  NORMSQHL(N,p,q,F,&A,&B,&S,&T)

Norm polynomial single-precision quadratic Hensel lifting.

Inputs
  N : in Z[x], the norm of a polynomial A[alpha,x] in Z[alpha][x],
      where alpha is an algebraic number.  N is squarefree.
  p : an odd medium prime.
  q : a single-precision power of p.
  F : a list of pairs ((d_1,F_1),...,,(d_s,F_s)).  Let M be the
      minimal polynomial of alpha, and let M_1 * ... * M_s be a
      complete factorization of M (mod p).  Then d_i = deg(M_i)
      and F_i is a list of the distinct monic irreducible factors
      N_i = res_t(M_i(t),A(t,x)) (mod p).

Outputs
  A : a list of pairs ((d_1,A_1),...,(d_s,A_s)).
      Let F_i = (f_1,...,f_k).  Then A_i = (g_1,...,g_k), where
      g_i is an element of Z/(q)[x] and f_j = H_p(g_k).
      Let a_1,...,a_r be all the elements of the lists A_1,...,A_s.
      Then the monic associate of N is congruent to a_1*...*a_r.
  B : a list (b_1,...b_{r-1}) of elements of Z/(q)[x] such that
      N is congruent to a_1 * ... * a_i * b_i.
  S : a list (s_1,...,s_{r-1}) of elements of Z/(q)[x];
  T : a list (t_1,...,t_{r-1}) of elements of Z/(q)[x];
      such that a_i*s_i + b_i*t_i = 1, deg(t_i) < deg(a_i).
===========================================================================*/
#include "saclib.h"

void NORMSQHL(N,p,q,F,A_,B_,S_,T_)
       Word N,p,q,F, *A_,*B_,*S_,*T_;
{
       Word A,Ap,B,G,S,T;

Step1: /* Form a single list from the elements of the F_i. */
       G = NORMFL(F);

Step2: /* Lift. */
       IUPSQHLL(p,q,G,N,&Ap,&B,&S,&T);

Step3: /* Regroup the elements of Ap. */
       A = NORMRL(F,Ap);

Return: /* Prepare for return. */
       *A_ = A;
       *B_ = B;
       *S_ = S;
       *T_ = T;
}
