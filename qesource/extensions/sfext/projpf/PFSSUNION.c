/* Projection factor set structure union. */
#include "qepcad.h"

Word PFSSUNION(Word A_, Word B_)
{
      Word A,B,C,a,b;

      A = A_; B = B_; C = NIL;
      while( A != NIL && B != NIL ) {
	ADV(A,&a,&A); 
	ADV(B,&b,&B);
	C = COMP(PFSUNION(a,b),C); }
      C = CINV(C);

      return (C);
}
