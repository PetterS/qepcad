/*======================================================================
                          Graph module

Vertices in the graph are cell indices.  A vertex's label is its truth
value.  Edges are directed from dimension i cells to dimension i-1 cells,
and an edge (u,v) exists if and only if cell(u) and cell(v) are adjacent
and cell(u) has dimension 1 greater than cell(v).

void GADDVERTEX(v,l) : v is a vertex (i,j), l is an int label (truth value)
void GADDEDGE(e)     : e is an edge ((i,j),(l,k)) edges are directed
                       and should be kept pointing higher dimension
		       to lower dimension
Word GVERTEXLABEL(v) : v is a vertex (i,j), return is vertex's label
void GNEWLABEL(v,l)  : v is a vertex (i,j), l is an int label (truth value)
Word GPREDLIST(v)    : v is a vertex (i,j), return is list of predecessor
                       vertices
Word GSUCCLIST(v)    : v is a vertex (i,j), return is list of successor
                       vertices

G  = (G1,G2, ... , Gn)
Gi = (i,T)
T  = (T1,T2, ... ,Tm)
Tj = (v,l,e)
v is a vertex, l a label (truth value), e a list of edges.
======================================================================*/
#include "truthbytop.h"

void GADDVERTEX(Word v, Word l, Word *G_)
{
  Word G,i,j,Tp,Tb,T,t,Gp;

Step1: /*  Initialize. */
  G = *G_;
  if (G == NIL) {
    G = LIST1(LIST2(FIRST(v),LIST1(LIST3(v,l,NIL))));
    goto Return; }
  
Step2: /* Add vertex to non-empty graph. */
  FIRST2(v,&i,&j);
  for(Gp = NIL; G != NIL && (i > FIRST(FIRST(G))); G = RED(G))
    Gp = COMP(FIRST(G),Gp);
  if (G == NIL || (i < FIRST(FIRST(G)))) {
    /* No other vertex with same 1st index. */
    G = CONC(Gp,COMP(LIST2(i,LIST1(LIST3(v,l,NIL))),G)); }
  else {
    /* Another vertex with same 1st index exists. */
    ADV(G,&Tb,&G);
    FIRST2(Tb,&t,&T);
    for(Tp = NIL; T != NIL && (j > SECOND(FIRST(FIRST(T)))); T = RED(T))
      Tp = COMP(FIRST(T),Tp);
    /** ERROR CHECK **/
    if (T != NIL && (j == SECOND(FIRST(FIRST(T))))) SWRITE("Error! Dup in GADDVERTEX!\n");
    /** ERROR CHECK **/
    T = CONC(Tp,COMP(LIST3(v,l,NIL),T));
    G = CONC(Gp,COMP(LIST2(t,T),G)); }

Return: /* Prepare to return. */
  *G_ = G;
  return;
}

Word GSTACKHANDLE(Word i, Word G_)
{  
  Word G,Gp,h;
  G = G_;
  for(Gp = NIL; G != NIL && (i > FIRST(FIRST(G))); G = RED(G));
  if (G == NIL || FIRST(FIRST(G)) != i)
    h = NIL;
  else
    h = FIRST(G);
  return h;
}


Word GVERTEXHANDLE(Word v, Word G_)
{
  Word G,i,j,Gp,T,h;

  FIRST2(v,&i,&j);
  h = GSTACKHANDLE(i,G_);
  if (h != NIL) {
    for(T = SECOND(h); T != NIL && SECOND(FIRST(FIRST(T))) != j ; T =  RED(T));
    if (T != NIL)
      h = FIRST(T);
    else
      h = NIL; }

  return h;
}

Word GVERTEXLABEL(Word v, Word G_)
{
  Word l;
  l = SECOND(GVERTEXHANDLE(v,G_));
  return l;
}
  
void GNEWLABEL(Word v, Word l, Word G_)
{
  SLELTI(GVERTEXHANDLE(v,G_),2,l);
  return;
}

void GADDEDGE(Word e, Word G_)
{
  Word a,b,h;

  FIRST2(e,&a,&b);
  h = GVERTEXHANDLE(a,G_);
  SLELTI(h,3,COMP(b,THIRD(h)));
  return;
}

Word GSUCCLIST(Word v, Word G_)
{
  Word h,L;
  h = GVERTEXHANDLE(v,G_);
  L = THIRD(h);
  return L;
}

Word vert2dim(Word v) { return (FIRST(v) % 2) + (SECOND(v) % 2); }

Word GPREDLIST(Word v, Word G_)
{
  Word d,L,i,j,ip,h1,S,w,E,l;

Step1: /* Initialize. */
  d = vert2dim(v);
  FIRST2(v,&i,&j);
  L = NIL;

Step2: /* Any predecessors in the same stack? */
  if (j % 2 == 0)
    L = COMP2(LIST2(i,j-1),LIST2(i,j+1),L);

Step3: /* Predecessors in previous or subsequent stack. */
  for(ip = i - 1; ip <= i + 1; ip += 2) {
    h1 = GSTACKHANDLE(ip,G_);
    if (h1 != NIL) {
      for(S = SECOND(h1); S != NIL; S = RED(S)) {
	FIRST3(FIRST(S),&w,&l,&E);
	if (vert2dim(w) == d+1) {
	  while(E != NIL && ! EQUAL(FIRST(E),v))
	    E = RED(E);
	  if (E != NIL)
	    L = COMP(w,L); } } } }

Return: /* Prepare to return. */
  return L;
}
