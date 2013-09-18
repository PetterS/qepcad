/*
FMAATOMREAD

Q : Projection factor set
V : The variable list
F : The formula
t : sucess flag (1 if successfull, 0 otherwise)
 */

#include "extlang.h"

Word POLYINDEX(Word P, Word p, Word r, Word *t);

void FMAATOMREAD(Word Q, Word V, Word *F_, Word *t_)
{
       Word F,P,P1,P2,R,a,r,s,t,k,pi;
       char c;
       /* hide r,s,t; */

Step1: /* Read the left polynomial. */
        t = 1; r = LENGTH(V);
        IPEXPREAD(r,V,&P1,&t); if (t == 0) goto Return;

Step2: /* Read the relational operator. */
        RLOPRDR(&R,&t); if (t == 0) goto Return;

Step2p: /* Read Root expression (if it's there). */
	k = 0;
	do {
	  c = CREAD();
	} while (c == ' ' || c == '\n');
	if (c == '_')
	  if (CREAD() == 'r' && CREAD() == 'o' && CREAD() == 'o'
	      && CREAD() == 't' && CREAD() == '_')
	    k = IREAD();
	  else {
	    t = 0; goto Return; }
	else
	  BKSP();	      

Step3: /* Read the right polynomial. */
        IPEXPREAD(r,V,&P2,&t); if (t == 0) goto Return;

Setp4: /* Tarski Atom. */
	if (k == 0) {
	  if (P2 != 0) { t = 0; goto Return; }
	  pi = POLYINDEX(Q,P1,r,&t); 
	  F = LIST2(pi,R);
	  goto Return; }

Step5: /* Extended Atom. */
	pi = POLYINDEX(Q,P2,r,&t);
	/* should do an error check here! */
	F = LIST2(pi,LIST2(R,k));
	goto Return;

Step6: /* Error exit. */
        DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;
}

Word POLYINDEX(Word P, Word p, Word r, Word *t)
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
  
  if (*t == 0) { SWRITE("Polynomial not found!!\n"); }
  return RED(LELTI(pp,PO_LABEL));
}

