#include "SINGULAR.h"
#include <iostream>
#include <string>
using namespace std;


SingularServer::SingularServer(string SingularBase)
{
  string SingularCall = SingularBase + "/Singular";
  
  // Fork
  childpid = fork();
  if (childpid == -1) { perror("Failed to fork!"); exit(1); }
  // Child process's code
  if (childpid == 0) {
    intoSingular.setStdinToPipe();
    outofSingular.setStdoutToPipe();

    // Begin: Just for debug!!
    //system("/home/wcbrown/bin/Singular -q --no-warn --min-time=0.001 --ticks-per-sec=1000 | tee /tmp/SingOutLog");
    //exit(0);
    // End:   Just for debug!!


    execlp(SingularCall.c_str(),
	   SingularCall.c_str(),
	   "-q",
	   "--no-warn",
	   "--min-time=0.001",
	   "--ticks-per-sec=1000",
	   NULL);
      perror("SingularServer Constructor: Singular startup failed! (Set SINGULAR environment variable)");
      outofSingular.closeOut();
      exit(0);
  }
}

SingularServer::~SingularServer()
{
  intoSingular.out() << endl << "quit;" << endl << flush;
}

int SingularServer::serverTime()
  {
    intoSingular.out() << "timer;" << endl;
    int t;
    outofSingular.in() >> t;
    return t;
  }

void SingularServer::reportStats(ostream &out)
{
  out << "Time in Singular: " 
      << serverTime()
      << " ms." << endl;    
}


char peekNonWS(istream &in) 
{ 
  char c; while((c = in.peek()) && c == ' ' || c == '\t' || c == '\n') in.get(); return c; 
}


Word readSingularPoly(Word r, Word V, istream &in)
{
  Word A, t;
  string s;
  in >> s;
  for(int i = 0; i < s.length(); ++i)
    if (s[i] == '*') s[i] = ' ';
  s += ".\n";
  istringstream si(s);
  PushInputContext(si);
  IPEXPREADR(r,V,&A,&t);
  PopInputContext();

  if (t == 0) 
  { 
    cerr << "QEPCADB could not read Singular's output!" << endl
         << s << endl;
    exit(1);
  }
  return A;
}

Word CreateVariableList(Word r)
{
  Word V = NIL;
  char s[] = {'a','\0'};
  for(int i = 'a' + r - 1; i >= 'a'; --i)
  {
    s[0] = i;
    V = COMP(LFS(s),V);
  }
  return V;
}

string WritePolyForSingular(Word r, Word P, Word V)
{
  //write poly to string
  string out;
  {
    ostringstream sout;
    PushOutputContext(sout);
    IPDWRITE(r,P,V);
    PopOutputContext();
    out = sout.str();
  }
  // Put in * symbols
  for(int i = 1; i < out.length() - 1; ++i)
    if (out[i] == ' ' && out[i+1] != '+' && out[i+1] != '-'
	&& out[i-1] != '+' && out[i-1] != '-'
	)
      out[i] = '*';

  return out;
}

void DefineRing(ostream &out, const string &name, Word r, const string &order="lp")
{
  out << "ring " << name << " = 0, (";
  for(int i = r-1; i > 0; --i)
    out << char('a' + i) << ',';
  out << "a), " << order << ";" << endl;
  out << "short = 0;" << endl;
}

Word SingularServer::IPRES(Word r, Word A, Word B)
{
  DefineRing(intoSingular.out(),"myring",r);
  Word V = CreateVariableList(r);
  string s_A =  WritePolyForSingular(r,A,V);
  intoSingular.out() << "poly A = " << s_A << ";" << endl;
  string s_B =  WritePolyForSingular(r,B,V);
  intoSingular.out() << "poly B = " << s_B << ";" << endl;
  intoSingular.out() << "resultant(A,B," << char('a' + r - 1) << ");" << endl;
  
  // Read & parse Singular output
  Word p = readSingularPoly(r-1,V,outofSingular.in());

  return p;
}

Word SingularServer::IPDSCR(Word r, Word A)
{
       Word Ap,B,a,n,rp;

Step1: /* Compute. */
       Ap = IPDMV(r,A);
       B = IPRES(r,A,Ap);
       a = PLDCF(A);
       rp = r - 1;
       B = IPEQ(rp,B,a);
       n = PDEG(A);
       if (REM(n,4) >= 2)
          B = IPNEG(rp,B);

Return: /* Prepare for return. */
       return(B);
}

