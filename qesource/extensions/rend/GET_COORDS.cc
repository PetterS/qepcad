#include "rend.h"
#include <iostream>
using namespace std;


int get_coords(Word *x, Word *X, Word *y, Word *Y, Word *e, Word *d1, Word *d2)
{
  if (!(qein() >> *x >> *X >> *y >> *Y))
    return 0;

  *e = LBRNREAD();
  if (e == 0)
    return 0;
  
  if (! (qein() >> *d1 >> *d2) )
    return 0;
  
  return 1;
}
