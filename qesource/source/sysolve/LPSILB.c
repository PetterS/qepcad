/*======================================================================
                      L <- LPSILB(r,S)

List of polynomials separate into level-buckets

Inputs
 r : a positive BDigit
 S : a list of r-variate saclib polynomials
Output
 L : a list (L_1,...,L_r), where each L_i contains the i-level 
     elements of S.
======================================================================*/
#include "qepcad.h"

Word LPSILB(BDigit r, Word S)
{
  Word L,i,Sp,rp,p,Lp;

Step1: /* Create skelaton of L */
  L = NIL;
  for(i = 1; i <= r; i++)
    L = COMP(NIL,L);
  
Step2: /* Place elt's of S into L by level */
  for(Sp = S; Sp != NIL; Sp = RED(Sp))
  {
    PSIMREP(r,FIRST(Sp),&rp,&p);
    if (rp > 0)
      SLELTI(L,i,COMP(p,LELTI(L,i)));
  }

Step3: /* Reverse L_i's to preserve order */
  Lp = CINV(L);
  for(L = NIL; Lp != NIL; Lp = RED(Lp))
    L = COMP(CINV(FIRST(Lp)),L);

Return: /* Prepare to return */
  return L;
}
