/*======================================================================
                      TCHILD(c; A1,A0,E1,E0)

Test the truth value of the children.

\Input
  \parm{c} is a cell.

\Output
  \parm{A1} is 1 if all children are true, 0 otherwise.
  \parm{A0} is 1 if all children are false, 0 otherwise.
  \parm{E1} is 1 if there exists a true child, 0 otherwise.
  \parm{E0} is 1 if there exists a false child, 0 otherwise.
  \parm{C0} is TRUE if children are all FALSE or all TRUE children are
            in a single connected block, FALSE if there are two TRUE
            children with a FALSE child between them, otherwise UNDET.
======================================================================*/
#include "qepcad.h"

void TCHILD(Word c, Word *A1_, Word *A0_, Word *E1_, Word *E0_)
{
       Word A0,A1,E0,E1,cb,cp,t;
       /* hide A0,A1,E0,E1; */

Step1: /* Setup. */
       cb = LELTI(c,CHILD);
       A1 = 1; A0 = 1; E1 = 0; E0 = 0;

Step2: /* Check. */
       while (cb != NIL)
         {
         ADV(cb,&cp,&cb);
         t = LELTI(cp,TRUTH);
         if (t == TRUE) { E1 = 1; A0 = 0; }
         if (t == FALSE) { E0 = 1; A1 = 0; }
         if (t == UNDET) { A0 = 0; A1 = 0; }
         }
       goto Return;

Return: /* Prepare for return. */
       *A1_ = A1;
       *A0_ = A0;
       *E1_ = E1;
       *E0_ = E0;
       return;
}

/*
Test children for conectivity

Inputs:
 c a cell
Outputs:
 s TRUE/FALSE/UNDET according to whether or not the
   children conform to all FALSE, or a single connected
   block of TRUE.

Note: This implementation is somewhat simple minded, in
that it never yields a TRUE when UNDET's are present,
and may return UNDET when FALSE could be concluded.
It's just conservative.
 */
Word TCHILD4C(Word c)
{
       Word s,nf,nt,t,cb,cp;

Step1: /* Setup. */
       cb = LELTI(c,CHILD);
       nf = 0; nt = 0;
 
Step2: /* Check. */
       while (cb != NIL)
       {
         ADV(cb,&cp,&cb);
         t = LELTI(cp,TRUTH);
	 if (t == UNDET) {
	   s = UNDET;
	   goto Return; }
	 if (t == TRUE && nt++ > 0 && nf > 0) {
	   s = FALSE;
	   goto Return; }
	 if (t == FALSE && nt > 0)
	   nf++;
       }
       s = TRUE;
       goto Return;
       
Return: /* Prepare for return. */
       return s;
}

/*
Test children for a full dimensional true cell.

Inputs:
 c : a cell
Outputs:
 s : TRUE/FALSE/UNDET according to whether there exists
     a full-dimensional TRUE cell.
 */
Word TCHILD4FDE(Word c)
{
       Word i,s,t,cb,cp,u;

Step1: /* Setup. */
       u = 0;
       cb = LELTI(c,CHILD);
 
Step2: /* Loop through full-dimensional children. */
       for(i = 1; cb != NIL; i++)
       {
	 ADV(cb,&cp,&cb);
	 if (i % 2) {
	   t = LELTI(cp,TRUTH);
	   if (t == UNDET)
	     u++;
	   else if (t == TRUE) {
	     s = TRUE;
	     goto Return; } }
       }
       if (u)
	 s = UNDET;
       else
	 s = FALSE;
       
Return: /* Prepare for return. */
       return s;
}


/*
Test children for all full dimensional true cells.

Inputs:
 c : a cell
Outputs:
 s : TRUE/FALSE/UNDET according to whether all 
     full-dimensional are TRUE
 */
Word TCHILD4FDA(Word c)
{
       Word i,s,t,cb,cp,u;

Step1: /* Setup. */
       u = 0;
       cb = LELTI(c,CHILD);
 
Step2: /* Loop through full-dimensional children. */
       for(i = 1; cb != NIL; i++)
       {
	 ADV(cb,&cp,&cb);
	 if (i % 2) {
	   t = LELTI(cp,TRUTH);
	   if (t == UNDET)
	     u++;
	   else if (t == FALSE) {
	     s = FALSE;
	     goto Return; } }
       }
       if (u)
	 s = UNDET;
       else
	 s = TRUE;
       
Return: /* Prepare for return. */
       return s;
}

/*
Test children for exists exactly k

Inputs:
 c : a cell
Outputs:
 s : TRUE/FALSE/UNDET according to whether exactly
     k cells are TRUE, all of which are sections
 */
Word TCHILD4EXk(Word c, Word k)
{
  Word i,s,t,cb,cp,u0,u1,x0,x1;

Step1: /* Setup. */
       u0 = 0; /* count of UNDET section cells */
       u1 = 0; /* count of UNDET sector cells */
       x0 = 0; /* count of TRUE section cells */
       x1 = 0; /* count of TRUE sector cells */
       cb = LELTI(c,CHILD);
 
Step2: /* Loop through full-dimensional children. */
       for(i = 1; cb != NIL; i++)
       {
	 ADV(cb,&cp,&cb);
	 t = LELTI(cp,TRUTH);

	 if (t == UNDET)
	   if (i % 2 == 1)
	     u1++;
	   else
	     u0++;

	 if (t == TRUE)
	   if (i % 2 == 1)
	     x1++;
	   else
	     x0++;
       }

Return: /* Prepare for return. */
       if (x1 == 0 && u1 == 0 && u0 == 0 && x0 == k)
	 s = TRUE;
       else if (x1 > 0 || x0 > k || (x0 + u0 < k))
	 s = FALSE;
       else
	 s = UNDET;
       return s;
}
