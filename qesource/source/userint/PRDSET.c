/*======================================================================
                      PRDSET()

Process "display setting" command.
======================================================================*/
#include "qepcad.h"

void QepcadCls::PRDSET()
{
       Word S,S1,k;
       /* hide k; */

Step1: /* Heading. */
       SWRITE("---------------------------------------------\n");
       SWRITE("             Current Settings\n");
       SWRITE("---------------------------------------------\n");
    
Step2: /* Projection operator. */
       SWRITE("Projection operators                  : ");
       CWRITE('(');
       for (k = 1; k <= GVNV - 2; k++) { CWRITE(LELTI(PCPROJOP,k)); CWRITE(','); }
       CWRITE(LELTI(PCPROJOP,GVNV - 1)); SWRITE(")\n");
      
Step3: /* Cell choice strategy. */
       SWRITE("Cell choice strategy level < f        : ");
       S = PCCCSF; SWRITE("(");
       while (S != NIL)
         {
         ADV(S,&S1,&S);
         switch (S1)
           {
           case TCORD: SWRITE("TC"); break;
           case NCORD: SWRITE("NC"); break;
           case HLORD: SWRITE("HL"); break;
           case LLORD: SWRITE("LL"); break;
           case GIORD: SWRITE("GI"); break;
           case LIORD: SWRITE("LI"); break;
           case SRORD: SWRITE("SR"); break;
           case SNORD: SWRITE("SN"); break;
           case GDORD: SWRITE("GD"); break;
           case LDORD: SWRITE("LD"); break;
           }
         if (S != NIL) SWRITE(",");
         }
       SWRITE(")\n");
       SWRITE("Cell choice strategy level >= f       : ");
       S = PCCCS; SWRITE("(");
       while (S != NIL)
         {
         ADV(S,&S1,&S);
         switch (S1)
           {
           case TCORD: SWRITE("TC"); break;
           case NCORD: SWRITE("NC"); break;
           case HLORD: SWRITE("HL"); break;
           case LLORD: SWRITE("LL"); break;
           case GIORD: SWRITE("GI"); break;
           case LIORD: SWRITE("LI"); break;
           case SRORD: SWRITE("SR"); break;
           case SNORD: SWRITE("SN"); break;
           case GDORD: SWRITE("GD"); break;
           case LDORD: SWRITE("LD"); break;
           }
         if (S != NIL) SWRITE(",");
         }
       SWRITE(")\n");

Step4: /* Condition for desired cells. */
       SWRITE("Solution simplifier                   : ");
       if (PCSIMPLIFY == 'b')
          SWRITE("Bottom-up\n");
       else
          SWRITE("Top-down\n");
       SWRITE("Condition for desired cells           : ");
       DESIREDWR(PCDESIRED);   
       SWRITE("\n");
       SWRITE("Use the condition                     : ");
       CWRITE(PCUSEDES); SWRITE("\n");

Step5: /* Solution formula constructrion. */
       SWRITE("Implicant generation strategy         : ");
       switch (PCIGS)
         {
         case 'l': SWRITE("Left to Right"); break;
         case 'r': SWRITE("Right to Left"); break;
         }
       SWRITE("\n");
    
Step6: /* Databases. */
       SWRITE("Use database                          : ");
       CWRITE(PCDBUSE); SWRITE("\n");
    
       SWRITE("Limit for database entry              : ");
       GWRITE(PCDBLIMIT); SWRITE("ms\n");
       
Step7: /* Specially treat trivial converions of sample points? */
       SWRITE("Specially treat trivial conversion    : ");
       CWRITE(PCTCN);
       SWRITE("\n");
   
Step8: /* Specially treat rational sample point? */
       SWRITE("Specially treat Rational sample point : ");
       CWRITE(PCRSP);
       SWRITE("\n");
   
Step9: /* Build a full CAD? */
       SWRITE("Build a full CAD                      : ");
       CWRITE(PCFULL); SWRITE("\n");

Step10: /* IPFZT test? */
       SWRITE("IPFZT test                            : ");
       CWRITE(PCIPFZT); SWRITE("\n");

Step11: /* approx precision */
       SWRITE("Approx precision                      : ");
       GWRITE(PCNUMDEC); SWRITE("\n");

Step12: /* Algorithm for resultant and discriminant computation. */
       SWRITE("Resultant and discriminant algorithm  : ");
       switch (PCRESALG) {
         case MODULAR: SWRITE("modular\n"); break;
         case SUBRES:  SWRITE("subresultant prs\n");  break; }

Step13: /* Propagate equational constraints? */
       SWRITE("Propagate equational constraints      : ");
       if (PCPROPEC == TRUE) SWRITE("True\n");
       else                  SWRITE("False\n");

Step14: /* Search for true/false cells? */
       SWRITE("Search for true cell?                 : ");
       CWRITE(PCSEARCHTRUE); SWRITE("\n");
       SWRITE("Search for false cell?                : ");
       CWRITE(PCSEARCHFALSE); SWRITE("\n");

Step15: /* SACLIB system parameters. */
       SWRITE("\n");
       SWRITE("Size of Heap (NU)                     : "); 
       GWRITE(NU); SWRITE(" words\n");
       SWRITE("Number of primes (NLPRIME)             : ");
       GWRITE(NLPRIME); SWRITE("\n");
       SWRITE("Number of small primes (NSPRIME)       : "); 
       GWRITE(NSPRIME); SWRITE("\n");
       SWRITE("Garbage collection limit ratio (RHO)  : "); 
       GWRITE(RHO); SWRITE("\n");

Return: /* Prepare for return. */
       SWRITE("---------------------------------------------\n");
       return;
}














