/*===========================================================================
                      J <- PROJ(k,P_k)

Projection.

\Input
  \parm{k} is a $\beta$--integer. $k \geq 2$.
  \parm{Pk} is the list of distinct positive irreducible elements
           of $Z[x_1,\ldots,x_k]$ of positive degree in $x_k$.
  
\Output
  \parm{J} is a projection of \v{Pk}.
===========================================================================*/
#include "qepcad.h"

Word QepcadCls::PROJ(Word k, Word P_k)
{
       Word J,p;

Step1: /* Project. */
       if (PCPROPEC == TRUE)
	  J = PROJMCECmod(k,P_k);
       else {
	  p = LELTI(PCPROJOP,k - 1);
	  switch (p) {
	     case 'c': J = PROJCO(k,P_k); break;
	     case 'm': J = PROJMC(k,P_k); break;
	     case 'h': J = PROJHO(k,P_k); break;
	     case 'l': J = PROJLA(k,P_k); break;
	     case 'p': J = PROJMCmod(k,P_k); break;
	     case 'x': J = PROJMCx(k,P_k); break; } }

       J = RMCONS(k - 1,J); 
       J = GROUPSAMEPJ(k - 1,J);
       goto Return;

Return: /* Prepare for return. */
       return(J);
}
