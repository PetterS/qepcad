/*======================================================================
                      SAMPLEWR(c)

Sample point write.

\Input
  \parm{c} is a cell whose sample point is to be written out
           to the output stream.
======================================================================*/
#include "qepcad.h"

void SAMPLEWR(Word k, Word s, Word PCNUMDEC)
{
       Word I,Ip,M,Mp,b,bp,F,j,Ms,Is;
       Word M1;

Step2: /* Extended representation. */
       if (ISPRIMIT(s)) goto Step3;
       FIRST5(s,&M,&I,&Mp,&Ip,&bp);
       SWRITE("The sample point is in an EXTENDED representation.\n\n");

       SWRITE("alpha = "); IUPRWR(LFS("x"),Mp,Ip); SWRITE("\n");
       SWRITE("      = "); ANDWRITE(Mp,Ip,PCNUMDEC); SWRITE("\n\n"); 

       AFLWR(Mp,Ip,LFS("Coordinate "),LFS("alpha"),bp,PCNUMDEC);

       SWRITE("Coordinate "); GWRITE(k); SWRITE(" = ");
       AFUPRWR(LFS("alpha"),LFS("x"),M,I);  SWRITE("\n");
       F = AFPNIP(Mp,M);  
       M = AFPICR(1,M);
       IPSRP(2,M,&M1,&M);
       AMUPMPR(Mp,Ip,M,I,F,&Is,&j);
       Ms = LELTI(F,j); 
       Is = IPSIFI(Ms,Is);  
       SWRITE("             = "); 
       IUPRWR(LFS("x"),Ms,Is);  SWRITE("\n");
       SWRITE("             = "); 
       ANDWRITE(Ms,Is,PCNUMDEC); SWRITE("\n");
       goto Return;

Step3: /* Primitive representation. */
       FIRST3(s,&M,&I,&b);
       SWRITE("The sample point is in a PRIMITIVE representation.\n\n");

       SWRITE("alpha = "); IUPRWR(LFS("x"),M,I); SWRITE("\n");
       SWRITE("      = "); ANDWRITE(M,I,PCNUMDEC); SWRITE("\n\n"); 

       AFLWR(M,I,LFS("Coordinate "),LFS("alpha"),b,PCNUMDEC);  SWRITE("\n");

Return: /* Prepare for return. */
       return;
}



void QepcadCls::SAMPLEWR(Word c)
{
       Word I,Ip,M,Mp,b,bp,k,s,F,j,Ms,Is;
       Word M1;

       s = LELTI(c,SAMPLE);
       k = LELTI(c,LEVEL);
       ::SAMPLEWR(k,s,PCNUMDEC);
}


