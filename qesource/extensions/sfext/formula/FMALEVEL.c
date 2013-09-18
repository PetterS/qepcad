/*===========================================================================
ForMulA level

Input 
F : an FMA formula

Output
L : the level of F, defined as the highest level occuring in the formula.

===========================================================================*/
#include "espcad.h"

Word FMALEVEL(Word F)
{
       Word f,Q,L;

Step1: /* Determine the level of the formula. */
       f = FIRST(F);
       switch (f)
	 {
	   /* Constants. */
	 case TRUE: 
	 case FALSE:
	   L = 0;
	   break;
	   
	   /* AND and OR. */
	 case ANDOP: 
	 case OROP:
	   L = 0;
	   for(Q = RED(F); Q != NIL; Q = RED(Q))
	     L = MAX(L,FMALEVEL(FIRST(Q)));
	   break;

	   /* Not */
	 case NOTOP:
	   L = FMALEVEL(SECOND(F));
	   break;

	   /* Binary ops. */
	 case RIGHTOP:
	 case LEFTOP:
	 case EQUIOP:
	   L = MAX(FMALEVEL(SECOND(F)),FMALEVEL(THIRD(F)));
	   break;

	   /* Atomic formulas. */
	 default:
	   if (ISLIST(f))
	     L = FIRST(f);
	   else {
	     L = -1;
	     SWRITE("Error in FMALEVEL! Unknown atom type!\n"); }
	   break;
	 }

Return: /* Return. */
       return L;
}
