/*=====================================================================
                        L <- IPSBLSSIL(A)

Integral polynomial squarefree basis labeled strong standard
isolation list.

Input
  A : A squarefree basis of integral polynomials, A =
      (A_1,...,A_m).

Output
  L : A labeled strong standard isolation list for the real
      roots of A.
=====================================================================*/
#include "saclib.h"

Word IPSBLSSIL(A)
       Word A;
{
        Word A1,A2,a1,a2,b1,b2,c,L,Lp,Lpp,I1,I2,s,T1,T2,t1,t2;

Step1: /* Apply IPSBLSIL to A. */
        L = IPSBLSIL(A);

Step2: /* Initialize refinement loop. */
        Lp = L;

Step3: /*  Refinement loop; if two consecutive intervals
        are adjacent, refine one until they are not. */

        while (Lp != NIL && RED(Lp) != NIL) {
           Lpp = RED(Lp);
           T1 = FIRST(Lp);
           T2 = FIRST(Lpp);
           FIRST3(T1,&I1,&A1,&t1);
           FIRST3(T2,&I2,&A2,&t2);
           FIRST2(I1,&a1,&b1);
           FIRST2(I2,&a2,&b2);
           if (EQUAL(b1,a2)) {

              if (!EQUAL(a1,b1)) {
                 do {
                    c = LSIM(a1,b1);
                    s = IUPBRES(A1,c);
                    if (s == -t1)
                       a1 = c;
                    else {
                       b1 = c;
                       if (s == 0)
                          a1 = c; } }
                 while (s == -t1);
                 I1 = LIST2(a1,b1);
                 T1 = LIST3(I1,A1,t1);
                 SFIRST(Lp,T1); }

              else {
                 do {
                    c = LSIM(a2,b2);
                    s = IUPBRES(A2,c);
                    if (s == t2)
                       b2 = c;
                    else {
                       a2 = c;
                       if (s == 0)
                          b2 = c; } }
                 while (s == t2);
                 I2 = LIST2(a2,b2);
                 T2 = LIST3(I2,A2,t2);
                 SFIRST(Lpp,T2); } }

           Lp = RED(Lp); }

Return: /* Return L. */
        return(L);
}
