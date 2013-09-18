/*======================================================================
                      SIGNP1(c,P1,I)

Signatures of Projection factors, $1$--level.
 
\Input
  \parm{c}  is the root cell.
  \parm{P1} is the list of the $1$--level projection factors.
  \parm{I}  is a list of the real roots of $P_1$ (see CONSTRUCT).
 
\Output
  The signatures of~$P_1$ on the cells 
  in the stack over the root cell~$c$
  are determined and attached to them.
======================================================================*/
#include "qepcad.h"
#include <vector>
using namespace std;

void SIGNP1(Word c, Word P1, Word I)
{
       Word S1,c1,cb,I1;

Step1: /* Compute the signatures of $P_1$. */
       vector<BDigit> S;
       for(Word P = P1; P != NIL; P = RED(P))  {
	 Word p = FIRST(P);
	 if (LELTI(p,PO_TYPE) == PO_POINT || EVEN(PDEG(LELTI(p,PO_POLY))))
	   S.push_back(1);
	 else
	   S.push_back(-1); }
       vector< vector<BDigit> > M;
       M.push_back(S);
       int i = 1;
       while(I != NIL) {	 
	 M.push_back(M[i-1]);
	 M.push_back(M[i-1]);
	 i += 2;
	 ADV(I,&I1,&I);
	 for(Word L = THIRD(I1); L != NIL; L = RED(L)) {
	   Word a = FIRST(L);
	   BDigit j = 1;
	   for(Word T = P1; FIRST(T) != a; T = RED(T), j++);
	   M[i-2][j-1] = 0;
	   M[i-1][j-1] = -M[i-3][j-1]; }
       }
	     

Step2: /* Attach the signatures to the cells. */
       int k = 0;
       cb = LELTI(c,CHILD);
       while (cb != NIL)
       {
         ADV(cb,&c1,&cb);
	 Word s = NIL; for(int i = S.size()-1; i >= 0; i--) s = COMP(M[k][i],s);
         SFIRST(LELTI(c1,SIGNPF),s);
	 k++;
       }
       goto Return;

Return: /* Prepare for return. */
       return;
}
