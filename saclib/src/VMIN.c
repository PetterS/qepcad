/*======================================================================
                      W <- VMIN(U,V)

Vector minimum.

Inputs
  U,V : lists of BETA-digits, U=(u1,...,ur) and V=(v1,...,vr).
  r   : a BETA-digit, r >= 1.

Outputs
  W   : a list of BETA-digits, W=(w1,...,wr) where wi = min(ui,vi).
======================================================================*/
#include "saclib.h"

Word VMIN(U,V)
       Word U,V;
{
       Word Us,Vs,W,u,v,w;
       /* hide Us,Vs,u,v,w; */

Step1: /* Compute. */
       W = NIL;
       Us = U;
       Vs = V;
       do
         {
         ADV(Us,&u,&Us);
         ADV(Vs,&v,&Vs);
         w = MIN(u,v);
         W = COMP(w,W);
         }
       while (!(Us == NIL));
       W = INV(W);

Return: /* Prepare for return. */
       return(W);
}
