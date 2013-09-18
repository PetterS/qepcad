/*======================================================================
                      t <- TYPEAF(A)

Type of Atomic Formula.

\Input
  \parm{A} is an atomic formula.
  
\Output
  \parm{t} is \c{TRUE}  if \v{F} is  a true constant atomic formula,
              \c{FALSE} if \v{F} is  a false constant atomic formula,
              \c{UNDET} otherwise.
======================================================================*/
#include "qepcad.h"

Word TYPEAF(Word A)
{
       Word I,P,Ps,T,r,rs,s,t;
       /* hide rs,s,t; */

Step1: /* Check. */
       if (FIRST(A) == IROOT)
       {
	 t = UNDET;
	 goto Return;
       }
       FIRST4(A,&T,&P,&r,&I);
       PSIMREP(r,P,&rs,&Ps);
       if (rs > 0) { t = UNDET; goto Return; }
       s = ISIGNF(Ps);
       switch (T)
         {
         case EQOP: if (s == 0) t = TRUE; else t = FALSE; break;
         case NEOP: if (s != 0) t = TRUE; else t = FALSE; break;
         case GTOP: if (s > 0) t = TRUE; else t = FALSE; break;
         case GEOP: if (s >= 0) t = TRUE; else t = FALSE; break;
         case LTOP: if (s < 0) t = TRUE; else t = FALSE; break;
         case LEOP: if (s <= 0) t = TRUE; else t = FALSE;
         break; }
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
