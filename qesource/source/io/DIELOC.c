/*======================================================================
                      DIELOC()

Display Input Error Location.
======================================================================*/
#include "qepcad.h"


// Moved to CREAD

/* void DIELOC() */
/* { */
/*        Word b,e; */
/*        /\* hide b,e; *\/ */

/* Step1: /\* Trivial case. *\/ */
/*        if (IBUFF[IPOS] == '\n') goto Return; */

/* Step2: /\* Get the beginning position of display. *\/ */
/*        b = IPOS; */
/*        e = (IPOS + 1) % ISIZE; */
/*        do  */
/*          b = (b + ISIZE - 1) % ISIZE; */
/*        while (IBUFF[b] != '\n' && b != e); */
/*        if (IBUFF[b] == '\n') */
/*          b = (b + 1)  % ISIZE; */

/* Step3: /\* Display. *\/ */
/*        while (b != IPOS) */
/*          { */
/*          CWRITE(IBUFF[b]); */
/*          b = (b + 1) % ISIZE; */
/*          } */
/*        CWRITE(IBUFF[IPOS]); */
/*        CWRITE('\n'); */

/* Return: /\* Prepare for return. *\/ */
/*        return; */
/* } */
