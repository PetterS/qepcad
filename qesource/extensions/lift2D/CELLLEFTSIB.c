
/* Cell left sibling.
   Takes a QEPCAD cell c and CAD D and returns the left sibling
   of c in CAD D.
*/
#include "lift2d.h"

Word CELLLEFTSIB(Word c, Word D)
{
  Word Ip;
  Ip = CINV(LELTI(c,INDX));
  return CELLFINDEX(D,CINV(COMP(FIRST(Ip) - 1,RED(Ip))));
}
