/*======================================================================
                      ATOMFRDR(V; F,t)

Atomic Formula Read, robust.

\Input
  \parm{V} is a non-null list of variables. 

\Output  
  \parm{F} is an atomic formula whose variables 
           all occur in $V$, read from the input stream.
  \parm{t} is 1 if successful, 0 otherwise.
======================================================================*/
#include "qepcad.h"
Word RPONE(Word r, Word A); /* This should be part of saclib! */
void ETFATOMRDR(Word V, Word P1, BDigit R, Word *F_, Word *t_);

void ATOMFRDR(Word V, Word *F_, Word *t_)
{
       Word F,P,P1,P2,R,a,r,s,t;
       /* hide r,s,t; */

Step1: /* Read the left polynomial. */
        t = 1; r = LENGTH(V);
        RPEXPREAD(r,V,&P1,&t); if (t == 0) goto Return;

Step2: /* Read the relational operator. */
        RLOPRDR(&R,&t); if (t == 0) goto Return;

Step3: /* Read _root_k expression */
	if (CREADB() != '_') { BKSP(); goto Step4; }
	BKSP();
	ETFATOMRDR(V,P1,R,&F,&t);
	goto Return;

Step4: /* Read the right polynomial. */
        RPEXPREAD(r,V,&P2,&t); if (t == 0) goto Return;

Step5: /* Finish up. */
        P = RPDIF(r,P1,P2); IPSRP(r,P,&a,&P);
        s = RNSIGN(a); if (s < 0) P = IPNEG(r,P);
        F = LIST4(R,P,r,NIL); goto Return;

Step6: /* Error exit. */
        DIELOC(); t = 0; goto Return;

Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;
}


/*======================================================================
                      ETFATOMRDR(V,P1,R;F,t)

Extended Tarski formula atom read, robust

Inputs
  V : variable list
  P1: the left-hand side, already read, a rational |V|-variate polynomial
  R : the relational operator, already read

Outputs
  F : the ETF atomic formula
  t : t = 1 if the read was successful, t = 0 otherwise

  Note: It is assumed that the LHS and the relational op have been
  read, but that the _root_ has not.  The atomic formula returned
  is *not* normalized it is of the form (IROOT,T,j,P,k,NIL) where P
  is a saclib k-variate polynomial of level k

======================================================================*/
void ETFATOMRDR(Word V, Word P1, BDigit R, Word *F_, Word *t_)
{
        Word t, F, r, j, P2, P2p, r1, r2, a, P, s;

Step1: /* Prepare */
        t = 1; r = LENGTH(V);


Step2: /* Read "_root_" */
        if (CREADB() != '_' || CREADB() != 'r' ||  CREADB() != 'o' ||  
	    CREADB() != 'o' ||  CREADB() != 't' ||  CREADB() != '_') 
	{
	  SWRITE("_root_ expected!\n");
	  DIELOC(); t = 0; goto Return; 
	}
	
Step3: /* Read index j */
	GREADR(&j,&t);
	if (!t || j == 0)
	{
	  SWRITE("nonzero index for _root_ expected!\n");
	  DIELOC(); t = 0; goto Return; 
	}
      
Step4: /* Read the right polynomial. */
        RPEXPREAD(r,V,&P2,&t); if (t == 0) goto Return;
  
Step5: /* Ensure the this ETF formula is proper */
	PSIMREP(r,P1,&r1,&P1);
	PSIMREP(r,P2,&r2,&P2p);
	if (PRED(P1) != 0 || !RPONE(r1,RPDMV(r1,P1)) || r1 != r2)
	{
	  SWRITE("Not a *proper* Extended Tarski Formula!\n");
	  DIELOC(); t = 0; goto Return; 
	}

Step6: /* Construct F */
        IPSRP(r2,P2p,&a,&P);
        s = RNSIGN(a); if (s < 0) P = IPNEG(r2,P);
	F = LIST6(IROOT,R,j,P,r2,NIL);
	
Return: /* Prepare for return. */
       *F_ = F;
       *t_ = t;
       return;  
  
}

/*======================================================================
                      t <- RPONE(r,A)

Rational polynomial one.

Inputs
  A : in Q[X1,...,Xr].
  r : a BETA-digit, r >= 0, the number of variables.

Outputs
  t : in Z,if A=1 then t=1, otherwise t=0.
======================================================================*/

Word RPONE(Word r, Word A)
{
       Word a,i,t;
       /* hide algorithm */

Step1: /* Determine. */
       t = 0;
       if (A == 0)
         goto Return;
       a = A;
       for (i = 1; i <= r; i++)
       {
         if (PDEG(a) != 0)
           goto Return;
         a = PLDCF(a);
       }
       if (RNCOMP(a,RNINT(1)) == 0)
         t = 1;

Return: /* Prepare for return. */
       return(t);
}
