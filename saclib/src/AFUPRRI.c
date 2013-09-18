/*======================================================================
                      Js <- AFUPRRI(M,I,A,B,J,s1,t1)

Algebraic number field univariate polynomial relative real root isolation.

Inputs
      M : in Z[x], the minimal polynomial of an algebraic number alpha.  
      I : an acceptable isolating interval for alpha.  
    A,B : in Q(alpha)[x]. 
      J : a left open, right closed interval (a1,a2) where a1 and a2 
          are binary rational numbers with a1 < a2.  
          A and B have unique roots, r1 and r2 respectively, in J,
          each of odd multiplicity and with r1 not equal r2.  
  s1,t1 : BETA-digits, s1 = sign(A(a1+)) and t1 = sign(B(a1+)).  

Outputs
     Js : a left-open, right closed interval. Js = (as1,as2) is a 
         subinterval of J with as1 and as2 binary rational numbers 
         and as1 < as2, such that Js contains r1 but not r2.
======================================================================*/
#include "saclib.h"

Word AFUPRRI(M,I,A,B,J,s1,t1)
       Word M,I,A,B,J,s1,t1;
{
       Word Js,a,as1,as2,s,t,u,v;
       /* hide s,t,u,v; */

Step1: /* Initialize. */
       FIRST2(J,&as1,&as2);

Step2: /* Bisect. */
       a = RIB(as1,as2);
       s = AFUPSR(M,I,A,a);
       if (s == 0)
         s = -s1;
       t = AFUPSR(M,I,B,a);
       if (t == 0)
         t = -t1;
       u = s1 * s;
       v = t1 * t;
       if (u > 0)
         as1 = a;
       else
         as2 = a;
       if (u == v)
         goto Step2;

Step3: /* Construct Js. */
       Js = LIST2(as1,as2);

Return: /* Prepare for return. */
       return(Js);
}
