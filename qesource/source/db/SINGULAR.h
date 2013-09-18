/***************************************************************
 * This file SINGULAR.h and SINGULAR.c define a CAServer based
 * on the Singular system.
 ***************************************************************/
#ifndef _SINGULAR_
#define _SINGULAR_

#include "qepcad.h"
#include "db/unnamedpipe.h"
#include "db/CAServer.h"
#include <sstream>
#include <signal.h>

class SingularServer : public CAServer
{
public:
  UnnamedPipe intoSingular, outofSingular;
  pid_t childpid;
  
  SingularServer(string SingluarBase); // give path to Singular
  ~SingularServer();
  void kill() { ::kill(childpid,SIGKILL); }
  
  void IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_);
  Word IPRES(Word r, Word A, Word B);
  Word IPDSCR(Word r, Word A);
  Word IPFACTGB(Word r, Word I, Word N);
  Word CONSTORDTEST(Word r, Word A, Word L);

  const string name() { return "Singular"; }
  int serverTime();
  void reportStats(ostream &out);
};


#endif
