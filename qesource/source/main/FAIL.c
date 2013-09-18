/*======================================================================
                      FAIL(algName,...)

Failure handler.  (Replaces the saclib FAIL.)
======================================================================*/
#include "qepcad.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void FAIL(char *algName, char *msg,...)
{
       va_list argPtr;

Step1: /* Basic message. */
       SWRITE("\n\n");
       SWRITE("Failure occurred in:    "); SWRITE(algName); SWRITE("\n");
       SWRITE("Reason for the failure: "); SWRITE(msg);  SWRITE("\n\n");

Step2: /* Failures from the SACLIB library. */
       va_start(argPtr,msg);

       /* GC Step2 */
       if (!strcmp(algName,"GC Step3")) 
         {
         /*  Please note that this step is NOT portable since  we are assuming that 
             addresses can taken as integers. */
         SWRITE("BACSTACK = "); 
	 fprintf(stdout,"%p\n",va_arg(argPtr,char *));
	 //GWRITE((int)va_arg(argPtr,char *)); SWRITE("\n");
         SWRITE("EACSTACK = "); 
	 fprintf(stdout,"%p\n",va_arg(argPtr,char *));
	 //GWRITE((int)va_arg(argPtr,char *)); SWRITE("\n");
         goto Exit;
         }

       /* GC Step8 */
       if (!strcmp(algName,"GC Step8")) 
         {
         SWRITE("N   = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("NU  = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("RHO = "); GWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* GREAD */
       if (!strcmp(algName,"GREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* AREAD */
       if (!strcmp(algName,"AREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* LREAD */
       if (!strcmp(algName,"LREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* IREAD */
       if (!strcmp(algName,"IREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* DIIPREAD */
       if (!strcmp(algName,"DIIPREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* DIRPREAD */
       if (!strcmp(algName,"DIRPREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* VLREAD */
       if (!strcmp(algName,"VLREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* VREAD */
       if (!strcmp(algName,"VREAD"))
         {
         SWRITE("C = "); CWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* SFRLS */
       if (!strcmp(algName,"SFRLS"))
         {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("a = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("e = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }
       
       /* SFRQ */
       if (!strcmp(algName,"SFRQ"))
         {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("g = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* SFRSUM */
       if (!strcmp(algName,"SFRSUM"))
         {
         SWRITE("u = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("v = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("g = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* IUPTR1 */
       if (!strcmp(algName,"IUPTR1"))
         {
         SWRITE("A    = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("m    = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("size = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* MAIPDM */
       if (!strcmp(algName,"MAIPDM"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("b  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("bp = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* MMPDMA */
       if (!strcmp(algName,"MMPDMA"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("p  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("M  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* IPGCDC */
       if (!strcmp(algName,"IPGCDC"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("gb = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* IPRES */
       if (!strcmp(algName,"IPRES"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("f  = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("Q  = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* IUPRC */
       if (!strcmp(algName,"IUPRC"))
         {
         SWRITE("A = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("f = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("Q = "); IWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* MPGCDC */
       if (!strcmp(algName,"MPGCDC"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("p  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* MPRES */
       if (!strcmp(algName,"MPRES"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("p  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

       /* ISFPF */
       if (!strcmp(algName,"ISFPF"))
         {
         SWRITE("r  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* IUPFDS */
       if (!strcmp(algName,"IUPFDS"))
         {
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("The current length of the LPRIME list = "); GWRITE(LENGTH(LPRIME)); SWRITE("\n");
         goto Exit;
         }

       /* AFINV */
       if (!strcmp(algName,"AFINV"))
         {
         SWRITE("M  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("A  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         SWRITE("B  = "); OWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

Step3: /* Failures from the qepcad system. */

       /* CONSTRUCT. */
       if (!strcmp(algName,"CONSTRUCT"))
         {
         int k;
         k = va_arg(argPtr,int);
         SWRITE("k  = "); OWRITE(k); SWRITE("\n");
         SWRITE("M  = "); IPDWRITE(1,va_arg(argPtr,int),LIST1(LFS("a"))); SWRITE("\
n");
         SWRITE("b  = "); LWRITE(va_arg(argPtr,int)); SWRITE("\n");
         OWRITE(va_arg(argPtr,int));
         SWRITE("S  = "); LWRITE(va_arg(argPtr,int)); SWRITE("\n");
         goto Exit;
         }

Exit: /* Prepare for quitting. */
       //       SWRITE("\nThe current statistics:\n");
       //       STATWR();
       SWRITE("\n\nNow the FAIL handler is quitting the program.....\n");
       va_end(argPtr);
       exit(1);
}













