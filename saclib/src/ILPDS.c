/*======================================================================
                      ILPDS(n,a,b; p,np)

Integer large prime divisor search.  

Inputs
  n    : in Z, n > 0, with no prime divisors less than 17.  
  a, b : 1 <= a <= b <= n.  

Outputs
  p,np : A search is made for a divisor p of the integer n, with a <= p <= b.  
         If such a p is found then n'=n/p, otherwise p=1 and n'=n.

Remarks  
  A modular version of fermats method is used, 
  and the search goes from a to b.
======================================================================*/
#include "saclib.h"

void ILPDS(n,a,b, p_,np_)
       Word n,a,b, *p_,*np_;
{
       Word L,Lp,m,np,p,q,r,r1,r2,s,t,x,x1,x2,y,yp;
       /* hide Lp,m,r1,r2,s,t; */

Step1: /* Compute boundary values of xl. */
       IQR(n,b,&q,&r);
       x1 = ISUM(b,q);
       IDQR(x1,2,&x1,&s);
       if (r != 0 || s != 0)
         x1 = ISUM(x1,1);
       q = IQ(n,a);
       x2 = ISUM(a,q);
       x2 = IDQ(x2,2);

Step2: /* Compute and sort residue list. */
       FRESL(n,&m,&L);
       L = LBIBMS(L);
       L = INV(L);

Step3: /* Find starting residue. */
       r = IDREM(x2,m);
       Lp = L;
       while (Lp != NIL && r < FIRST(Lp))
         Lp = RED(Lp);
       if (Lp == NIL)
         {
         Lp = L;
         s = m;
         }
       else
         s = 0;
       ADV(Lp,&r1,&Lp);
       s = s + r - r1;
       x = IDIF(x2,s);

Step4: /* Test successive values of xl. */
       while (ICOMP(x,x1) >= 0)
         {
         yp = IDIF(IPROD(x,x),n);
         ISQRT(yp,&y,&t);
         if (t == 0)
           {
           p = IDIF(x,y);
           np = ISUM(x,y);
           goto Return;
           }
         if (Lp != NIL)
           {
           ADV(Lp,&r2,&Lp);
           s = r1 - r2;
           }
         else
           {
           ADV(L,&r2,&Lp);
           s = m + r1 - r2;
           }
         r1 = r2;
         x = IDIF(x,s);
         }

Step5: /* No divisor found. */
       p = 1;
       np = n;

Return: /* Prepare for return. */
       *p_ = p;
       *np_ = np;
       return;
}
