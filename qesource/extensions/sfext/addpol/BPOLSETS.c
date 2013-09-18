/*======================================================================
                      BPOLSETS(L,D,P;T,N)

Border polynomial sets.

Inputs
 L  : a list (L_1,...,L_k), where each L_i is a pair of level i 
      conflicting cells, as computed by CFLCELLLIST.
 D  : the CAD or RCAD structure containing the cells in L.
 P  : the projection factor set structure defining D.

Outputs
 T  : a list (T_1,...,T_m), where for each conflicting pair (a,b) which
     lie in the same cylinder over a level N-1 cell, there is a T_i
     corresponding to (a,b) which consists of every level N projection
     factor which is not identically zero in the stack containing a and
     b, but which is zero in a (equivalently b) or in some cell between
     a and b in the stack.

 N  : the greatest level such that there is a conflicting pair in which 
      both elements lie in the same cylinder over a level N-1 cell.
======================================================================*/
#include "qepcad.h"

void BPOLSETS(Word L_, Word D, Word P, Word *T_, Word *N_)
{
      Word L,T,Q,q,a,b,I_a,I_b,i_a,i_b,n,P_N,S_a,S_b,s_a,s_b,t,N,p,
	   S_T,S_L,s_c,c,i,Tb,Tp;

Step1: /* Initialization. */
      L = LCOPY(L_);
      T = NIL;
      for(N = LENGTH(L); T == NIL; N--) {

Step2: /* Loop over each pair of the level N pairs. */
	for(Q = LELTI(L,N); Q != NIL; Q = RED(Q)) {
	  q = FIRST(Q);
	  FIRST2(q,&a,&b);

Step3: /* Play the game with the indices. */
	  I_a = CINV(LELTI(a,INDX));
	  I_b = CINV(LELTI(b,INDX));
	  do {
	    ADV(I_a,&i_a,&I_a);
	    ADV(I_b,&i_b,&I_b);
	  } while (! EQUAL(I_a,I_b) );
	  I_a = CINV(COMP(i_a,I_a));
	  I_b = CINV(COMP(i_b,I_b));
	  n = LENGTH(I_a);

Step4: /* If this pair represents a conflict at a lower level ... */
	  if (n < N) {
	    a = CELLFINDEX(D,I_a);
	    b = CELLFINDEX(D,I_b);
	    SLELTI(L,n,COMP(LIST2(a,b),LELTI(L,n))); }

	  else {
Step5: /* Set I_a to the index of the lower border cell and I_b to the upper. */
	    if (i_a > i_b) { 
	      t = i_a; i_a = i_b; i_b = t; };
	    if (ODD(i_a)) {
	      i_a++;
	      i_b--; }

Step6: /* Set S_L to the list of all section cells between a and b, inclusive. */
	    S_T = LELTI(CELLFINDEX(D,INV(RED(CINV(I_a)))),CHILD); /* The stack. */
	    c = FIRST(S_T); /* First cell in the stack. */
	    for(i = 1; i < i_a; i++, S_T = RED(S_T));
	    S_L = NIL;
	    do {
	      S_L = COMP(FIRST(S_T),S_L);
	      S_T = RED2(S_T);
	      i += 2;
	    }while(i <= i_b);
	    
	    
Step7: /* Set Tp to the list of N-level polynomials which are zero in a 
(equivalently b) or some cell in the stack between a and b. */
	    for(Tp = NIL; S_L != NIL; S_L = RED(S_L))
	      Tp = PFSUNION(Tp,LPFZC(FIRST(S_L),P));
	    
Step8: /* Remove any N-level projection factors which are identically zero
in the stack containing a and b.  Such a p.f. must be zero in c. */
	    P_N = LELTI(P,N);
	    s_c = FIRST(LELTI(c,SIGNPF));
	    for(Tb = NIL; P_N != NIL; P_N = RED(P_N), s_c = RED(s_c))
	      if (FIRST(s_c) == 0)
		Tb = COMP(FIRST(P_N),Tb);
	    Tp = LPFSETMINUS(Tp,Tb); 
	    T = COMP(Tp,T); } } }

Return: /* Prepare to return. */
      *T_ = T;
      *N_ = N + 1;
      return;
}
