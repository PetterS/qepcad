/*======================================================================
                      INITIO()

Initialize Input/Output.
======================================================================*/
#include "qepcad.h"
#include <stdlib.h>
#ifdef _MSC_VER
	namespace
	{
		bool isatty(int) { return false; }
	}
#else
	#include <unistd.h>
#endif

#include <iostream>
#include "db/readlineistream.h"

void InputContextInit(istream&);
void OutputContextInit(ostream&);

void INITIO()
{
       Word i;

Step1: /* Initialize Input. */	  
       if (isatty(0)) {
         #ifdef _MSC_VER
		   InputContextInit(std::cin);
         #else
           InputContextInit(*(new readlineIstream()));
         #endif
	   }
       else {
         InputContextInit(std::cin);
	   }
       
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
