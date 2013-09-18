/*
Sample point rational last coordinate.
*/
#include "oldadj.h"

Word SPRLC(Word c)
{
       Word s,M,I,b,pr,r;

Step1: /* Get sample point. */
       s = LELTI(c,SAMPLE);

Step2: /* Primitive sample point. */
       FIRST3(s,&M,&I,&b);
       pr = LAST(b);
       if (pr == 0)
	 r = 0;
       else
	 r = FIRST(pr);

Return: /* Prepare to return. */
       return r;
}
