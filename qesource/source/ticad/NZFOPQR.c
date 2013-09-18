/*======================================================================
                      t <- NZFOPQR(c,k,b,A)

Non-zero first order partial query (Rational sample point)

\Input
  \parm{c} is a cell.
  \parm{k} is a positive $\beta$--integer.
  \parm{b} is the $k$-tuple coordinates of a rational sample point.
  \parm{A} is a $(k+1)$--variate integral polynomial.

\Output
  t : 1 if able to determine that there is a nonzero first order partial 
      of A, 0 otherwise
======================================================================*/
#include "qepcad.h"

Word QepcadCls::NZFOPQR(Word c, Word k, Word b, Word A)
{
  Word L, S, p;

  /* Step1: Compute all first-order partials of A */
  L = IPALLPARTIALS(k + 1,A,1,1);   

  /* Step2: See if we can deduce that one of the partials is non-zero in the cylinder over c. */
  bool nzf = false; /* non-zero flag */
  while(!nzf && L != NIL)
  {
    p = FIRST(L);

    if (ACCCVBCR(k,c,p,b,&S) == TRUE)
    {
      if (S != 0 && PDEG(S) == 0)
	nzf = true;      
      else
	; // At this point I could check whether S is positive/negative definite
    }
    else
    {
      ; // At this point I could check whether the factors of S can each be proven
      ; // To be positive/negative definite using the cell c and its parents!
      ; // Of course this would be a lot of work!
    }

    L = RED(L);
  }

  /* Return! */
  if (nzf && PCVERBOSE) {
    SWRITE("Determined that pol ");
    IPDWRITE(k+1,A,GVVL);
    SWRITE(" has constant order 1 over cell ");
    LWRITE(LELTI(c,INDX));
    SWRITE("\n");
  }
  return nzf ? 1 : 0;
  
}
