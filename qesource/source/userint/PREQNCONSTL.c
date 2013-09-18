/*===========================================================================
                         PREQNCONSTL()

Process eqn-const-list command.
===========================================================================*/
#include "qepcad.h"

void QepcadCls::PREQNCONSTL()
{

       Word i,j,t,E,k,L,Lp,L1;

Step1: /* Check if propagation of equational constraints was specified. */
       if (PCPROPEC == FALSE) {
	  SWRITE("Error PREQNCONSTL: \"prop-eqn-const\" was not issued.\n");
	  goto Return; }

Step2: /* Read in argument of the form "(A_i,j,...,A_m,n)". */
       L = NIL;
       k = 0;
       if (CREADB() != '(') {
	  SWRITE("Error PREQNCONSTL: '(' was expected.\n");
	  goto Step5; }
       do {
	  if (CREADB() != 'A') {
	     SWRITE("Error PREQNCONSTL: 'A' was expected.\n");
	     goto Step5; }
	  if (CREADB() != '_') {
	     SWRITE("Error PREQNCONSTL: '_' was expected.\n");
	     goto Step5; }
	  GREADR(&i,&t); if (t == 0) goto Return;
	  if (i > k) k = i;
	  if (CREADB() != ',') {
	     SWRITE("Error PREQNCONSTL: ',' was expected.\n");
	     goto Step5; }
	  GREADR(&j,&t); if (t == 0) goto Return;
	  if (LKAHEAD() == ',') CREADB();
	  L = COMP(MKLABEL("A",i,j),L); }
       while (LKAHEAD() != ')');
       L = INV(L);
       CREADB();

Step3: /* Check validity of labels. */
       Lp = L;
       while (Lp != NIL) {
	  ADV(Lp,&L1,&Lp);
	  if (VALIDLBL(L1,GVPF) != TRUE) {
	     SWRITE("Error PREQNCONSTL: ");
	     LABELWR(FIRST(L1),RED(L1));
	     SWRITE(" -- No such polynomial.\n");
	     goto Return; }
	  if (LBLLEVEL(L1) > GVLV) {
	     SWRITE("Error PREQNCONSTL: ");
	     SWRITE("Declared constraint is of too high a level.\n");
	     goto Return; } }

Step4: /* Update list of equational constraints. */
       E = LELTI(GVEQNCONST,k);
       if (E == NIL)
	  SLELTI(GVPIVOT,k,L);
       E = SUFFIX(E,L);
       SLELTI(GVEQNCONST,k,E);
       goto Return;
       
Step5: /* Input error. */
       DIELOC();

Return: /* Prepare for return. */
       return;
}



Word POLYLABEL(Word P, Word p, Word r, Word *t)
{
  Word P_r, Pp, pp;

  for(; PDEG(p) == 0; r--)
    p = SECOND(p);

  /* Is p already in P? */
  P_r = LELTI(P,r); *t = 0;
  for(Pp = P_r; Pp != NIL; Pp = RED(Pp)) {
    pp = FIRST(Pp);
    if ( EQUAL(LELTI(pp,PO_POLY),p) ) {
      *t = 1; break; } }

  return LELTI(pp,PO_LABEL);
}

void QepcadCls::PREQNCONSTPOLY()
{
  Word t1,t2,t3,r,P1,E,k,pi;

  // Check if propagation of equational constraints was specified. 
  if (PCPROPEC == FALSE) {
    SWRITE("Error PREQNCONSTL: \"prop-eqn-const\" was not issued.\n");
    return; }

  // Read constraint polynomial, and trim representation to poly's level
  t1 = 1; r = LENGTH(GVVL);
  IPEXPREAD(r,GVVL,&P1,&t1); 
  if (t1 != 0) { for(; r > 0 && PDEG(P1) == 0; r--) P1 = SECOND(P1); }

  // ERROR: polynomial expression is bad!
  if (t1 == 0) {
    SWRITE("ERROR! Invalid polynomial expression!\n");
    return; }

  // Find index of poly P1 (or -P1)
  pi = POLYLABEL(GVPF,P1,r,&t2);
  if (t2 == 0) {   pi = POLYLABEL(GVPF,IPNEG(r,P1),r,&t3); }
  
  // ERROR: neither P1 nor -P1 is a projection factor
  if (!t2 && !t3) {
    SWRITE("ERROR! Polynomial not a projection factor!\n");
    return; }

  // Update list of equational constraints. 
  E = LELTI(GVEQNCONST,r);
  if (E == NIL)
    SLELTI(GVPIVOT,r,LIST1(pi));
  E = SUFFIX(E,LIST1(pi));
  SLELTI(GVEQNCONST,r,E);
    
  return;
}
