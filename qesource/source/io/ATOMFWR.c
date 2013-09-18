/*======================================================================
                      ATOMFWR(V,A)

Atomic Formula Write.

\Input
   \parm{V} is a non-null list of distinct variables.
   \parm{A} is an atomic formula with variables in $V$,
            written out to the output strem.
======================================================================*/
#include "qepcad.h"

void ATOMFWR(Word V, Word A)
{
       Word I,P,T,r,j,Pp,X;

Step1: /* Write Atomic Tarski Formula. */
       if (FIRST(A) == IROOT) goto Step2;
       FIRST4(A,&T,&P,&r,&I);
       IPDWRITE(r,P,V);
       SWRITE(" "); RLOPWR(T); SWRITE(" 0");
       goto Return;

Step2: /* Write Atomic Extended Tarski Formula */
       FIRST6(A,&X,&T,&j,&P,&r,&I);
       
       /* Correct for unnormalized ETF atoms */
       if (I == NIL)
	 P = LIST1(P);

       VWRITE(LELTI(V,r));
       SWRITE(" "); RLOPWR(T); 
       SWRITE(" _root_"); IWRITE(j);
       if (LENGTH(P) == 1)
       {
	 SWRITE(" ");
	 IPDWRITE(r,FIRST(P),V);
       }
       else
       {
	 for(Pp = P; Pp != NIL; Pp = RED(Pp))
	 {
	   SWRITE(" (");
	   IPDWRITE(r,FIRST(Pp),V);
	   SWRITE(")");
	 }
       }

Return: /* Prepare for return. */
       return;
}
