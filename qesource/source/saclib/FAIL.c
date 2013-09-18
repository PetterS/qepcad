/*======================================================================
                      FAIL(algName,msg,...)

Failure handler. 
** REDEFINED FOR QEPCAD! QepcadB needs to, potentially, kill some child
** processes.  That's what this adds.  A better long-term solution is to
** change Saclib's FAIL to add an analogue to "atexit".

Inputs
  algName :  the name of the algorithm which called this algorithm.
  msg     :  a string giving the reason for the failure.
  ...     :  any other arguments that the calling algorithm passed.

Side effects
  This algorithm display the information about why the failure occurred
  and aborts the whole program.
======================================================================*/
#include "qepcad.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef __STDC__
void FAIL(const char *algName, const char *msg,...)
#else
void FAIL(algName,msg)
       const char *algName;
       const char *msg;
#endif
{
       va_list argPtr;
       //       extern int strcmp();

Step0: /* Shutdown child processes! This is the QEPCAD-specific step. */
       ENDQEPCAD();

Step1: /* Basic message. */
       SWRITE("\n\n");
       SWRITE("Failure occurred in:    "); SWRITE(algName); SWRITE("\n");
       SWRITE("Reason for the failure: "); SWRITE(msg);  SWRITE("\n\n");

Step2: /* Failures from the SACLIB library. */
       va_start(argPtr,msg);

       /* GCSI marking stack */
       if (!strcmp(algName,"GCSI (marking stack)"))
         {
         /*  Note that this step is NOT portable since we are assuming that
             pointers fit into integers. */
	   SWRITE("BACSTACK = "); fprintf(stderr,"%p\n",va_arg(argPtr,char *));
	   //GWRITE((int)va_arg(argPtr,char *)); SWRITE("\n");
	   SWRITE("EACSTACK = "); fprintf(stderr,"%p\n",va_arg(argPtr,char *));
	   //GWRITE((int)va_arg(argPtr,char *)); SWRITE("\n");
         goto Abort;
         }

       /* GCSI final check */
       if (!strcmp(algName,"GCSI (final check)")) {
         SWRITE("N   = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("NU  = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("RHO = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

       /* GREAD */
       if (!strcmp(algName,"GREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* AREAD */
       if (!strcmp(algName,"AREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* LREAD */
       if (!strcmp(algName,"LREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* IREAD */
       if (!strcmp(algName,"IREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* DIIPREAD */
       if (!strcmp(algName,"DIIPREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* DIRPREAD */
       if (!strcmp(algName,"DIRPREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* IPREAD */
       if (!strcmp(algName,"IPREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* RPREAD */
       if (!strcmp(algName,"RPREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* VLREAD */
       if (!strcmp(algName,"VLREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* VREAD */
       if (!strcmp(algName,"VREAD")) {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* SFRLS */
       if (!strcmp(algName,"SFRLS")) {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("a = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("e = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

       /* SFRQ */
       if (!strcmp(algName,"SFRQ")) {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("g = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

       /* SFRSUM */
       if (!strcmp(algName,"SFRSUM")) {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("g = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

       /* MAIPDM */
       if (!strcmp(algName,"MAIPDM")) {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("b  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("bp = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Abort;
         }

       /* MMPDMA */
       if (!strcmp(algName,"MMPDMA")) {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("p  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("M  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

       /* IPGCDC */
       if (!strcmp(algName,"IPGCDC")) {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("gb = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Abort;
         }

       /* IPRES */
       if (!strcmp(algName,"IPRES")) {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("f  = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("Q  = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Abort;
         }

       /* AFINV */
       if (!strcmp(algName,"AFINV")) {
         SWRITE("M  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Abort;
         }

Abort: /* Prepare for abort. */
       SWRITE("\n\nNow the FAIL handler is aborting the program ...\n");
       va_end(argPtr);
       abort();

Exit:  /* Prepare for exit. */
       SWRITE("\n\nNow the FAIL handler is exiting the program ...\n");
       va_end(argPtr);
       exit(1);
}
