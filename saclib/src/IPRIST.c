/*===========================================================================
			       L <- IPRIST(A)

Integral polynomial real root isolation using a Sturm sequence.
 
Inputs  
  A : in Z[X], non-zero, squarefree.

Outputs
  L : a list (I_1,...,I_r) of isolating intervals for all of
      the real roots of A with I_1 < I_2 < ... < I_r.
      Each I_j is a left-open right-closed binary rational interval.
===========================================================================*/
#include "saclib.h"

Word IPRIST(A)
       Word A;
{
       Word L,Ap,Ab,S,b,v_1,v_2;

Step1: /* Compute primitive Sturm sequence. */
       Ab = IPIPP(1,A);
       Ap = IPIPP(1,IPDMV(1,Ab));
       S = IPPNPRS(Ab,Ap);

Step2: /* Compute root bound. */
       b = IUPRB(Ab);

Step3: /* Search for isolating intervals. */
       v_1 = VAR(IPLEV(S,RNNEG(b)));
       v_2 = VAR(IPLEV(S,b));
       L = IPIISS(S,RNNEG(b),b,v_1,v_2);

Return: /* Prepare for return. */
       return(L);
}
