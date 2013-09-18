/*======================================================================
                      ASSPR(A; p,m)

Assignment problem.

Inputs
   A : an n by n square matrix of BETA-digits.

Outputs
   p : an n-permutation for which A[1,p(1)] + ... + A[n,p(n)] is maximal.
   m : in Z, the maximal sum above.

Algorithm
   See "Combinatorial Theory" by Marshall Hall, Jr, Blaisdell Pub. Co,
   1967, pages 58-62.

Analysis
   Let M_i be the maximum of the elements in row i of A and let M be
   the sum of the M_i.  Let m be the maximal sum above.  Then the
   computing time is dominated by (M - m + 1) n^3.
======================================================================*/
#include "saclib.h"

void ASSPR(A, p_,m_)
       Word A, *p_,*m_;
{
	BDigit  a11,i,j,m,u1,v1;
        Word A1,Ap,I,Ip,J,p,S,S1,Sp,U,Us,V,Vs;

Step1: /* Set U = (u_1,...,u_n) where u_i is the maximum of the
          elements in row i of A and V = (0,...,0). */

        Ap = A;
        U = NIL;
        V = NIL;
        do {
           ADV(Ap,&A1,&Ap);
           ADV(A1,&u1,&A1);
           while (A1 != NIL) {
              ADV(A1,&a11,&A1);
              u1 = MAX(u1,a11); }
           U = COMP(u1,U);
           V = COMP(0,V); }
        while (Ap != NIL);
        U = INV(U);
        V = INV(V);

Step2: /* Compute S = (S_1,...,S_n) where. S_i = {j: u_1 + v_j = a_{i,j}. */
        S = NIL;
        Ap = A;
        Us = U;
        do {
           S1 = NIL;
           ADV(Ap,&A1,&Ap);
           ADV(Us,&u1,&Us);
           Vs = V;
           j = 1;
           do {
              ADV(Vs,&v1,&Vs);
              ADV(A1,&a11,&A1);
              if (u1 + v1 == a11)
                 S1 = COMP(j,S1);
              j = j + 1; }
           while (Vs != NIL);
           S1 = INV(S1);
           S = COMP(S1,S); }
        while (!(Ap == NIL));
        S = INV(S);

Step3: /* Solve the SDR problem for S. */
        SDR(S,&p,&I);

Step4: /* Optimal assignment found, compute its value.. */
        if (p != NIL) {
           m = 0;
           Us = U;
           Vs = V;
           do {
              ADV(Us,&u1,&Us);
              ADV(Vs,&v1,&Vs);
              m = m + u1 + v1; }
           while (Us != NIL);
           goto Return; }

Step5: /* No SDR, compute the union J of the sets S_i such that 
          i is in I. */

        J = NIL;
        Sp = S;
        Ip = I;
        i = 1;
        do {
           ADV(Sp,&S1,&Sp);
           if (Ip != NIL && FIRST(Ip) == i) {
              Ip = RED(Ip);
              J = SUNION(J,S1); }
           i = i + 1; }
        while (Ip != NIL);

Step6: /* Replace u_i by u_i - 1 for all i in I  Replace v_j by v_j + 1
          for all j in J.  Then return to Step 2. */

        Us = U;
        i = 1;
        do {
           if (I != NIL && FIRST(I) == i) {
              SFIRST(Us,FIRST(Us) - 1);
              I = RED(I); }
           Us = RED(Us);
           i = i + 1; }
        while (I != NIL);
        Vs = V;
        j = 1;
        do {
           if (J != NIL && FIRST(J) == j) {
              SFIRST(Vs,FIRST(Vs) + 1);
              J = RED(J); }
           Vs = RED(Vs);
           j = j + 1; }
        while (J != NIL);
        goto Step2;

Return: /* Return p and m. */
       *p_ = p;
       *m_ = m;
       return;
}
