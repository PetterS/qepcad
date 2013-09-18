/*  Projection factors of discriminant. */
#include "qepcad.h"

Word PFDISCRIM(Word q, Word P, Word J)
{
      Word i,h,D,d,L;

Step1: /* See if this discriminant has already been computed. */
      i = SECOND(LELTI(q,PO_LABEL));
      h = LIST4(PO_DIS,0,0,q);
      D = PPWITHHIST(J,i-1,h);

Step2: /* Compute it if it hasn't, get a list of its factors if it has. */
      if (! D) {
	d = IPDSCRQE(i,LELTI(q,PO_POLY));
	ADD2PROJPOLS(i-1,d,h,J,P,&D,&L); }
      else {
	L = LIST_OF_FACS(D,P); }

Return:/* Return. */
      return (L);
}
