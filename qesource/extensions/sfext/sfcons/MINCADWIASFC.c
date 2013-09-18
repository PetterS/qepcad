/* Minimal CAD with input polynomials allowing solution formula construction.

Inputs
 D : a CAD
 P : the projection factor set defining D.

Outputs
 Ds: if t = 1, a sub-CAD of D, which still allows solution formula 
     const.
 Ps: if t = 1, a projection factor set defining Ds.
 t : 0 if D is identically true or false, -1 if no solution formula 
     is possible, 1 otherwise. */
#include "qepcad.h"
static Word t0,t1,t2,t3;

Word MINCADWIASFC(Word D, Word P, Word *Ds_, Word *Ps_)
{
      Word t,Ps,Ds,Q,SF,C,i;

/* TIME */ t0 = ACLOCK();
Step0: /* Check for the trivial cases. */
      switch( DOPFSUFF(P,LIST1(D)) ) {
      case (TRUE) : SWRITE("\n\nInput is identically TRUE.\n\n");
	            t = 0;
                    goto Return;
      case (FALSE): SWRITE("\n\nInput is identically FALSE.\n\n");
	            t = 0;
                    goto Return; 
      case (NIL)  : SWRITE("\n\nThe projection set does not suffice.\n\n");
	            t = -1;
                    goto Return; }
/* TIME */ t0 = ACLOCK() - t0;
 
t = 1;

/* TIME */ t1 = ACLOCK();
Step1: /* Minimal CAD. */
      CCADCON(GVNFV,P,D,&Ps,&Ds);
/* TIME */ t1 = ACLOCK()-t1;

Step2: /* Find a minimal set of polynomials which suffice for SF const,
          making use of the set Q computed in Step 1. */
/* TIME */ t2 = ACLOCK();
      Q = MINPFSET(P,Ps,D,GVNFV);
/* TIME */ t2 = ACLOCK()-t2;

Step3: /* Construct a CAD from the proj-closure of Qs from step2. */
/* TIME */ t3 = ACLOCK();
      CCADCONFPFS(GVNFV,P,D,Q,&Ps,&Ds);
      Ps = PFSREORDERREV(P,Ps);
      Ds = CADFPCADWI(Ds,Ps,NIL,NIL,P);
/* TIME */ t3 = ACLOCK()-t3;

Return:/* Prepare to return. */
      *Ds_ = Ds;
      *Ps_ = Ps;
      return (t);
}

void MINCADWIASFC_STATS()
{
  SWRITE("Checking for special cases: ");
  IWRITE(t0); SWRITE("\n");
  SWRITE("Finding some necessary polynomials: ");
  IWRITE(t1); SWRITE("\n");
  SWRITE("Finding a set of pol's sufficing for sf const: ");
  IWRITE(t2); SWRITE("\n");
  SWRITE("Constructing the sub-CAD allowing sf construction: ");
  IWRITE(t3); SWRITE("\n");
  return;
}
