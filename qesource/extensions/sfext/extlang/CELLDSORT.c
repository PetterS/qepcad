/*  Cell Descendants sorted. */
/*  At this point I'm doing this without partial CAD's!! */
#include "extlang.h"
static Word compare(Word c1, Word c2);

Word CELLDSORT(Word I_L)
{
  Word O_L,S,T,s;

  if (I_L == NIL || !ISLIST(LELTI(FIRST(I_L),SC_CDTV))) {
    O_L = LIST1(I_L);
    goto Return; }

 Step1: /* Initialize S. */
  S = NIL;
  for(T = I_L; T != NIL; T = RED(T))
    S = CCONC(LELTI(FIRST(T),SC_CDTV),S);
  
 Step2: /* Sort S. */
  S = INV(GISL(S,compare));

 Step3: /* */
  O_L = NIL;
  while(S != NIL) {
    T = NIL;
    while (S != NIL && (T == NIL || compare(FIRST(S),s) == 0)) {
      ADV(S,&s,&S);
      T = COMP(s,T); }
    O_L = CONC(CELLDSORT(T),O_L); }
  
 Return: /* Prepare to return. */
  return O_L;
}

static Word compare(Word c1, Word c2)
{
  Word s1,s2,t,a1,a2;
  s1 = CCONC(LELTI(c1,SC_SIGN),LELTI(c1,SC_EXTS));
  s2 = CCONC(LELTI(c2,SC_SIGN),LELTI(c2,SC_EXTS));
  t = 0;
  while(s1 != NIL) {
    ADV(s1,&a1,&s1);
    ADV(s2,&a2,&s2);
    if (a1 != a2) {
      t = BDCOMP(a1,a2);
      break; } }
  return t;
}
