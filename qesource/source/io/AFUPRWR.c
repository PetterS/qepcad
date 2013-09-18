/*======================================================================
                      AFUPRWR(a,v,A,I)

Algebraic number Field Univariate Polynomial Real root Write.

\Input 
  \parm{v} is a variable.
  \parm{A} is an algebraic univariate polynomial.
  \parm{I} is an isolating interval.
======================================================================*/
#include "qepcad.h"

void AFUPRWR(Word a, Word v, Word A, Word I)
{
       Word l,r;

Step1: /* Write. */
       SWRITE("the unique root of "); AFPDWR(1,A,LIST1(v),a);
       FIRST2(I,&l,&r);
       SWRITE(" between "); RNWRITE(l); SWRITE(" and "); RNWRITE(r);

Return: /* Prepare for return. */
       return;
}
