/***************************************************************
***
*** gcword.cc
***
*** This file implements the gcw_MARK() function, which is called
*** by the modified saclib garbage collector in order to account
*** for saclib Words pointed to by GCWord objects.
***
*** This file implements the gcw_register(p) function, which is
*** called upon creation and upon destuction of a GCWord object.
*** Each call adds p, the address of the GCWord, to the vector G,
*** so that if a given address occurs an odd number of times, it
*** contains a live GCWord object ... which the garbage collector
*** needs to consider.
***
*** The clean() function modifies vector G so that an address
*** appears in G after the call if and only if it appeared an odd
*** number of times before the call, and no address appears more
*** than once after the call.
***
*** CWB 5/15/00
***************************************************************/
#include <vector>
#include <algorithm>
#include "gcword.h"
using namespace std;

extern "C" {
void gcw_MARK();
}

static vector<Word*> G;
static int lim = 10;

void clean()
{
  //-- a hack to ensure that lim ends up being NU -------------//
  if (lim < NU) lim = NU;

  sort(G.begin(),G.end());

  //-- compacts sorted array by ignoring double values --------//
  int i,j,N = G.size()-1;
  for(i = 0; i < N; i++)
    if (G[i] == G[i+1]) {
      G[i] = G[i+1] = 0;
      i++; }
  for(i = 0, j = 0; j <= N; j++)
    if (G[j] != 0)
      swap(G[i++],G[j]);
  G.resize(i);
}

void gcw_register(Word *p)
{
  G.push_back(p);
  if (G.size() == lim)
    clean();
}

void gcw_MARK()
{
  //  SWRITE("gcw size is: ");IWRITE(G.size()); SWRITE("\n");
  clean();
  for(int i = 0; i < G.size(); i++)
    if (*G[i] > BETA && *G[i] < BETAp && (*G[i] & 1))
      MARK(*G[i]);

  return;
}
