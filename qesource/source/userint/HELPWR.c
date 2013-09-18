/*======================================================================*\
                          HELPWR(I)

Help Write.
I is a command ID.
\*======================================================================*/
#include "qepcad.h"
#include <stdio.h>

void HELPWR(Word I)
{
  extern char *Helps[];
  char *c;
  int i;
  
  for (i=1;i<=70;i++) putchar('-');
  c = Helps[I];
  while (*c) putchar(*c++);
  for (i=1;i<=70;i++) putchar('-'); putchar('\n');
}



