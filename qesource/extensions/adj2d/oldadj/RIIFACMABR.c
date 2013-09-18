/*
Refine isolating interval for Arnon-Collins-McCallum adjacency at binary rational

H = (h1,h2) LSI
I = (i1,i2) LSI

The interval is h2 = i2.

*/
#include "oldadj.h"

Word RIIFACMABR(Word P, Word J, Word K, Word *H, Word *I)
{
  Word i1,i2,b1,b2,p,h1,h2;
  
  
  b1 = FIRST(J);
  if (K != 0)
    b2 = SECOND(K);
  else
    b2 = SECOND(J);

  FIRST2(*H,&h1,&h2);
  FIRST2(*I,&i1,&i2);

  p = IPLBREVAL(2,P,b1);
  while(TSVSLI(p,LIST2(h1,h2)) != 0)
    h1 = LSIM(h1,h2);
  while(IUPLBREVAL(p,h1) == 0)
    h1 = LSIM(h1,h2);
  while(TSVSLI(p,LIST2(i1,i2)) != 0)
    i2 = LSIM(i1,i2);
  while(IUPLBREVAL(p,i2) == 0)
    i2 = LSIM(i1,i2);


  p = IPLBREVAL(2,P,b2);
  while(TSVSLI(p,LIST2(h1,h2)) != 0)
    h1 = LSIM(h1,h2);
  while(IUPLBREVAL(p,h1) == 0)
    h1 = LSIM(h1,h2);
  while(TSVSLI(p,LIST2(i1,i2)) != 0)
    i2 = LSIM(i1,i2);
  while(IUPLBREVAL(p,i2) == 0)
    i2 = LSIM(i1,i2);

  *H = LIST2(h1,h2);
  *I = LIST2(i1,i2);
  return LIST2(h1,i2);
}
