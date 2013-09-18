/*=====================================================================
		      L <- IPLSILM(L1,L2)

Integral polynomial labeled standard isolation list merge.

Inputs
  L1, L2 : labeled standard isolation lists such that
           the sets of roots isolated by L1 and L2
           are disjoint.

Outputs
  L : a labeled standard isolation list for all roots
      isolated by either L1 or L2.
=====================================================================*/
#include "saclib.h"

Word IPLSILM(L1,L2)
       Word L1,L2;
{
       Word A1,A2,I1,I2,Is1,Is2,L,Lp1,Lp2,s,t1,t2,T1,T2;

Step1: /* L1 or L2 empty. */
       if (L1 == NIL) {
	  L = L2;
	  goto Return; }
       if (L2 == NIL) {
	  L = L1;
	  goto Return; }

Step2: /* Initialize L, T1, T2, Lp1 and Lp2. */
       L = NIL;
       ADV(L1,&T1,&Lp1);
       ADV(L2,&T2,&Lp2);

Step3: /* Get components of T1 and T2. */
       FIRST3(T1,&I1,&A1,&t1);
       FIRST3(T2,&I2,&A2,&t2);

Step4: /* Apply IPIIS repeatedly. */
       IPIIS(A1,A2,I1,I2,t1,t2,&Is1,&Is2,&s);
       T1 = LIST3(Is1,A1,t1);
       T2 = LIST3(Is2,A2,t2);
       if (s < 0) {
	  L = COMP(T1,L);
	  if (Lp1 == NIL) {
	     L = COMP(T2,L);
	     goto Step5; }
	  else
	     ADV(Lp1,&T1,&Lp1); }
       else {
	  L = COMP(T2,L);
	  if (Lp2 == NIL) {
	     L = COMP(T1,L);
	     Lp2 = Lp1;
	     goto Step5; }
	  else
	     ADV(Lp2,&T2,&Lp2); }
       goto Step3;

Step5: /* Include remaining elements of Lp2 in L and invert. */
       while (Lp2 != NIL) {
	  ADV(Lp2,&T2,&Lp2);
	  L = COMP(T2,L); }
       L = INV(L);

Return: /* Return L. */
       return(L);
}
