/*======================================================================
Solution Formula Extension Interface

This function simply reads in a single non-whitespace character
from standard in, and decides what solution formula construction
method to call and, of course, calls it.

======================================================================*/
#include "qepcad.h"

void QepcadCls::SOLEXTINT()
{
  Word t,F_e,F_n,F_s, T, f, c;

Step1: /* Initialization */
  T = ACLOCK();
  f = 1;
  c = CREADB();

Step2: /* Send off to the proper solution formula constructor */
  switch(c) {

  case 'T': /* Tarski Formula */
    SFC3(GVPC,GVPF,GVPJ,GVNFV,
	 CCONC(LIST6(0,0,0,1,0,1),LIST10(0,0,2,0,3,2,4,1,5,-1)));
    break;

  case 'E': /* Extended Language Formula */
    SFC3(GVPC,GVPF,GVPJ,GVNFV,CCONC(LIST10(1,0,0,1,0,3,2,4,1,5),LIST1(-1)));
    break;

  case 'G': /* "Geometry-based" Formula */
    SFC3(GVPC,GVPF,GVPJ,GVNFV,
	 CCONC(LIST4(1,0,2,1),LIST4(3,2,0,-4))); 
    break;

  case 'I': /* Interactive SF-Construction Session */
    SFC4(GVPC,GVPF,GVPJ,GVNFV,NIL); 
    break;

  case 'F': /* Full Dimensional SF-Construction Session */
    SFCFULLD(GVPC,GVPF,GVPJ,GVNFV); 
    break;

  default: /* Bad option. */
    SWRITE("Parameter not understood!\n"); 
    f = 0;
    break; }

Step3: /* Timing info */
  if (f) {
    T = ACLOCK() - T;
    TMSFCONST = COMP(T,TMSFCONST);
  }
  
  return;
}
