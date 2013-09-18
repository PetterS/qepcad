/*======================================================================
                  d <- RNCADRTV(D,P,Q,N)

Rebuild new CAD, retaining truth values.

Inputs
  D : A qepcad CAD or a RCAD (i.e. a CAD with RCell's)
  P : The qepcad projection factor data structure corresponding to D.
  Q : A qepcad projection factor data structure which includes P.  It
      is required that the jth ith level polynomial of P is also the
      jth ith level polynomial of Q.
  N : The level of the CAD D.

Outputs
  d : The RCAD (i.e. a CAD with RCell's) defined by Q whose cells have
      truth values assigned from D.
======================================================================*/
#include "qepcad.h"
#include "newpols.h"
static void GETPROJFACS(Word P,Word Q,Word k,Word *Pp_,Word *PpO_,Word *PpN_);

Word QepcadCls::RNCADRTV(Word D, Word P, Word Q, Word N)
{
      Word c,r,d,k,Pp,PpO,PpN;
      Word t1,t2,t3;

Step1: /* Construct d, the root RCell. */
      d = LIST10(0,NIL,0,UNDET,NIL,NIL,NIL,NOTDET,NIL,NIL);
      r = LIST2(D,1);
      d = CONC(d,r);

Step2: /* Chose cell to raise stack over. */
      while ((c = CRCELL(d)) > BETA) {
	k = LELTI(c,LEVEL);
	GETPROJFACS(P,Q,k+1,&Pp,&PpO,&PpN);

Step3: /* Build a stack or RCell's over c, complete with truth values.   */
             t1 = GVPC; GVPC = d; /* Basically all this stuff is to      */
	     t2 = GVPF; GVPF = Q; /* fool CONSTRUCT into lifting in free */
	     t3 = GVNV; GVNV = N; /* variable space like I want!         */
	CSORCELLTR_MOD(c,Pp,PpO,PpN,P); 
             GVPC = t1;
	     GVPF = t2;
	     GVNV = t3;
}

Return: /* Prepare to return. */
      return (d);
}


/*======================================================================
                  GETPROJFACS(P,Q,k,Pp,PpO,PpN)

Get projection factors.

Inputs
  P  : A qepcad projection factor data structure.
  Q  : A qepcad projection factor data structure which includes P.  It
       is required that the jth ith level polynomial of P is also the
       jth ith level polynomial of Q.
  k  : A positive BETA-digit not greater than the number of levels in P.

Outputs
  Pp : A list (Pp_1,...,Pp_i), where i is the number of level k projection
       factors in Q, and Pp_j is the integer polynomial represented by
       the jth level k polynomial data structure in Q.
  PpO: A list (PpO_1,...,PpO_i), where i is the number of level k projection
       factors in P, and PpO_j is the integer polynomial represented by
       the jth level k polynomial data structure in P.
  PpN: Given by CCONC(PpO,PpN) = Pp.
======================================================================*/
static void GETPROJFACS(Word P,Word Q,Word k,Word *Pp_,Word *PpO_,Word *PpN_)
{
      Word Q_k,Pp,P_k,PpO,PpN,T;

Step1: /* Construct Pp. */
      Q_k = LELTI(Q,k);
      for(Pp = NIL; Q_k != NIL; Q_k = RED(Q_k))
	Pp = COMP(LELTI(FIRST(Q_k),PO_POLY),Pp);
      Pp = INV(Pp);

Step2: /* Construct PpO. */
      P_k = LELTI(P,k);
      for(PpO = NIL; P_k != NIL; P_k = RED(P_k))
	PpO = COMP(LELTI(FIRST(P_k),PO_POLY),PpO);
      PpO = INV(PpO);

Step3: /* Construct PpN. */
      PpN = Pp;
      T = PpO;
      while (T != NIL) {
	T = RED(T); PpN = RED(PpN); }

Return: /* */
      *Pp_  = Pp;
      *PpO_ = PpO;
      *PpN_ = PpN;
      return;
}
