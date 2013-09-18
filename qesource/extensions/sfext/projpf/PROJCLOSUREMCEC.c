/*  PROJMCEC-closure. 
    Alters P, J and Q. */
#include "qepcad.h"

void QepcadCls::PROJMCECCLOSURE(Word P, Word J, Word Q)
{
      Word N,k,Q_k,PP,NP,pp,L,l,i,S,s;

Step1: /* Initialization. */
      N = LENGTH(Q);

Step2: /* Loop from */
      for(k = N; k > 1; k--) {

	Q_k = LELTI(Q,k);
	SEPPIVNONPIV(Q_k,k,&PP,&NP);

	while (PP != NIL) {
	  ADV(PP,&pp,&PP);

Step3: /* Add necessary coefficients of pp. */
	  L = PFSUFFCOEF(pp,P,J);
	  while (L != NIL ) { 
	    ADV(L,&l,&L); 
	    i = SECOND(LELTI(l,PO_LABEL));
	    SLELTI(Q,i,PFSUNION(LELTI(Q,i),LIST1(l))); }

Step4: /* Add factors of the discriminant of pp. */
	  if (PDEG(LELTI(pp,PO_POLY)) > 1) {
	    L = PFDISCRIM(pp,P,J);
	    while (L != NIL ) { 
	      ADV(L,&l,&L); 
	      i = SECOND(LELTI(l,PO_LABEL));
	      SLELTI(Q,i,PFSUNION(LELTI(Q,i),LIST1(l))); } }

Step5: /* Add resultants. */
	  for(S = CCONC(PP,NP); S != NIL; S = RED(S)) {
	    s = FIRST(S);
	    L = PFRES(pp,s,P,J);
	    while (L != NIL ) { 
	      ADV(L,&l,&L); 
	      i = SECOND(LELTI(l,PO_LABEL));
	      SLELTI(Q,i,PFSUNION(LELTI(Q,i),LIST1(l))); } } } }

Return:/* Return. */
      return;
}