void SingularServer::IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_)
{
  int T1 = serverTime();

  Word V = CreateVariableList(r);
  string out =  WritePolyForSingular(r,P,V);

  // Send Singular commands
  DefineRing(intoSingular.out(),"myring",r);
  intoSingular.out() << "poly F = " << out << ";" << endl;
  intoSingular.out() << "factorize(F);" << endl;
  
  // Read & parse Singular output
  istream &in = outofSingular.in();
  string s1, s2;
  in >> s1;
  Word L = NIL;
  while(true)
  {
    char c;
    while((c = in.get()) && c != '=' && c != ':');
    if (c == ':') break;
    Word p = readSingularPoly(r,V,in);
    L = COMP(p,L);
  }
  Word M = NIL;
  int m;
  char c;
  in >> m;
  M = COMP(m,M);
  for(int i = 1; i < LENGTH(L); ++i) { in >> c >> m;  M = COMP(m,M); }
  while(in.get() != '\n');

  // Pair factors and multiplicities (and make sure factors are positive)
  Word FML = NIL;
  Word sn = 1;
  for(;RED(L) != NIL; L = RED(L), M = RED(M))
  {
    Word pL = FIRST(L);
    if (ISIGNF(PLBCF(r,pL)) == -1)
    {
      if (ODD(FIRST(M)))
	sn *= -1;
      pL = IPNEG(r,pL);
    }
    FML = COMP(LIST2(FIRST(M),pL),FML);
  }
  // Sign and content
  Word lcf = PLBCF(r,FIRST(L));
  Word ct = IABSF(lcf);
  sn *= ISIGNF(lcf);

  // Figure out how long that took!
  int T2 = serverTime();

  // RETURN
  *s_ = sn;
  *c_ = ct;
  *L_ = FML;
  return;
}

Word SingularServer::IPFACTGB(Word r, Word I, Word N)
{
  // WRITE SINGULAR INPUT
  DefineRing(intoSingular.out(),"myring",r);
  Word V = CreateVariableList(r);
  intoSingular.out() << "ideal I = ";
  for(Word L = I; L != NIL; L = RED(L))
  {
    intoSingular.out() << WritePolyForSingular(r,FIRST(L),V);
    if (RED(L) != NIL)
      intoSingular.out() << ", ";
    else
      intoSingular.out() << ";" << endl;
  }
  intoSingular.out() << "option(\"redSB\");" << endl;
  intoSingular.out() << "facstd(I);" << endl;
  intoSingular.out() << "\"[end]:\";" << endl;

  // READ SINGULAR OUTPUT
  Word F = NIL;
  string marker; 
  while(outofSingular.in() >> marker && marker != "[end]:")
  {
    Word GBi = NIL;
    while(peekNonWS(outofSingular.in()) == '_')
    {
      while(outofSingular.in().get() != '=');
      Word p = readSingularPoly(r,V,outofSingular.in());
      GBi = COMP(p,GBi);      
    }
    F = COMP(CINV(GBi),F);
  }
  return CINV(F);
}

Word TDEG(Word r, Word A)
{
  if (r == 0) return 0;
  Word M = 0;
  for(Word L = A; L != NIL; L = RED2(L))
    M = IMAX(M,FIRST(L) + TDEG(r-1,SECOND(L)));
  return M;
}

Word SingularServer::CONSTORDTEST(Word r, Word A, Word L)
{
  // SINGULAR INPUT: Define Ideal A + L & compute groebner basis G
  DefineRing(intoSingular.out(),"myring",r,"dp");
  Word V = CreateVariableList(r);
  intoSingular.out() << "ideal I = ";
  for(Word Lp = L; Lp != NIL; Lp = RED(Lp))
    intoSingular.out() << WritePolyForSingular(r,FIRST(Lp),V) << ", ";
  intoSingular.out() 
    << WritePolyForSingular(r,A,V) << ";" << endl
    << "ideal G = std(I);" << endl
    << "G;" << endl
    << "\"[end]:\";" << endl;

  // SINGULAR OUTPUT: Read G
  Word G = NIL;
  while(peekNonWS(outofSingular.in()) == 'G')
  {
    while(outofSingular.in().get() != '=');
    Word p = readSingularPoly(r,V,outofSingular.in());
    G = COMP(p,G);      
  }
  { string em; while(outofSingular.in() >> em && em != "[end]:"); }
  G = CINV(G);

  // SINGULAR INPUT: Find lowest order partials that are not all reduced to 0 by G
  Word M = NIL, k;
  for(k = 1; M == NIL; k++)
  {
    for(Word P = IPALLPARTIALS(r,A,k,1); P != NIL; P = RED(P))
    {
      intoSingular.out() 
	<< "reduce(" << WritePolyForSingular(r,FIRST(P),V) << ",G);" << endl;
      Word p = readSingularPoly(r,V,outofSingular.in());
      if (p != 0)
	M = COMP(p,M);
    }    
  }
  
  // SINGULAR INPUT: Compute groebner basis for G + all partials
  intoSingular.out() << "ideal J = ";
  for(Word Lp = G; Lp != NIL; Lp = RED(Lp))
    intoSingular.out() << WritePolyForSingular(r,FIRST(Lp),V) << ", ";
  for(Word Lp = M; Lp != NIL; Lp = RED(Lp))
    intoSingular.out() << WritePolyForSingular(r,FIRST(Lp),V) << (RED(Lp) != NIL ? ", " : ";\n");
  intoSingular.out() << "std(J);" << endl;
  intoSingular.out() << "\"[end]:\";" << endl;

  // SINGULAR OUTPUT:
  Word GBi = NIL;
  while(peekNonWS(outofSingular.in()) == '_')
  {
    while(outofSingular.in().get() != '=');
    Word p = readSingularPoly(r,V,outofSingular.in());
    GBi = COMP(p,GBi);      
  }
  { string em; while(outofSingular.in() >> em && em != "[end]:"); }
  GBi = CINV(GBi);
  
  if (LENGTH(GBi) == 1) 
  { 
    Word rs,ps; PSIMREP(r,FIRST(GBi),&rs,&ps); 
    if (rs == 0) return TRUE;
  }
  return GBi;
    
}
