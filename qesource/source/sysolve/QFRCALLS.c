#include "qepcad.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "db/unnamedpipe.h"
#include "db/CAServer.h"
#include <sstream>
#include <signal.h>

bool qfrFalseCheck(string qfrInputString);

/*
qfrCheckNonVanishing
Inputs:
  r - 
  P - an r-variate saclib polynomial
  A - the assumptions formula
  F - the quantifier-free input formula
  V - the variable list (length at least r)

Outputs:
  qfc: true if tarski/qfr determines that P is never zero
       given A and F.  false otherwise.
 */
bool qfrCheckNonVanishing(BDigit r, Word P, Word A, Word F, Word V)
{
  if (PCVERBOSE) { SWRITE("qfr non-vanishing test: "); IPDWRITE(r,P,V); SWRITE("\n");  }

	 // Conjoin quantifier-free part of the input with assumptions and change level to r.
	 Word tF = A == NIL  ? F : LIST3(ANDOP,A,F);
	 Word tFred = CHANGEASSUMPTIONSLEVEL(tF,r,1);

	 // Prepare input to call qfr through the tarski program
	 ostringstream oss;
	 PushOutputContext(oss);
	 /* SWRITE("[ "); */
	 /* if (r > 0) { */
	 /*   SWRITE("ex "); */
	 /*   Word VL = V; */
	 /*   for(int i = 0 ; i < r; ++i) */
	 /*   { */
	 /*     if (i != 0) SWRITE(","); */
	 /*     VWRITE(FIRST(VL)); */
	 /*     VL = RED(VL); */
	 /*   } */
	 /* } */
	 SWRITE("[ "); IPDWRITE(r,P,V); SWRITE(" = 0 /\\ "); 
	 SWRITE("[ "); QFFWR(V,tFred); SWRITE(" ]]");
	 PopOutputContext();
	 string qfrInputString = "set F " + oss.str() 
	   + " set G $exclose F set H $qfr G print H quit";

	 // Check if tarski/qfr can deduce that this formula is false!
	 int qfc = qfrFalseCheck(qfrInputString);
	 if (PCVERBOSE) { cout << "QFR says: " << qfc << endl; }
	 return qfc;
}

/*
qfrCheckNonNullified
Inputs:
  r - 
  P - an r-variate saclib polynomial
  A - the assumptions formula
  F - the quantifier-free input formula
  V - the variable list (length at least r)

Outputs:
  qfc: true if tarski/qfr determines that P is never nullified
       given A and F.  false otherwise.
 */
bool qfrCheckNonNullified(BDigit r, Word P, Word A, Word F, Word V)
{
  if (PCVERBOSE) { SWRITE("non-nullified test: "); IPDWRITE(r,P,V); SWRITE("\n"); }

  // Get the system, and return if the system is trivially unsat or sat
  Word S = COEFSYS(r,P);
  if (S == 1) 
    return true;
  if (S == 0)
    return false;

  // Produce the formula version of the system
  Word Fp = NIL;
  for(Word Sp = S; Sp != NIL; Sp = RED(Sp))    
    Fp = COMP(SYSTOUNNORMFORMULA(r-1,FIRST(Sp)),Fp);
  Fp = COMP(OROP,Fp);
  Word tF = A == NIL  ? LIST3(ANDOP, Fp, F) : LIST4(ANDOP,Fp,A,F);
  Word tFred = CHANGEASSUMPTIONSLEVEL(tF,r-1,1);

  if (PCVERBOSE) {
    SWRITE("System is: ");
    QFFWR(V,tFred);
    SWRITE("\n"); }

  // Prepare input to call qfr through the tarski program
  ostringstream oss;
  PushOutputContext(oss);
  SWRITE("[ "); QFFWR(V,tFred); SWRITE(" ]");
  PopOutputContext();
  string qfrInputString = "set F " + oss.str() 
    + " set G $exclose F set H $qfr G print H quit";

  int qfc = qfrFalseCheck(qfrInputString);
  if (PCVERBOSE) { cout << "QFR says: " << qfc << endl; }
  return qfc;
}

bool qfrFalseCheck(string qfrInputString)
{
  UnnamedPipe intoQfr, outofQfr;
  if (PCVERBOSE) { cerr << "forking (" + qfrInputString + " )..." << endl; }
  int childpid = fork();
  if (childpid == -1) { perror("Failed to fork!"); exit(1); }

  // Child process's code
  if (childpid == 0) {
    intoQfr.closeOut();
    intoQfr.setStdinToPipe();
    outofQfr.closeIn();
    outofQfr.setStdoutToPipe();
    execlp("/home/wcbrown/research/tarski/interpreter/formula/tarski",
	   "/home/wcbrown/research/tarski/interpreter/formula/tarski",
	   NULL);
    perror("qfr startup failed!\n");
    outofQfr.closeOut();
    exit(0);
  }

  intoQfr.closeIn();
  outofQfr.closeOut();
  intoQfr.out() << qfrInputString;
  intoQfr.closeOut();
  string s;
  outofQfr.in() >> s;
  outofQfr.closeIn();
  if (s == "false")
    return true;
  else
    return false;
}

