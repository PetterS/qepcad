/*======================================================================
                      Js <- AMUPIIR(M,I,B,J)

Algebraic module polynomial isolating interval refinement.  

Inputs
  M : in Z[X].  M is the minimal polynomial for a real algebraic number
      alpha.
  I : an acceptable isolating interval for alpha.
  B : in Z[alpha,y].  B(alpha,y) is squarefree over Q(alpha)[y].
  J : a binary rational isolting interval for a real root of B.
Outputs
  Js : a binary rational subinterval of J, obtained by a single 
       application of RIB, containing the same root.
======================================================================*/
#include "saclib.h"

Word AMUPIIR(M,I,B,J)
       Word M,I,B,J;
{
       Word Js;
       Word a,b,c,s,t;

Step1: /* Get the endpoints of J, and bisect. */
       FIRST2(J,&a,&b);
       c = RIB(a,b);

Step2: /* If A(b) = 0 then Js = (b,b). */
       t = AMUPBES(M,I,B,b);
       if (t == 0)
         {
         Js = LIST2(b,b);
         goto Return;
         }

Step3: /* Otherwise, compare the signs of B at c and b. */
       s = AMUPBES(M,I,B,c);
       if (s == t)
         Js = LIST2(a,c);
       else
         Js = LIST2(c,b);

Return:
       return(Js);
}
