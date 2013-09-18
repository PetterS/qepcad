/*======================================================================
                      C <- CREAD()

Character read.  (Replaces the saclib CREAD.)

Outputs
  C : the next character from the input stream.

Side effects
  LASTCHAR : set to the character C, for backspacing.
======================================================================*/
#include "qepcad.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stack>
#include <fstream>
#include <iostream>
#include "db/readlineistream.h"
#include "db/convenientstreams.h"
using namespace std;

static istream *currIn = 0;
static char IBUFF[ISIZE];    /* The size of input buffer for errory display. */
static Word IPOS;            /* The position of the last character read. */
static Word ECHO;            /* Echo the input if 1. */
static Word WASBKSP;         /* 1 if there was backspace. */
static Word INSTATE = 0;     /* 0=standard, 1=in comment */

istream& qein() { return *currIn; }

Word setECHO(Word k) { swap(k,ECHO); return k; }
Word setWASBKSP(Word k) { swap(k,WASBKSP); return k; }

class InputContext
{
public:
  Word LASTCHAR, WASBKSP, ECHO, INSTATE;
  char IBUFF[ISIZE];
  istream *pin;
};

static stack<InputContext> ICS;

void PushInputContext(istream &in) 
{
  // Save Current Context
  ICS.push(InputContext());
  ICS.top().LASTCHAR = LASTCHAR;
  ICS.top().WASBKSP = WASBKSP;
  ICS.top().ECHO = ECHO;
  ICS.top().INSTATE = INSTATE;
  ICS.top().pin = currIn;
  for(int i = 0; i < ISIZE; ++i)  ICS.top().IBUFF[i] = IBUFF[i];

  // Create a new Current Context
  InputContextInit(in);
  /*
  LASTCHAR = '\n';
  WASBKSP = 0;
  ECHO = 0;
  INSTATE = 0;
  currIn = &in;
  for (int i=0; i < ISIZE; i++) IBUFF[i] = '?';
  IPOS = 0; IBUFF[IPOS] = '\n';
  */
}

void PopInputContext()
{
  LASTCHAR = ICS.top().LASTCHAR;
  WASBKSP = ICS.top().WASBKSP;
  ECHO = ICS.top().ECHO;
  INSTATE = ICS.top().INSTATE;
  currIn = ICS.top().pin;
  for(int i = 0; i < ISIZE; ++i)  IBUFF[i] = ICS.top().IBUFF[i];
  ICS.pop();
}

void InputContextInit(istream& defaultin) 
{ 
  LASTCHAR = '\n';
  WASBKSP = 0;
  ECHO = 0;
  INSTATE = 0;
  currIn = &defaultin;
  for (int i=0; i < ISIZE; i++) IBUFF[i] = '?';
  IPOS = 0; IBUFF[IPOS] = '\n';
}


Word CREAD()
{
       Word C;
       /* hide algorithm */

Step1: /* If there was backspace. */
       if (! WASBKSP) goto Step2;
       C = LASTCHAR;
       WASBKSP = 0;
       goto Return;

Step2: /* Get a new character. */
       C = (*currIn).get(); //C = getc(INSTREAM);

Step3: /* End of file. */
       if (C == EOF)
       {
	 cerr << "\007\007\007";
	 int fd = open("/dev/tty",O_RDONLY);
	 PushInputContext(*(new readlineIstream(fd)));
         //C = (*currIn).get();
         return CREAD();
       }

       else if (INSTATE == 0 && C == '#')  { INSTATE = 1; return CREAD(); }
       else if (INSTATE == 1 && C != '\n') { return CREAD(); }
       else if (INSTATE == 1 && C == '\n') { INSTATE = 0; }


Step4: /* Remember the character. */
       LASTCHAR = C;

Step5: /* If requested, echo. */
       if (ECHO) CWRITE(C);

Step6: /* Keep it in the IBUFF. */
       IPOS = (IPOS + 1) % ISIZE;
       IBUFF[IPOS] = C;

Return: /* Prepare for return. */
       return(C);
}


void DIELOC()
{
       Word b,e;
       /* hide b,e; */

Step1: /* Trivial case. */
       if (IBUFF[IPOS] == '\n') goto Return;

Step2: /* Get the beginning position of display. */
       b = IPOS;
       e = (IPOS + 1) % ISIZE;
       do 
         b = (b + ISIZE - 1) % ISIZE;
       while (IBUFF[b] != '\n' && b != e);
       if (IBUFF[b] == '\n')
         b = (b + 1)  % ISIZE;

Step3: /* Display. */
       while (b != IPOS)
         {
         CWRITE(IBUFF[b]);
         b = (b + 1) % ISIZE;
         }
       CWRITE(IBUFF[IPOS]);
       CWRITE('\n');

Return: /* Prepare for return. */
       return;
}




