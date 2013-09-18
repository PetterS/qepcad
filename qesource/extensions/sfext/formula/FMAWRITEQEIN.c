/*

ForMulA write.

*/
#include "extlang.h"

void FMAWRITEQEIN(Word F, Word P, Word V)
{
  Word Q,L,i,j,n,np,P_i,G;

Step1: /* Get list of polynomials. */
  Q = FMAPOLLIST(F,P);

Step2: /* Print header. */
  if (Q == NIL) goto Return;
  SWRITE("[]\n(");
  np = n = SECOND(LELTI(LAST(Q),PO_LABEL));
  for(G = V; np > 0; np--,G = RED(G)) {
    VWRITE(FIRST(G));
    if (np > 1) SWRITE(","); }
  SWRITE(")\n");
  IWRITE(n);
  SWRITE("\n[\n");
  for(; Q != NIL; Q = RED(Q)) {
    i = SECOND(LELTI(FIRST(Q),PO_LABEL));
    IPDWRITE(i,LELTI(FIRST(Q),PO_POLY),V);
    if (RED(Q) != NIL) 
      SWRITE(" = 0 /\\ \n");
    else
      SWRITE(" = 0 \n"); }
  SWRITE("].\nprop\nfull\ngo\nres-alg S\ngo\nfast\ngo\n");

Step3: /* Print tvff. */
  SWRITE("tvff\n[\n");
  FMAWRITENEWLINE(F,P,V,0);
  SWRITE("\n].\n");
  
Return:
  return;
}


