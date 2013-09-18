/*======================================================================
                      L <- IPRIMO(A,Ap,I)

Integral polynomial real root isolation, modified Uspensky method,    
open interval.

Inputs
  A  : in Z[X], without multiple roots.
  Ap : the derivative of A.
  I  : an open interval (a,b) with binary rational endpoints, 
       represented by the list (a,b), 
       such that there are integers h and k 
       for which a = h 2^k and b = (h+1) 2^k.

Outputs
  L  : a list (I1,...,Ir) of isolating intervals 
       for the real roots of A in I. 
       Each Ij is a left open right closed interval 
       with binary rational endpoints and I1 < I2 < ... < Ir.
======================================================================*/
#include "saclib.h"

Word IPRIMO(A,Ap,I)
       Word A,Ap,I;
{
       Word J,L,b,c;
       /* hide J,b,c; */

Step1:
       L = IPRIMS(A,Ap,I);
       if (L != NIL)
         {
         L = INV(L);
         J = FIRST(L);
         b = SECOND(I);
         c = SECOND(J);
         if (RNCOMP(b,c) == 0 && IUPBES(A,b) == 0)
           L = RED(L);
         L = INV(L);
         }

Return: /* Prepare for return. */
       return(L);
}
