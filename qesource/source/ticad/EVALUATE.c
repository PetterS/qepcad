/*======================================================================
                      EVALUATE(c,k,F,A)

Evaluate the truth values, trial.

\Input
  \parm(c} is a cell.
  \parm{k} is the level of the cell~$c$.
  \parm{F} is the normalized quantifier-free part of the input formula.
  \parm{A} is the list~$(A_1,\ldots,A_r)$,
            where $A_i = (A_{i,1},\ldots,A_{i,n_i})$ is the list
            of all the distinct $i$--level polynomials in~$F$.
                
\Output
  The truth values of some cells in the stack over
  the cell~$c$ are  determined, if possible.
======================================================================*/
#include "qepcad.h"

void QepcadCls::EVALUATE(Word c, Word k, Word F, Word A)
{
       Word cb,cs,t,tt,ks, Q, q, flag;

Step1: /* Unhelpful case. */
       if (LELTI(A,k + 1) == NIL) goto Return;

Step2: /* Evaluate the truth of the children of c */
       cb = LELTI(c,CHILD);
       while (cb != NIL)
         {
         ADV(cb,&cs,&cb);
	 
	 /* Check Assumptions if relevent*/
	 t = UNDET;
	 if (k + 1 <= GVNFV && GVNA != NIL) {
	   tt = QFFTEV(GVNA,cs,k + 1);
	   if (tt == FALSE)
	     t = NA;
	   else if (tt == TRUE)
	     t = UNDET;
	   else if (tt == UNDET) // If assumptions are undetermined, then one MUST lift
	     continue;           // further, regardless of the trial eval of the formula.
	 }                       // Because a T/F value for the formula can't be interpreted
                                 // Unless you know whether the assumptions hold!
	 
	 /* Check QFF-input formula */
	 if (t == UNDET)
	   t = QFFTEV(F,cs,k + 1);


	 /* Deal with the "Exist exactly k" operator!
	  * If the quantifier-free part of the input formula
	  * is identically true in some ks-level cell cs, then
	  * at any higher level it's identically true for
	  * every point in the cylinder over cs.  Thus, if there's
	  * an "Exists exactly k" quantifier at a level higher than
	  * ks, the quantified formula is false at cs!  (i.e. even
	  * though the unquantified formula is true in cs! */
	 if (t == TRUE) 
	 {
	   ks = k + 1; /* ks is the level of cs. */
	   Q = REDI(GVQ, ks <= GVNFV ? 0 : ks - GVNFV);
	   for(flag = FALSE; Q != NIL && !flag; Q = RED(Q))
	   {
	     q = FIRST(Q);
	     flag = (ISLIST(q) && FIRST(q) == EXISTk);
	   }
	   if (flag)
	     t = FALSE;
	 }


	 /* Apply truth value! */
         if (t != UNDET)
         { 
           SLELTI(cs,TRUTH,t); 
           SLELTI(cs,HOWTV,BYTEV); 

	   /* Remember witness cells for SAT problems. */
                               if (GVWL == -1) // Init GVWL the 1st time here
			       { 
				 Word T = GVQ; 
				 while(T != NIL && FIRST(T) == EXIST) 
				   T = RED(T); 
				 GVWL = (T == NIL && GVNFV == 0) ? NIL : 0; 
			       }
			       if(GVWL != 0 && t == TRUE) 
			       { 
				 GVWL = COMP(cs,GVWL); 
			       }

	   /*Int*/ if (PCSEARCHTRUE == 'y' && t == TRUE)
                               /*Int*/   { 
                               /*Int*/   SWRITE("****** True cell ******\n");
                               /*Int*/   CELLWR(cs);
                               /*Int*/   PCSEARCHOK = 'y';
                               /*Int*/   }
                               /*Int*/ if (PCSEARCHFALSE == 'y' && t == FALSE)
                               /*Int*/   { 
                               /*Int*/   SWRITE("****** False cell *****\n ");
                               /*Int*/   CELLWR(cs);
                               /*Int*/   PCSEARCHOK = 'y';
                               /*Int*/   }
           }
         }

Return: /* Prepare for return. */
       return;
}

