/*======================================================================
                         SIMPLE_CAD_INFO
n : the level
======================================================================*/
#include "qepcad.h"

void SIMPLE_CAD_INFO(Word D, Word P, Word n, Word flag)
{
      Word Ps,Cs,t,Db;

Step1: /* Check for the trivial cases. */
      switch( DOPFSUFF(P,LIST1(D)) ) {
      case (TRUE) : SWRITE("\n\nInput is identically TRUE.\n\n");
                    goto Return;
      case (FALSE): SWRITE("\n\nInput is identically FALSE.\n\n");
                    goto Return; 
      default     : break; }

Step2: /* Construct the simple CAD. */
      t = ACLOCK();
      if (flag & 1)
	CCADCONmod(n,P,D,&Ps,&Cs);
      else
	CCADCON(n,P,D,&Ps,&Cs);
      t = ACLOCK() - t;
      if (flag & 1)
	SWRITE(" Full-dimension-cell-based Simple CAD construction required: ");
      else
	SWRITE(" Simple CAD construction required: ");	
      IWRITE(t);
      SWRITE(" milliseconds.\n\n");

Step3: /* Display stats. */
      PCADSTATS(Cs,Ps,n);
      PPROJFWRITE(Ps);
      SWRITE("\n\n");

Return: /* Prepare to return. */
      return;
}
