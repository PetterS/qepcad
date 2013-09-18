/*======================================================================
                      Js <- AFUPIIR(M,I,B,J)

Algebraic number field polynomial isolating interval refinement.  

Inputs
  M : in Z[x].  M is the minimal polynomial for a real algebraic number
      alpha.
  I : an acceptable isolating interval for alpha.
  B : in Q(alpha)[y].  B(alpha,y) is squarefree.
  J : a binary rational isolating interval for a real root of B.
Outputs
  Js : a binary rational subinterval of J, obtained by a single 
       application of RIB, containing the same root.
======================================================================*/
#include "saclib.h"

Word AFUPIIR(M,I,B,J)
       Word M,I,B,J;
{
       Word Js;
       Word a,b,c,s,t;

Step1: /* Get the endpoints of J, and bisect. */
       FIRST2(J,&a,&b);
       if (RNCOMP(a,b) == 0) {
         Js = J;
         goto Return; }
       c = RIB(a,b);

Step2: /* If A(b) = 0 then Js = (b,b). */
       t = AFUPSR(M,I,B,b);
       if (t == 0)
         {
         Js = LIST2(b,b);
         goto Return;
         }

Step3: /* Otherwise, compare the signs of B at c and b. */
       s = AFUPSR(M,I,B,c);
       if (s == t)
         Js = LIST2(a,c);
       else
         Js = LIST2(c,b);

Return:
       return(Js);
}
