/*======================================================================
                      PARENTWR(P)

Parentage write.

\Input
  \parm{H} is a list of parentages.
======================================================================*/
#include "qepcad.h"

void PARENTWR(Word P)
{
       Word P1,T,d,r,m,A,r1,A1,r2,A2;

Step1: /* Input polynomial. */
       if (P == NIL)
         {
         SWRITE("input");
         goto Return;
         }

Step2: /* Intemediate polynomials. */
       while (P != NIL)
         {
         ADV(P,&P1,&P);
         T = FIRST(P1);
         switch(T)
           {
           case PO_TCO:
             A = LELTI(P1,2);
             SWRITE("tail(");
             PLABELWR(A);
             SWRITE(")");
             break;

           case PO_LCO:
             r = LELTI(P1,2);
             A = LELTI(P1,3);
             SWRITE("ldcf(");
             if (r > 1)
                {
                SWRITE("red");
                GWRITE(r);
                SWRITE("(");
                PLABELWR(A);
                SWRITE(")");
                }
             if (r == 1)
                {
                SWRITE("red");
                SWRITE("(");
                PLABELWR(A);
                SWRITE(")");
                }
             if (r == 0)
                PLABELWR(A);
             SWRITE(")");
             break;

           case PO_FAC:
             m = LELTI(P1,2);
             A = LELTI(P1,3);
             SWRITE("fac");
             if (m > 1)
               GWRITE(m);
             SWRITE("(");
             PLABELWR(A);
             SWRITE(")");
/*---------- New Stuff. -------------*/
	     SWRITE(" = fac");
             if (m > 1)
               GWRITE(m);
             SWRITE("(");
	     PARENTWR(LELTI(A,PO_PARENT));
	     SWRITE(")");

/*-----------------------------------*/
             break;

           case PO_DIS:
             d = LELTI(P1,2);
             r = LELTI(P1,3);
             A = LELTI(P1,4);
             SWRITE("dis");
             if (d > 0)
               GWRITE(d);
             SWRITE("(");
             if (r > 1)
                {
                SWRITE("red");
                GWRITE(r);
                SWRITE("(");
                PLABELWR(A);
                SWRITE(")");
                }
             if (r == 1)
                {
                SWRITE("red");
                SWRITE("(");
                PLABELWR(A);
                SWRITE(")");
                }
             if (r == 0)
                PLABELWR(A);             
             SWRITE(")");
             break;

           case PO_RES: 
             d  = LELTI(P1,2);
             r1 = LELTI(P1,3);
             A1 = LELTI(P1,4);
             r2 = LELTI(P1,5);
             A2 = LELTI(P1,6);
             SWRITE("res");
             if (d > 0)
               GWRITE(d);
             SWRITE("(");
             if (r1 > 1)
                {
                SWRITE("red");
                GWRITE(r1);
                SWRITE("(");
                PLABELWR(A1);
                SWRITE(")");
                }
             if (r1 == 1)
                {
                SWRITE("red");
                SWRITE("(");
                PLABELWR(A1);
                SWRITE(")");
                }
             if (r1 == 0)
                PLABELWR(A1);                           
             SWRITE("|");
             if (r2 > 1)
                {
                SWRITE("red");
                GWRITE(r2);
                SWRITE("(");
                PLABELWR(A2);
                SWRITE(")");
                }
             if (r2 == 1)
                {
                SWRITE("red");
                SWRITE("(");
                PLABELWR(A2);
                SWRITE(")");
                }
             if (r2 == 0)
                PLABELWR(A2);                           
             SWRITE(")");
             break;

           case PO_DER:
             d = LELTI(P1,2);
             A = LELTI(P1,3);
             SWRITE("der");
             if (d > 0)
               GWRITE(d);
             SWRITE("(");
	     PLABELWR(A);             
             SWRITE(")");
             break;

           case PT_NUL:
             A = LELTI(P1,2);
             SWRITE("nulpt");
             SWRITE("(");
	     PLABELWR(A);             
             SWRITE(")");
             break;

           case PT_PRJ:
              A = LELTI(P1,2);
             SWRITE("prjpt");
             SWRITE("(");
	     PLABELWR(A);             
             SWRITE(")");
             break;

           case PT_DEL:
             A = LELTI(P1,2);
             SWRITE("delpt");
             SWRITE("(");
	     PLABELWR(A);             
             SWRITE(")");
             break;

           default:
             FAIL("PARENTWR","Some bug in the program!!!");
           }
         if (P != NIL) {
/*---------- New Stuff. -------------*/

	   SWRITE("\n");
	   TAB(7);
	   SWRITE("= "); }


/*-----------------------------------*/
         }

Return: /* Prepare for return. */
       return;
}

