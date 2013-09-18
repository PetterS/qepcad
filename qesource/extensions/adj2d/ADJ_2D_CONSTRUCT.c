/*======================================================================
                      ADJ_2D_CONSTRUCT(c,P2)

Construct a stack.
 
Input
    c : a qepcad cell for a level 1 sector cell.
    P2: is the list of the level 2 projection factors.
 
Output

======================================================================*/
#include "adj2D.h"
#include "qepcad.h"

void QepcadCls::ADJ_2D_CONSTRUCT(Word c, Word P2)
{
  Word s,sh,M,K,C,Pps,T,B,E,I;

Step1:/* Convert rep. */
  s = LELTI(c,SAMPLE);
  sh = CONVERT(s,1);
  SLELTI(c,SAMPLE,sh);
  FIRST3(sh,&M,&K,&C);

Step3: /* Rational sample point is of course guaranteed. */
  C = RCFAFC(C);
  Pps = SUBSTR(c,1,C,P2);
  SLELTI(c,DEGSUB,PLDEG(Pps));
  IPLSRP(Pps,&s,&T);
  IPFSBM(1,T,&B,&E);
  if (B != NIL) I = IPLRRI(B); else I = NIL;
  ECR(c,I,E,B);
  SIGNPR(c,1,B,I,E,s);
  
  return;
}
