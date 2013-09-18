/*======================================================================
                      SETTRUTHVALUE(t,I,c)

======================================================================*/
#include "qepcad.h"

void SETTRUTHVALUE(Word t, Word I, Word c)
{
  Word S;

  S = LELTI(c,CHILD);
  if (I == NIL)
    if (S == NIL) {
      SLELTI(c,TRUTH,t);
      SLELTI(c,HOWTV,MANSET); }
    else {
      for(; S != NIL; S = RED(S))
	SETTRUTHVALUE(t,NIL,FIRST(S)); }
  else
    SETTRUTHVALUE(t,RED(I),LELTI(S,FIRST(I)));
  return;
}



void KTHSECTIONTRUE(Word c, Word j, Word k, Word op, Word i)
{
  Word S,s,m,t,flag;
  S = LELTI(c,CHILD);
  if (LELTI(c,LEVEL) == i - 1) {
    for(m = 0,flag = 0; S != NIL; S = RED(S),flag = 0) {
      s = FIRST(S);
      if (LELTI(FIRST(LELTI(s,SIGNPF)),j) == ZERO) {
	m++;
	flag = 1; }
      t = FALSE;
      switch(op) {
      case (LTOP) : if (m < k) t = TRUE; break;
      case (EQOP) : if (m == k && flag) t = TRUE;  break;
      case (GTOP) : if (m > k || (m == k && !flag)) t = TRUE; break;
      case (GEOP) : if (m >= k) t = TRUE; break;
      case (NEOP) : if (m != k || !flag) t = TRUE; break;
      case (LEOP) : if (m < k || (m == k && flag)) t = TRUE; break; }
      SLELTI(s,TRUTH,t);
      SLELTI(s,HOWTV,MANSET); } }
  else 
    for(; S != NIL; S = RED(S))
      KTHSECTIONTRUE(FIRST(S),j,k,op,i);
  return;
}
