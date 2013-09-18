/*  Projection factors of resultant. */
#include "qepcad.h"

Word PFRES(Word p, Word q, Word P, Word J)
{
      Word i,h,R,r,L;

Step1: /* See if this resultant has already been computed. */
      i = SECOND(LELTI(q,PO_LABEL));
      h = LIST6(PO_RES,0,0,p,0,q);
      R = PPWITHHIST(J,i-1,h);

Step2: /* Compute it if it hasn't, get a list of its factors if it has. */
      if (! R) {
	r = IPRESQE(i,LELTI(p,PO_POLY),LELTI(q,PO_POLY));
	ADD2PROJPOLS(i-1,r,h,J,P,&R,&L); }
      else {
	L = LIST_OF_FACS(R,P); }

Return:/* Return. */
      return (L);
}
