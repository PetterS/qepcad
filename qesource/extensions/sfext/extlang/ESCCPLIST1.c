/*

Extended sub-CAD conflicting pair list 1.

L  : a list (l_1, ..., l_n) of cells, all with the same signiture.  There is
     an m s.t. if l_i and l_j have different truth values, then the projections
     onto m-space of l_i and l_j are distinct cells in the same stack.
m  : the aforementioned "m".

Q  : a list (q_1, ....,q_h) of all conflicting pairs associated with the
     cells from L.  Each conflicting pair is given as a pair of cells of
     the highest level with different truth values.  If q_i = (a,b), then
     the projections onto m-space of a and b are distinct cells in the
     same stack, the projection of a being below the projection of b.

 */
#include "extlang.h"
static Word compare(Word a, Word b);
static int curr_m;

Word ESCCPLIST1(Word L, Word m)
{
  Word Q,Lp,o1,o2,T;
  Q = NIL;
  curr_m = m;
  for(Lp = GMSDSL(L,compare); Lp != NIL; Lp = RED(Lp)) {
    for(ADV(Lp,&o1,&T); T != NIL; T = RED(T)) {
      o2 = FIRST(T);
      if (LELTI(o1,SC_CDTV) != LELTI(o2,SC_CDTV)) {
	Q = COMP(LIST2(o1,o2),Q); } } }
  return Q;
}

static Word compare(Word a, Word b)
{
  Word I_a,I_b;
  I_a = LELTI(LELTI(LELTI(a,SC_REP),INDX),curr_m);
  I_b = LELTI(LELTI(LELTI(b,SC_REP),INDX),curr_m);
  return I_a < I_b ? -1 : (I_a > I_b);
}
