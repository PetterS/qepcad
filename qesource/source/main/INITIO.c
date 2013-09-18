/*======================================================================
                      INITIO()

Initialize Input/Output.
======================================================================*/
#include "qepcad.h"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "db/readlineistream.h"

void InputContextInit(istream&);
void OutputContextInit(ostream&);

void INITIO()
{
       Word i;

Step1: /* Initialize Input. */	  
       if (isatty(0)) 
	 InputContextInit(*(new readlineIstream()));
       else
	 InputContextInit(std::cin);
       
Step2: /* Initialize Output. */
       OutputContextInit(std::cout);

Step3: /* Control Echo. */
       if (!isatty(0) && !NOECHOSWITCHSET)
         setECHO(1);
       else
         setECHO(0);

Return: /* Prepare for return. */
       return;
}
