/*======================================================================
                      S <- SUBSTDB((c,k,M,b,B)

SUBST with database usage.
======================================================================*/
#include "qepcad.h"

Word SUBSTDB(Word c, Word k, Word M, Word b, Word B, QepcadCls &Q)
{
        Word S;

Step1: /* Data base usage turned off? */
        if (PCDBUSE == 'n') {
           S = Q.SUBST(c,k,M,b,B);
           goto Return; }

Step2: /* Search. */
	if (DBSRCH(DBSUBST,LIST4(k,M,b,B)) == 0) { 
           S = Q.SUBST(c,k,M,b,B);
           DBADD(DBSUBST,LIST4(k,M,b,B),S,&DBSUBST); }
	else 
	  S = DBINFO; 
	
Return: /* Return S. */
           return(S);
}
