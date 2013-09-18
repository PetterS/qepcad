/*======================================================================
                      w <-- VECTOR_DIF_S(u,v,f)

Vector difference "special".

Inputs
  u  : a list of BETA-digits.
  v  : a list of BETA-digits, LENGTH(u) = LENGTH(v).

Outputs
  w  : a list of BETA-digits of length LENGTH(u).  Each componant of
       w is the difference of componants of u and v.
  f  : 0 if all entries of w 0, 
       1 if all entries non-negative, even, and some non-zero.
       2 if all entries non-negative, some odd
       3 if there are negative entries.
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"

Word VECTOR_DIF_S(Word u, Word v, Word *f)
{
  Word s,w,c;

  Word fo, fn, fnz;
    
  fo = 0;
  fn = 0;
  fnz = 0;
  for(s = NIL; u != NIL; u = RED(u), v = RED(v)) {
    c = FIRST(u) - FIRST(v);
    if (c < 0)      
      fn = 1;
    if ( (c & 1) == 1 )
      fo = 1;
    if (c != 0)
      fnz = 1;
    s = COMP(c,s); }
  w = INV(s);
  
  if (fn)
    *f = 3; /* There are negative entries. */
  else if (fo)
    *f = 2; /* All entries non-negative, some odd. */
  else if (fnz)
    *f = 1; /* All entires non-negative, even, and some non-zero. */
  else 
    *f = 0; /* All entries zero. */
  return w;
}
