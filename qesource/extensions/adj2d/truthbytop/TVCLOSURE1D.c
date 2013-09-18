/*======================================================================

Truth value closure 1D.

Inputs:
D : a CAD cell.
P : a thoroughly useless parameter.
J : a thoroughly useless parameter.
k : the level of the CAD in which D resides
t : a type of truth value closure:

  t = 1 : means solution space closed.
  t = 2 : means non-solution space closed.
  t = 3 : means solution space is the closure of an open set.

The truth-value closure is preformed in a stack

======================================================================*/
#include "truthbytop.h"
#include "adj2D.h"

static void topinfset(Word c, Word t)
{
  if (LELTI(c,TRUTH) == UNDET) {
	  SLELTI(c,TRUTH,t);
	  SLELTI(c,HOWTV,TOPINF); }
  return;
}

void TVCLOSURE1D(Word D, Word P, Word J, Word k, Word t)
{
  Word S,cl,cm,cr,tl,tm,tr,I,fdflag ;
  
Step1: /* Initialize and check special cases. */
  S = LELTI(D,CHILD);
  if (S == NIL || LENGTH(S) == 1)
    goto Return;

Step2: /* */
  switch (t) {
  case 1: /* solution space closed */
    do {
      ADV2(S,&cl,&cm,&S); cr = FIRST(S);
      if (CCTV(cm) == UNDET) {
	if (CCTV(cl) == TRUE || CCTV(cr) == TRUE)
	  topinfset(cm,TRUE); }
      else 
	if (CCTV(cm) == FALSE) {
	  topinfset(cl,FALSE);
	  topinfset(cr,FALSE); }
    }while(RED(S) != NIL);
    break;

  case 2: /* non-solution space closed */
    do {
      ADV2(S,&cl,&cm,&S); cr = FIRST(S);
      if (CCTV(cm) == UNDET) {
	if (CCTV(cl) == FALSE || CCTV(cr) == FALSE)
	  topinfset(cm,FALSE); }
      else 
	if (CCTV(cm) == TRUE) {
	  topinfset(cl,TRUE);
	  topinfset(cr,TRUE); }
    }while(RED(S) != NIL);
    break;

  case 3: /* means solution space is the closure of an open set */
    /* The situation here is a little complicated.  If the stack
       is over a full dimensional cell, then you can say more than
       you can otherwise. fdflag is 1 if the stack is over a
       full-dimensional cell and 0 otherwise. */

    for(I = LELTI(D,INDX); I != NIL && EVEN(FIRST(I)); I = RED(I));
    fdflag = (I == NIL);

    /* This loop deduces: 
       1) if cm false then all neighbors false
       2) if cl true or cr true then cm true
       3) if cl false and cr false then cm flase
       The third conclusion is only valid for stacks over full dimensiona
       cells.
     */
    do {
      ADV2(S,&cl,&cm,&S); cr = FIRST(S);
      tm = CCTV(cm);
      if (tm == FALSE) {
	topinfset(cl,FALSE);
	topinfset(cr,FALSE); }
      else if (tm == UNDET) {
	tl = CCTV(cl);
	tr = CCTV(cr);
	if (tl == TRUE || tr == TRUE)
	  topinfset(cm,TRUE);
	else if (fdflag && tl == FALSE && tr == FALSE)
	  topinfset(cm,FALSE); }
    }while(RED(S) != NIL);

    /* This loop basically just applies the fact that, for a stack
       over a full dimensional cell, a true section implies one of
       the neighboring sectors is true. 
     */
    S = LELTI(D,CHILD);
    do {
      ADV2(S,&cl,&cm,&S); cr = FIRST(S);
      if (fdflag && CCTV(cm) == TRUE) {
	tl = CCTV(cl);
	tr = CCTV(cr);
	if (tl == FALSE)
	  topinfset(cr,TRUE);
	else if (tr == FALSE)
	  topinfset(cl,TRUE); }
    }while(RED(S) != NIL);

    break; }

Step3: /* Propogate truth values up. */
  CTVPROPUP(D,UNDET,k,TOPINF);

Return: /* Prepare to return. */
  return;
}
