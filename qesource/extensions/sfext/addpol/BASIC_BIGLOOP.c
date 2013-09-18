/*  The big loop for SF construction. 
    It returns P and D, the projection factors and a CAD, which
    allow solution formula construction. */
#include "qepcad.h"

void STRIPPED_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_)
{
      Word P,D,G,C,T,N_T,Tb,Gb,Gbp,S_N_T,Tp,Gp,K,KT,p,i,S;
      Word Q,Q_i,Ps,Ds,Qb,Qb_i,Dsp,t,Ph;
      Word inum,tm;

Step1: /* Initialize. */
      P = NIL; for(i = N; i > 0; i--) { P = COMP(LELTI(P0,i),P); }
      D = D0; 
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }

Step2: /* Construct the conflicting pair set. */
      C = CFLCELLLIST(LIST1(D));
      for(t = C; t != NIL && FIRST(t) == NIL;t = RED(t));
      if (t == NIL) goto Return; /* If no conflicting pairs, return. */

Step3: /* Construct T. */
      BPOLSETS(C,D,P,&T,&N_T);

Step4: /* Construct G. */
      Gb = PMINHITSETWPTS(T,P,LELTI(G,N_T));
      G = NIL; for(i = 0; i < N; i++) { G = COMP(NIL,G); }
      SLELTI(G,N_T,Gb);

Step6:/* Construct K. */
      KCONST(Jb,Pb,Gb,&K,&KT);

Step8: /* Introduce new derivative, p. */
      p = NEWDERIV(KT,P,Pb,Jb,P);

Step9: /* Construct new P, the PROJ-closure of S u G u {p}. */
      Ps = LCOPY(P);
      SLELTI(P,N_T,PFSUNION(LELTI(P,N_T),LIST1(p)));
      PROJMCECCLOSURE(Pb,Jb,P);

Step10:/* Construct D, the RCAD defined by P. */
      P = PFSREORDER(P,Ps);
      D = RNCADRTV(D,Ps,P,N);

Step11:/* Repeat the Loop. */
      goto Step2;

Return:/* Return. */
      *P_ = P;
      *D_ = D;
      return;
}
