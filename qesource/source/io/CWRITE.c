/*======================================================================
                      CWRITE(C)

Character write.  C is written to the output stream.
This version replaces the saclib CWRITE.
======================================================================*/
#include "qepcad.h"
#include <stdio.h>
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

class OutputContext
{
public:
  ostream *pout;
  Word OPOS;
};

static stack<OutputContext> OCS;
ostream *currOut;

void PushOutputContext(ostream &out) 
{
  OCS.push(OutputContext());
  OCS.top().pout = currOut;
  OCS.top().OPOS = OPOS;
  currOut = &out;
  OPOS = 0;
}

void PopOutputContext()
{
  currOut = OCS.top().pout;
  OPOS = OCS.top().OPOS;
  OCS.pop();
}

void OutputContextInit(ostream& defaultout) 
{
  OPOS = 0;
  currOut = &defaultout;
}


void CWRITE(Word C)
{
Step1: /* Write. */
      (*currOut) << char(C);
      if (C == '\n') 
	OPOS = 0;
      else
	OPOS++;

Return: /* Prepare for return. */
      return;
}
