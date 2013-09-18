/*======================================================================
                      ENDQEPCAD()

Clean up the qepcad system.
======================================================================*/
#include "qepcad.h"
#include "db/CAPolicy.h"
extern ServerBase GVSB;

void ENDQEPCAD()
{
  /* Delete the CAServers ... mostly to let them kill child processes! */
  for(ServerBase::iterator p = GVSB.begin(); p != GVSB.end(); ++p)    
    delete p->second;
  GVSB.clear();
  delete GVCAP;
  delete GVContext;

Return: /* Prepare for return. */
       return;
}
