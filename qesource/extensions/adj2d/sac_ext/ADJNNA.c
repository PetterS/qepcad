/*    Adjacency: number of negative asymptotes. 

      Two input possiblities:

      1) (i1,i2) must be a lbrn interval, the root of a in (k1,k2) is
         in (i1,i2).
	 

*/
#include "sac_ext.h"
static Word aux_ADJNNA(Word p,Word q1,Word q0,Word i1,Word i2);

Word ADJNNA(Word P, Word i1, Word i2, Word j, Word A, Word k1, Word k2)
{
  Word p,q1,q0,L1,L2,a,L,s,M,d1,d2,l,r,Q;
  
Step1: /* Get q1, q0:  -q0/q1 = dy/dx */
  Q = IBPIDFV(P);
  q1 =IPLBREVAL(2,PCFE(Q,1),j);
  q0 =IPLBREVAL(2,PCFE(Q,0),j);

Step2: /* Substitute y = j, and take primitive squarefree part. */
  p = IPPGSD(1,IPLBREVAL(2,P,j));

  if (PDEG(q1) < 0 || PDEG(q0) < 0 || (PDEG(q1) != 0 && IPRES(1,p,q1) == 0 )
      || (PDEG(q0) != 0 && IPRES(1,p,q0) == 0)) {
    /****** Instead of crashing, we could send back for different j. ********/
    SWRITE("ERROR IN ADJNNA!  So far both p,q assumed relatively prime!\n");
    return 0;
  }

Step4: /* k1 != k2. */
  L = aux_ADJNNA(p,q1,q0,i1,i2);

Step5: /* Divide L into L1 and L2, the elements of L to the left
and right of A(x) falling in (k1,k2). */
  L1 = NIL; L2 = NIL;
  while(L != NIL) {
    a = FIRST(L);
    FIRST2(a,&s,&M);
    if (RRCOMPSRI(A,k1,k2,p,FIRST(M),SECOND(M),&k1,&k2,&d1,&d2) == -1)
      break;
    L1 = COMP(a,L1);
    L = RED(L); }
  L1 = INV(L1);
  L2 = L;

Step6: /* The two program branches meet, and we determine l and r. */
    for(l = 0; L1 != NIL; L1 = RED(L1))
      l -= FIRST(FIRST(L1));
    for(r = 0; L2 != NIL; L2 = RED(L2))
      r += FIRST(FIRST(L2)); 

    return LIST2(l,r);
}


static Word aux_ADJNNA(Word p, Word q1, Word q0, Word i1, Word i2)
{
       Word Lq1,Lq0,R,T,s1,s0,M,L;
    /* Set L to be the list of pairs (s,M), where s is the sign
       of dy/dx for the section of P(x,y) passing through the
       the point (j,alpha), where alpha is the root of p(x) isolated
       in M.
    */
Step1: /* Isolate roots of p in (i1,i2) and find the sign of q1 at each root. */
       Lq1 = IUPSOPOR(p,q1,i1,i2);

Step2: /* Extract a simple list of isolating intervals from Lq1. */
       for(R = NIL, T = Lq1; T != NIL; T = RED(T))
	 R = COMP(SECOND(FIRST(T)),R);
       R = INV(R);

Step3: /* Find the sign of q1 at each root of p in R. */
       Lq0 = IUPSOPORFIL(p,q0,R);

Step4: /* Combine Lq1 and Lq2 to get a list of roots of p in (i1,i2)
with the sign of -q0/q1 at each root attatched. */
       for(L = NIL; Lq1 != NIL; Lq1 = RED(Lq1), Lq0 = RED(Lq0)) {
	 FIRST2(FIRST(Lq1),&s1,&M);
	 FIRST2(FIRST(Lq0),&s0,&M);
	 L = COMP( LIST2(-s0*s1,M) , L); }
       L = INV(L);

Return: /* Prepare to return. */
       return L;
}
