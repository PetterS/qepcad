/*======================================================================
                      L <- MDLCRA(m1,m2,L1,L2)

Modular digit list chinese remainder algorithm.  

Inputs
  m1, m2 : positive BETA-integers, 
           with gcd(m1,m2)=1 and ml=m1*m2 less than BETA.  
  L1, L2 : lists of elements of z(m1) and z(m2) respectively. 

Outputs
  L      : a list of all al in z(ml) such that 
           al is congruent to al1 modulo m1 and 
           al is congruent to al2 modulo m2 with 
           al1 in L1 and al2 in L2.
======================================================================*/
#include "saclib.h"

Word MDLCRA(m1,m2,L1,L2)
       Word m1,m2,L1,L2;
{
       Word L,Lp1,Lp2,a,a1,a2,mp1;
       /* hide Lp1,Lp2,a,a1,a2,mp1; */

Step1: /* Compute. */
       mp1 = MDINV(m2,m1);
       L = NIL;
       Lp1 = L1;
       while (Lp1 != NIL)
         {
         ADV(Lp1,&a1,&Lp1);
         Lp2 = L2;
         while (Lp2 != NIL)
           {
           ADV(Lp2,&a2,&Lp2);
           a = MDCRA(m1,m2,mp1,a1,a2);
           L = COMP(a,L);
           }
         }

Return: /* Prepare for return. */
       return(L);
}
