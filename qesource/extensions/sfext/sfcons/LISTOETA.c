/*
List of extended Tarski atoms.
 */
#include "qepcad.h"

Word LISTOETA(Word P, Word i)
{
     Word L,n,L_A,p,B;

Step1: /* Construct list of all projection factors, in reverse order. */
     for(L = NIL, n = 1; n <= i; n++)
	 L = CCONC(LELTI(P,n),L);
     L = CINV(L);
     
 Step2: /* */
     for(L_A = NIL; L != NIL; L = RED(L)) {
	 p = FIRST(L);
	 B = PDEG(LELTI(p,PO_POLY));
	 L_A = CCONC(PLISTOETA(p,B > 1 ? B : 0),L_A); }
     
     return L_A;
}
/*
Polynomial list of extended Tarski atoms.
  p : a QEPCAD polynomial
  B : a bound on the number of roots (need not be a valid bound)
 */
Word PLISTOETA(Word p, Word B)
{
    Word L,I,i;

    L = NIL;
    I = RED(LELTI(p,PO_LABEL));

    for(i = B; i > 0; i--) {
	L = COMP(LIST2(I,LIST2(NEOP,i)),L);
	L = COMP(LIST2(I,LIST2(NEOP,-i)),L);

	L = COMP(LIST2(I,LIST2(EQOP,i)),L);
	L = COMP(LIST2(I,LIST2(EQOP,-i)),L);

	L = COMP(LIST2(I,LIST2(LTOP,i)),L);
	L = COMP(LIST2(I,LIST2(LTOP,-i)),L);

	L = COMP(LIST2(I,LIST2(GTOP,i)),L);
	L = COMP(LIST2(I,LIST2(GTOP,-i)),L);

	L = COMP(LIST2(I,LIST2(LEOP,i)),L);
	L = COMP(LIST2(I,LIST2(LEOP,-i)),L);

	L = COMP(LIST2(I,LIST2(GEOP,i)),L);
	L = COMP(LIST2(I,LIST2(GEOP,-i)),L); }

    L = COMP(LIST2(I,NEOP),L);
    L = COMP(LIST2(I,EQOP),L);
    L = COMP(LIST2(I,LTOP),L);
    L = COMP(LIST2(I,GTOP),L);
    L = COMP(LIST2(I,LEOP),L);
    L = COMP(LIST2(I,GEOP),L);
    
    return L;
}
