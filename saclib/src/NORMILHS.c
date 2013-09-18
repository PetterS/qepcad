/*===========================================================================
	     NORMILHS(N,q,Q,Ap,B,S,T; Y,Z,Us,As,Bs)

Norm polynomial initial linear Hensel step.

Inputs
  N : in Z[x], the norm of a polynomial A[alpha,x] in Z[alpha][x],
      where alpha is an algebraic number.  N is squarefree.
  q : a single-precision power of an odd prime p.
  Q : in Z, Q = q^2.
  Ap : a list of pairs ((d_1,F_1),...,,(d_s,F_s)).  Let M be the
       minimal polynomial of alpha, and let M_1 * ... * M_s be a
       complete factorization of M (mod p).  Then d_i = deg(M_i)
       and F_i is a list of distinct monic factors of
       N_i = res_t(M_i(t),A(t,x)) (mod q).
       Let (a_1,...,a_r) be the list of all the elements of the
       lists F_1,...,F_s.
  B,S,T : lists (b_1,...,b_{r-1}), (s_1,...,s_{r-1}),
          (t_1,...,t_{r-1}) of elements of Z/(q)[x] such that
	  b_{i-1} = a_i b_i, for i = 2,...,r-1, and a_i s_i +
	  b_i t_i = 1, deg(s_i) < deg(b_i), deg(t_i) < deg(a_i)
	  for i = 1,...,r-1.

Outputs
  Y,Z : lists (y_1,...,y_{r-1}),(z_1,...,z_{r-1}) of elements
        of Z/(q)[x]. 
  Us : a list (u_1,...,u_{r-1}) of elements of Z[x].
       y_i, y_i, u_i satisfy a_i y_i + b_i z_i = u_i (mod q).
  As : a list of pairs ((d_1,As_1),...,(d_s,As_s)).
       Let F_i = (f_1,...,f_k).  Then As_i = (g_1,...,g_k), where
       g_i is an element of Z/(Q)[x] and f_j = H_q(g_k).
       Let as_1,...,as_r be all the elements of the lists As_1,...,As_s.
       Then the monic associate of N is congruent to as_1*...*as_r.
  Bs : a list (bs_1,...,bs_{r-1}) of elements of Z/(Q)[x]. b_i = H_q(bs_i).
===========================================================================*/
#include "saclib.h"

void NORMILHS(N,q,Q,Ap,B,S,T, Y_,Z_,Us_,As_,Bs_)
       Word N,q,Q,Ap,B,S,T, *Y_,*Z_,*Us_,*As_,*Bs_;
{
       Word A,Ab,As,Bs,Us,Y,Z;

Step1: /* Form a single list from the elements of the F_i. */
       A = NORMFL(Ap);

Step2: /* Lift. */
       IUPILHS(q,Q,A,B,S,T,N, &Y,&Z,&Us,&Ab,&Bs);

Step3: /* Regroup the elements of At. */
       As = NORMRL(Ap,Ab);

Return: /* Prepare for return. */
       *Y_  = Y;
       *Z_  = Z;
       *Us_ = Us;
       *As_ = As;
       *Bs_ = Bs;
       return;
}
