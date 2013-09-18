/*======================================================================
                      t <- VCOMP(U,V)

Vector comparison.

Inputs
  U,V : lists of BETA-digits, U=(u1,...,ur) and V=(v1,...,vr).
  r   : a BETA-digit, r >= 1.

Outputs
  t   : If U = V then t=0.  
        If U is not equal to V then
           t = 1 if ui <= vi for all i,
           t = 2 if vi <= ui for all i, and
           t = 3 otherwise.
======================================================================*/
#include "saclib.h"

Word VCOMP(U,V)
       Word U,V;
{
       Word Us,Vs,t,t1,t2,u,v;
       /* hide algorithm */

Step1: /* Compute. */
       t1 = 0;
       t2 = 0;
       Us = U;
       Vs = V;
       do
         {
         ADV(Us,&u,&Us);
         ADV(Vs,&v,&Vs);
         if (u < v)
           t1 = 1;
         else
           if (v < u)
             t2 = 2;
         }
       while (!(Us == NIL));
       t = t1 + t2;

Return: /* Prepare for return. */
       return(t);
}
