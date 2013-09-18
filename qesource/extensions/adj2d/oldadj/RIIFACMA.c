/*
Refine isolating interval for Arnon-Collins-McCallum adjacency

*/
#include "oldadj.h"

Word RIIFACMA(Word I, Word A, Word t, Word P, Word J, Word K)
{
  Word i1,i2,b1,b2,p,i,s;
  
  FIRST2(I,&i1,&i2);
  
  b1 = FIRST(J);
  if (K != 0)
    b2 = SECOND(K);
  else
    b2 = SECOND(J);
  
  p = IPLBREVAL(2,P,b1);
  while(TSVSLI(p,LIST2(i1,i2)) != 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }
  while(IUPLBREVAL(p,i1) == 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }
  while(IUPLBREVAL(p,i2) == 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }

  p = IPLBREVAL(2,P,b2);
  while(TSVSLI(p,LIST2(i1,i2)) != 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }
  while(IUPLBREVAL(p,i1) == 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }
  while(IUPLBREVAL(p,i2) == 0)
       {i = LSIM(i1,i2);
    s = LBRNSIGN(IUPLBREVAL(A,i));
    if (s == 0) {
      i1 = LSIM(i1,i);
      i2 = LSIM(i,i2); }
    else if (s == t)
      i2 = i;
    else
      i1 = i; }
      
  return LIST2(i1,i2);
}


