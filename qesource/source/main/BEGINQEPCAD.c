/*======================================================================
                         BEGINQEPCAD()

Does all the system setup to get qepcad ready.  Assumes saclib has
already been initialized!
======================================================================*/
#include <fstream>
#include <sstream>
#include "qepcad.h"
#include "db/CAServer.h"
#include "db/OriginalPolicy.h"
#include "db/SingularPolicy.h"
#include "db/SingSacPolicy.h"
#include "db/convenientstreams.h"
#include "db/CAPolicy.h"
#include <ctype.h>
#include <sys/wait.h>

void QEPCAD_ProcessRC(int argc, char **argv);
void QEPCAD_Usage(int cols);

/*
  This is a somewhat graceful way for me to work on experimental
  features.
 */
int experimentalExtensionFlag = 0; 

ServerBase GVSB;
CAPolicy *GVCAP = 0;
QEPCADContext* GVContext = 0;

void BEGINQEPCAD(int &argc, char**& argv)
{
  /* Process QEPCAD's command line arguments. 
     NOTE: The -exp version is there to give me a nice way to work
     on experimental features in the same branch as I'm releasing!
   */

  /* With an invalid command-line argument (or -h) just print usage 
     and exit*/
  int usageAndExit = -1; /* -1 means don't print usage and exit! */

  /* #cols for usage message output is 80 or terminal width if 
     stdout attached to a terminal*/
  int cols = 80;         /* number of columns for help output */
  int isStdoutTerm = system("test -t 1");
  isStdoutTerm = WEXITSTATUS(isStdoutTerm);
  if (isStdoutTerm == 0 && isatty(0))
  {
    int tmp = system("bash -c 'exit $(stty size | cut -d\" \" -f2)'");
    tmp = WEXITSTATUS(tmp);
    if (10 <= tmp <= 512)
      cols = tmp;
  }

  /* LOOP OVER ARGUMENTS! */
  for(int i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i],"-exp") == 0) { experimentalExtensionFlag = 1; }
    else if (strcmp(argv[i],"-noecho") == 0) { NOECHOSWITCHSET = TRUE; }
    else if (strcmp(argv[i],"-h") == 0)
    {
      usageAndExit = 0;
    }
    else
    {
      cerr << "Unknown option '" << argv[i] << "'!" << endl;
      usageAndExit = 1;
    }
  }
  if (usageAndExit >= 0) { QEPCAD_Usage(cols); exit(usageAndExit); }

  /* Set things up so Singular can be used as a CAServer */
  GVContext = new QEPCADContext;
  QEPCAD_ProcessRC(argc,argv);

  QEGLOBALS();
  SETUPSYS();
  
  /* Line buffer output */
  setlinebuf(stdout); 
  
  /* Initialize the qepcad system globals. */
  INITSYS();
  
  /* Launch CA Servers and set up CA Policy */
  if (GVContext->SingularPath == "")
    GVCAP = new OriginalPolicy;
  else
  {
    pair<string,CAServer*> tp(string("Singular"),new SingularServer(GVContext->SingularPath));
    GVSB.insert(tp);
    GVCAP = new SingSacPolicy;
  }

}

void QEPCAD_ProcessRC(int argc, char **argv)
{
  char *qepath = getenv("qe");
  if (qepath == NULL) { FAIL("QEPCAD_ProcessRC","Environment variable qe not defined!"); }
  string rcFileName = qepath + string("/default.qepcadrc");
  ifstream rcin(rcFileName.c_str());
  if (!rcin) { return; }
  string name, tmp;
  while(rcin)
  {
    slwcistream sin(rcin,slwcistream::skipleadingws);
    if (!(sin >> name)) { continue; }
    if (name == "SINGULAR")
    {      
      if (!(sin >> tmp)) { cerr << "Error reading SINGULAR path in " << rcFileName << "!" << endl; }
      else { GVContext->SingularPath = tmp; }
    }
  }
}

void QEPCAD_Usage(int cols)
{
      ostringstream out;
      out << "usage: qepcad [-h] [-noecho] [+N<numcells>]\n\n";
      out << "QEPCAD B v" << QEPCADBVersion();
      out << "\
 is a program for studying Cylindrical Algebraic Decomposition (CAD). \
It constructs CADs from an input formula and variable order, and provides \
many commands for getting info out of the CAD, including construction of \
simple equivalent Tarski formulas.\n\
\n\
Options\n\
-h      : Help information\n\
-noecho : Turns off echoing of input\n\
\n\
Saclib options\n\
+N<numcells> : Sets garbage collected space to <numcells>.  Default is 2000000.\n\
";
      int i = 0, x = 0;
      int N = int(out.str().length());
      while(i < N)
      {
	char c = out.str()[i];
	if (isspace(c)) 
	{ 
	  cout << c; 
	  ++i; 
	  ++x;
	  if (c == '\n') { x = 0; }
	  else if (x >= cols) { x = 0; cout << endl; } 
	}
	else
	{
	  int j = i + 1; while(j < N && !isspace(out.str()[j])) ++j;
	  if (x + j - i > cols) { cout << endl; x = 0; }	  
	  for(int k = i; k < j; ++k, ++x) cout << out.str()[k];
	  if (x >= cols) { x = 0; cout << endl; }
	  i = j;
	}
      }
}
