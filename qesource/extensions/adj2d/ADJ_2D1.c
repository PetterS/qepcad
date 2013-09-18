/*======================================================================
                      L <- ADJ_2D1(c,c_l,P,J)

Adjacency for 2D CAD cells.

Inputs
  c  : a section cell in the 1D CAD.
  c_l: a neighbor of c.
  P  : the projection factor set.
  J  : the projection polynomial set.

Outputs
  L  : a list of elements of the form ((i,j),(k,l))
       indicating an adjacency between cell (i,j) and cell (k,l).
======================================================================*/
#include "adj2D.h"
#include "adj2D.h"
/**************************************/
static FILE *OUTPUT;

static void init()
{
  OUTPUT = fopen("stats_ADJ_2D1","a");
}
void sa_send(const char* S)
{
  fprintf(OUTPUT,"%s",S);
}
static void uninit()
{
  fclose(OUTPUT);
}
/**************************************/






#define tImIngs

#ifdef  tImIngs
Word ADJ_2D1(Word c, Word c_l, Word P, Word J)
{
  Word U,V,v_l,Sol,S,A,Ap,a,b;
  /*
init();
sa_send("[");
  */
Step1: /* Initialization. */
  v_l = LDCOEFMASK(c,P,J);
  U = AD2DS_CONS(c_l,P);
  V = AD2DS_CONS(c,P);

Step2: /* Get Adjacencies. */
  /* Sol = ADJ_2D1_SIMPLE(U,V,v_l,FIRST(LELTI(c,INDX))); */
  Sol = ADJ_2D1P1(U,V,v_l,FIRST(LELTI(c,INDX)));

Step3: /* If c_l is to the right of c, reverse order of pairs. */
  if (FIRST(LELTI(c,INDX)) < FIRST(LELTI(c_l,INDX))) {
    for(S = NIL; Sol != NIL; Sol = RED(Sol)) {
      for(A = NIL, Ap = FIRST(Sol); Ap != NIL; Ap = RED(Ap)) {
	FIRST2(FIRST(Ap),&a,&b);
	A = COMP(LIST2(b,a),A); }
      S = COMP(A,S); }
    Sol = S; }

Return: /* Prepare to return. */
  /*
  sa_send("]\n");
  uninit();
  */
  return Sol;
}

#else

Word ADJ_2D1(Word c, Word c_l, Word P, Word J)
{
  Word U,V,v_l,Sol,S,A,Ap,a,b;
  Word t,i,I = 1000;

Step1: /* Initialization. */
  printf("\n");
  t = ACLOCK();
  for(i = 0; i < I; i++)
    v_l = LDCOEFMASK(c,P,J);
  t = ACLOCK() - t;
  printf("LDCOEFMASK:        %6.3f\n",t/(float)I);
  t = ACLOCK();
  for(i = 0; i < I; i++)    
    U = AD2DS_CONS(c_l,P);
  t = ACLOCK()-t;
  printf("AD2DS_CONS open:   %6.3f\n",t/(float)I);
  t = ACLOCK();
  for(i = 0; i < I; i++)    
    V = AD2DS_CONS(c,P);
  t = ACLOCK()-t;
  printf("AD2DS_CONS closed: %6.3f\n",t/(float)I);

Step2: /* Get Adjacencies. */
  t = ACLOCK();
  for(i = 0; i < I; i++)    
    Sol = ADJ_2D1P1(U,V,v_l,FIRST(LELTI(c,INDX)));
  t = ACLOCK()-t;
  printf("ADJ_2D1P1:         %6.3f\n",t/(float)I);
  printf("\n");

Step3: /* If c_l is to the right of c, reverse order of pairs. */
  if (FIRST(LELTI(c,INDX)) < FIRST(LELTI(c_l,INDX))) {
    for(S = NIL; Sol != NIL; Sol = RED(Sol)) {
      for(A = NIL, Ap = FIRST(Sol); Ap != NIL; Ap = RED(Ap)) {
	FIRST2(FIRST(Ap),&a,&b);
	A = COMP(LIST2(b,a),A); }
      S = COMP(A,S); }
    Sol = S; }

Return: /* Prepare to return. */
  return Sol;
}

#endif
