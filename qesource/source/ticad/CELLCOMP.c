/*======================================================================
                      t <- CELLCOMP(c1,c2,S)

Cell Compare.

\Input
  \parm{c1} is a cell.
  \parm{c2} is another cell.
  \parm{S}  is a non-empty list of partial orderings.
  
\Output
  \parm{t} is $1$ if $c_1 > c_2$ 
             $-1$ if $c_1 < c_2$
              $0$ if the partial orderings fail to order $c_1$ and $c_2$.
======================================================================*/
#include "qepcad.h"

Word CELLCOMP(Word c1, Word c2, Word S)
{
       Word S1,Sp,t;
       /* hide t; */

Step1: /* Compare. */
       Sp = S;
       while (Sp != NIL)
         {
         ADV(Sp,&S1,&Sp);
         switch (S1)
           {
           case HLORD: t = -LVCOMP(c1,c2); break;
           case LLORD: t =  LVCOMP(c1,c2); break;
           case GIORD: t = -IXCOMP(c1,c2); break;
           case LIORD: t =  IXCOMP(c1,c2); break;
           case SNORD: t = -SSCOMP(c1,c2); break;
           case SRORD: t =  SSCOMP(c1,c2); break;
           case NCORD: t = -CVCOMP(c1,c2); break;
           case TCORD: t =  CVCOMP(c1,c2); break;
           case GDORD: t = -DSCOMP(c1,c2); break;
           case LDORD: t =  DSCOMP(c1,c2); break;
           }
         if (t != 0) goto Return;
         }
       goto Return;

Return: /* Prepare for return. */
       return(t);
}
