/*======================================================================
                      GCSI(s,EACSTACK)

Garbage collection, system independent.

Inputs
         s : a BETA-digit, the size in bytes at which data is aligned on the
             stack.
  EACSTACK : a C pointer, the address of the last element on the stack.

Side effects
  Active variables are marked. Then a new available cell list is formed
  from the unmarked cells and the marks are removed.
  If GCM=1 a report is written out. If the number of reclaimed cells
  is no more than NU / RHO  then a message is written and a failure
  occurs.
======================================================================*/
#include "replacesac.h"
#include <cstdio>
extern "C" {
extern void gcw_MARK();
}

void GCSI(Word s, char *EACSTACK)
{
       Word I,L,N,N1,Np,Np1,T,T1,c,**i,j,inc;
       char *a;
       GCArray *v;
       /* hide I,L,N,N1,Np,Np1,T,T1,c,i,j,inc,a,v; */

Step1: /* Setup. */
	  if (GCM == 1) {
         SWRITE("\nThe "); GWRITE(GCC+1); 
         SWRITE("--th garbage collection....\n");
       }
       T1 = CLOCK();

Step3: /* Mark the global variables. */
       L = GCGLOBALS; 
       while (L != NIL) {
         c = *((Word *)PTRFIRST(L));
	 if ((ISLIST(c) || ISGCA(c)) && !ISNIL(c))  MARK(c);
	 L = PTRRED(L);
       }

Step2: /* Mark the cells in the GCGLOBALS list. */
       L = GCGLOBALS; 
       while (L != NIL) {
	 I = RED(L);
	 SRED(L,-I);
	 L = I;
       }

Step3b: /* Mark the GCWord variables. */
       gcw_MARK();

Step4: /* Mark the cells accessible from the system stack. */
       if (((BACSTACK - EACSTACK) % s) != 0)
         FAIL("GCSI (marking stack)","Alignment error",BACSTACK,EACSTACK);
       if (EACSTACK > BACSTACK)
         inc = s;
       else
         inc = -s;
       for (a = BACSTACK; a != EACSTACK; a += inc) {
         c =  *((Word *) a);
	 if ((ISLIST(c) || ISGCA(c)) && !ISNIL(c))  MARK(c);
       }

Step5: /* Unmark the cells in the AVAIL and GCAAVAIL lists. */
       for (L=AVAIL,N1=0; L!=NIL; L=RED(L),N1++)
	 if (RED(L) <= -BETA)  
           SRED(L,-RED(L)); 
       for (L=GCAAVAIL,Np1=0; L!=NIL; L=GCASPACEBp[L].next,Np1++)
	 if (GCASPACEBp[L].next <= -BETA)
	   GCASPACEBp[L].next = -GCASPACEBp[L].next;

Step6: /* Reclaim unmarked cells */
       AVAIL = NIL;
       N = 0;
       for (L = BETA+NU-1; L > BETA; L -= 2) {
         if (RED(L) > 0) {
           SRED(L,AVAIL);
	   SFIRST(L,0);
           AVAIL = L;
           N++;
         }
         else
           SRED(L,-RED(L));
       }
       GCAAVAIL = NIL;
       Np = 0;
       for (I = BETApp-1; I > BETAp; I--) {
         if (GCASPACEBp[I].next > 0) {
           GCAFREE(I);
           Np++;
         }
         else
           GCASPACEBp[I].next = -GCASPACEBp[I].next;
       }

Step7: /* Increment counters. */
       T = CLOCK() - T1;
       TAU = TAU + T;
       GCC = GCC + 1;
       GCCC = GCCC + N - N1;
       GCAC = GCAC + Np - Np1;
  
Step8: /* Optional report. */
       if (GCM == 1 || N <= NU / RHO) {
         SWRITE("\n** ");
         GWRITE(N); SWRITE(" cells, ");
         GWRITE(Np); SWRITE(" arrays in ");
         GWRITE(T); SWRITE(" milliseconds.\n");
       }

Step9: /* Too few cells or arrays? */
       if (N <= NU / RHO)
         FAIL("GCSI (final check)","Too few cells reclaimed.",N,NU,RHO);
       if (Np == 0)
         FAIL("GCSI (final check)","No arrays reclaimed.",N,NU,RHO);

Return: /* Prepare for return. */
       return;
}





