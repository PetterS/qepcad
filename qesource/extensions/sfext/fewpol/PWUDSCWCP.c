/*======================================================================
                         R <- PWUDSCWCP(D,P,N)

Polynomials which uniquely define section cells which, together with
at least one stack nieghbor are a conflicting pair.

Inputs
 D : a CAD which is not a leaf.
 P : the projection factor set defining D.
 N : the level of the CAD in which D resides.

Outputs
 R : a qepcad projection factor set data structure, containing all
     polynomials p in P such that there exists a section cell c in the
     sub-tree rooted at D such that p is the only projection factor
     which is identically zero in c, and c and at least one of its
     stack nieghbors form a conflicting pair.
======================================================================*/
#include "qepcad.h"

Word PWUDSCWCP(Word D, Word P, Word N)
{
      Word C,R,i,a,b,c,L,p,T_a,T_b,T_c,t_a,t_b,t_c,r;

Step1: /* Initialization. */
      C = LELTI(D,CHILD);
      R = NIL; for(i = 0; i < N; i++) R = COMP(NIL,R);

Step2: /* Loop over the children of C. Child cell b will always be
	  a section.  Decide if the polynomial defining that section
	  need to be added to R. */
      for(ADV(C,&a,&C); C != NIL; a = c) {
	ADV2(C,&b,&c,&C);

Step3: /* Get a list of polynomials which are zero in b and not in c. */
	L = LPFSETMINUS(LPFZC(b,P),LPFZC(c,P));
	if (LENGTH(L) == 1) {

Step4: /* If b is a section of a single projection factor ... */
	  T_a = LELTI(a,TRUTH); T_b = LELTI(b,TRUTH); T_c = LELTI(c,TRUTH); 
	  t_a = CATV(a); t_b = CATV(b); t_c = CATV(c);
	  if (( T_b == TRUE && (t_a != TRUE || t_c != TRUE)) ||
	      ( T_b == FALSE && (t_a != FALSE || t_c != FALSE)) ||
	      ( ( T_a == TRUE || T_c == TRUE) && t_b != TRUE) ||
	      ( ( T_a == FALSE || T_c == FALSE) && t_b != FALSE)) {

Step5: /* Add pol defining b to R. */
	    p = FIRST(L);
	    r = SECOND(LELTI(p,PO_LABEL));
	    SLELTI(R,r,PFSUNION(LELTI(R,r),L)); } }

Step6: /* If necessary, search children of a and b. */
	if (LELTI(a,CHILD) != NIL)
	  R = PFSSUNION(PWUDSCWCP(a,P,N),R);
	if (LELTI(b,CHILD) != NIL)
	  R = PFSSUNION(PWUDSCWCP(b,P,N),R); }

Step7: /* If necessary search children of a. */
      if (LELTI(a,CHILD) != NIL)
	R = PFSSUNION(PWUDSCWCP(a,P,N),R);

Return: /* Return. */
      return (R);
}
