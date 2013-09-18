/*======================================================================
                      SWRITE(s)

String write.

Inputs
  s : a character string (in C format, i.e. an array of char, 
      ending with '\0').

Side effects
  s is written out to the output stream.
======================================================================*/
#include "saclib.h"

void SWRITE(s)
       const char *s;
{
       /* hide algorithm */

Step1: /* Write out the string. */
       while (*s != '\0')
         {
         CWRITE(*s);
         s++;
         }

Return: /* Prepare for return. */
       return;
}
