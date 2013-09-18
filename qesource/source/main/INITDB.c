/*======================================================================
                      INITDB()

Initialize Databases.
======================================================================*/
#include "qepcad.h"

void INITDB()
{

Step1: /* Initialize. */
       DBAFCSBM = NIL;
       DBAFPNIP = NIL;
       DBAFUPGC = NIL;
       DBAFUPSFN = NIL;
       DBFNDTS = NIL;
       DBGETRP = NIL;
       DBMODCR = NIL;
       DBIPFAC = NIL;
       DBSUBST = NIL;

Return: /* Prepare for return. */
       return;
}
