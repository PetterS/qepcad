/*======================================================================
                      Jp <- RMCONS(r,J)

Remove constant polynomials.

\Input
  \parm{r} is a positive $\beta$--integer.
  \parm{J} is a list of integral polynomials in $r$ variables.
  
\Output
  \parm{J'} is the list of integral polynomials obtained from \v{J}
            by removing all the constant polynomials.
======================================================================*/
#include "qepcad.h"

Word RMCONS(Word r, Word J)
{
       Word J1,Jh,Jh1,Jp;

Step1: /* Remove. */
       Jp = NIL; Jh = J;
       while (Jh != NIL)
         {
         ADV(Jh,&J1,&Jh);
         Jh1 = LELTI(J1,PO_POLY);
         if (!PCONST(r,Jh1))
           Jp = COMP(J1,Jp);
         }
       Jp = INV(Jp); goto Return;

Return: /* Prepare for return. */
       return(Jp);
}
