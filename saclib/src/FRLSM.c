/*======================================================================
                      L <- FRLSM(m,a)

Fermat residue list, single modulus.

Inputs
  m  : positive BETA-digit.
  a  : an element of Z(m).

Outputs
  L  : a list of the distinct elements b in Z(m) such that b^2-a
       is a square in Z(m).
======================================================================*/
#include "saclib.h"

Word FRLSM(m,a)
       Word m,a;
{
       Word L,S,Sp,i,ip,j,mp,s,sp;
       /* hide Sp,i,ip,j,mp,s,sp; */

Step1: /* Compute list of squares of z(m). */
       mp = m / 2;
       S = NIL;
       for (i = 0; i <= mp; i++)
         {
         s = MDPROD(m,i,i);
         S = COMP(s,S);
         }

Step2: /* Compute L. */
       L = NIL;
       Sp = S;
       for (i = mp; i >= 0 ; i--)
         {
         ADV(Sp,&s,&Sp);
         sp = MDDIF(m,s,a);
         j = LSRCH(sp,S);
         if (j != 0)
           {
           L = COMP(i,L);
           ip = MDNEG(m,i);
           if (ip != i)
             L = COMP(ip,L);
           }
         }

Return: /* Prepare for return. */
       return(L);
}
