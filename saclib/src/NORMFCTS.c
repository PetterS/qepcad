/*===========================================================================
	      NORMFCTS(N,p,Q,Qp,q,K,L,d,W1,N1; F,Nb,Ib)

Norm polynomial factor combination test subroutine.

Inputs
  N : the norm of a polynomial A[alpha,x] in Z[alpha][x], where
      alpha is an algebraic number.  N is squarefree.
  p : an odd medium prime.
  Q : a positive power of p.  
  Qp: the floor function of the square root of Q/2.
  q : a BETA-digit, q = ILOG2(Qp).
  K : a list of lists of modular factors for the trial combination.
  L : a (possibly empty) list of pairs ((d_2,L_2),...,(d_s,L_s)).
      Let M be the minimal polynomial of alpha, and let M_1 *
      M_2 * ... * M_s be a complete factorization of M (mod p).
      Then d_i = deg(M_i) and L_i is a pair (n_i,A_i), where A_i
      is a GCArray containing the distinct monic irreducible
      factors (with tags) of res_t(M_i(t),A(t,x)) (mod p).
  T : a (possibly empty) list (T_1,...,T_s) of GCA handles.  The
      jth element of T_i is the value of the the jth element of
      A_i evaluated at 1.
  d : a BETA-digit, the degree of the possible factor of A[alpha,x].
  W0 : the product of the elements of K evaluated at 1.
  N1 : in Z, N1 = N(1).

Outputs
  F  : an irreducible factor of N (may be = 1).
  Nb : N divided by F.
  Ib : a (possible empty) list of lists I_i of indices j_i such
       that if f_{j_i} is the j_ith element of L_i, then f_{j_i}
       was combined to produce F.
===========================================================================*/
#include "saclib.h"

void NORMFCTS(N,p,Q,Qp,q,K,L,T,d,W0,N1, F_,Nb_,Ib_)
       Word N,p,Q,Qp,q,K,L,T,d,W0,N1, *F_,*Nb_,*Ib_;
{
       Word A,A1,C,F,*I,I1,Ib,Kp,L1,Lp,Nb,Tp,T1,W,W1,
            e,f,i,k,max,min,n,t,tp;

Step1: /* L = NIL. */
       if (L == NIL) {
	  NORMFT(N,p,Q,Qp,q,K,W0,N1,&F,&Nb);
	  Ib = NIL;
	  goto Return; }

Step2: /* Get the next group of factors and compute the degree e
	  that the degree of the product must equal. */
       ADV(L,&L1,&Lp);
       FIRST2(L1,&e,&L1);
       e = e*d;
       FIRST2(L1,&n,&A);
       ADV(T,&T1,&Tp);

Step3: /* Initialize number of factors to combine. */
       k = 1;

Step4: /* Check minimum and maximum possible degree. */
       min = max = 0;
       for (i = 0; i < k; i++)
	  max += PDEG(SECOND(GCAGET(A,i)));
       if (max < e) /* not enough factors. */
	  goto Step10;
       for (i = n-1; i >= n - k; i--)
	  min += PDEG(SECOND(GCAGET(A,i)));
       if (min > e) /* too many factors. */
	  goto Step11;
       
Step5: /* Initialize I,  combination array
	             W,  the array for the products of the polynomials
                         evaluated at 1
		     t,  the last changed index in combination and
		     tp, the last changed index in trailing
                         coefficient product. */
       I = GETARRAY(k);
       for (i = 0; i < k; i++)
	  I[i] = i;
       W = GCAMALLOC(k,GC_CHECK);
       t = tp = 0;

Step6: /* Get combination of factors and compute degree of product. */ 
       C = NIL;
       f = 0;
       for (i = 0; i < k; i++) {
	  A1 = SECOND(GCAGET(A,I[i]));
	  f += PDEG(A1);
	  C = COMP(A1,C); }
       if (f != e)
	  goto Step9;
       Kp = COMP(C,K);
       
Step7: /* Update the trailing coefficient product. */
       if (tp == 0)
	  W1 = W0;
       else
	  W1 = GCAGET(W,tp-1);
       for (i = tp; i < k; i++) {
	  W1 = MIPROD(Q,GCAGET(T1,I[i]),W1);
	  GCASET(W,i,W1); }
       tp = t;

Step8: /* Recursion. */
       NORMFCTS(N,p,Q,Qp,q,Kp,Lp,Tp,d,W1,N1, &F,&Nb,&Ib);
       if (PDEG(F) > 0) {
	  I1 = NIL;
	  for (i = k-1; i >= 0; i--)
	     I1 = COMP(I[i],I1);
	  Ib = COMP(I1,Ib);
	  goto Return; }

Step9: /* Get next combination, if any. */
       LEXNEXTC(n,k,I,&t);
       if (t < tp)
	  tp = t;
       if (I[0] >= 0)
	  goto Step6;
       FREEARRAY(I);

Step10: /* Increment number of factors to combine. */
       k++;
       if (k < n)
	  goto Step4;

Step11: /* No factors found. */
       F = PMON(1,0);
       Nb = N;
       Ib = NIL;

Return: /* Prepare for return. */
       *F_   = F;
       *Nb_  = Nb;
       *Ib_  = Ib;
       return;
}
