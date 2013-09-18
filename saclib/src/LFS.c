/*======================================================================
                         L <- LFS(s)

List from String.

Inputs
  s : a character string.

Outputs
  L : the list of the characters in s.
======================================================================*/
#include "saclib.h"
#include <string.h>

Word LFS(s)
       const char *s;
{
       Word L,i,l;
       const char *p;

Step1: /* Make a list from the string s. */
       L =NIL;
       l = strlen(s);
       p = s + l - 1;
       for (i=1; i<=l; i++)
         {
         L = COMP(*p,L);
         p--;
         }

Return: /* Prepare for return. */
       return(L);
}
