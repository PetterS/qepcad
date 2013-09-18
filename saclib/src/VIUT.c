/*======================================================================
                      VIUT(U,V,i; Up,Vp)

Vector of integers, unimodular transformation.

Inputs
  U : an n-vector over Z, Ui not zero.
  V : an n-vector over Z.
  i : a BETA-digit, 1 <= i <= n.

Outputs
 Up,Vp: n-vectors over Z, [Up,Vp] = [U,V]K,  where K is a unimodular
        matrix (depending on Ui and Vi) whose elements are obtained
        from IDEGCD.
======================================================================*/
#include "saclib.h"

void VIUT(U,V,i, Up_,Vp_)
       Word U,V,i, *Up_,*Vp_;
{
       Word Up,Vp,c,p,q,r,s,u,v;
       /* hide c,u,v; */

Step1: /* Compute. */
       u = LELTI(U,i);
       v = LELTI(V,i);
       IDEGCD(u,v,&c,&p,&q,&r,&s);
       Up = VILCOM(p,q,U,V);
       Vp = VILCOM(r,s,U,V);

Return: /* Prepare for return. */
       *Up_ = Up;
       *Vp_ = Vp;
       return;
}
