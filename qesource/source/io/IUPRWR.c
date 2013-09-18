/*======================================================================
                      IUPRWR(v,A,I)

Integral Univariate Polynomial Real root Write.

\Input 
  \parm{v} is a variable.
  \parm{A} is an integral univariate polynomial.
  \parm{I} is an isolating interval.
======================================================================*/
#include "qepcad.h"

void IUPRWR(Word v, Word A, Word I)
{
       Word l,r;

Step1: /* Write. */
       SWRITE("the unique root of "); IPDWRITE(1,A,LIST1(v));
       FIRST2(I,&l,&r);
       SWRITE(" between "); RNWRITE(l); SWRITE(" and "); RNWRITE(r); 

Return: /* Prepare for return. */
       return;
}
