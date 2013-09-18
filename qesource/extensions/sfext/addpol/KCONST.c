/*======================================================================
                     KCONST(J,P,G;K,KT)

Construct the set K.

Input:
 J : The set of projection polynomials.
 P : The set of projection factors.
 G : A list of border polynomials (all of the same level).

Output:
 K : A list of the the border polynomials G along with all polynomials
     in P which are derivatives of any order of elements of G.
 KT: The "derivative tree" structure.  The derivative tree is a list
     (V_1,...,V_t), where t is the number of elements in K.  Each 
     element is a pair (p,C), where p is the PO_LABEL of a polynomial
     in K, and C is a) the list of all PO_LABELS of polynomials in P
     which are factors of derivitives of the polynomial with label p,
     b) is NIL if the derivative has been computed and is constant,
     c) is zero if the derivative of the polynomial with label p has
     not been computed.

======================================================================*/
#include "qepcad.h"
/*--------- S1 operations. -----------*/

static Word S1_IN(Word o, Word S1)
{
      return ( MEMBER(o,S1) );
}

static void S1_ADD(Word o, Word *S1)
{
      if ( ! S1_IN(o,*S1) ) {
	*S1 = COMP(o,*S1); }
      return;
}

static Word S1_GET(Word *S1)
{
      Word s1;
      ADV(*S1,&s1,S1);
      return ( s1 );
}


static Word S1_EMPTY(Word S1)
{
      return ( (S1 == NIL) );
}

/*--------- S2 operations. -----------*/

static Word S2_IN(Word o, Word S2)
{
      Word S;
      for(S = S2; S2 != NIL; S2 = RED(S2)) {
	if ( EQUAL(FIRST(FIRST(S2)),o) )
	  return (1); }
      return (0);
}

static void S2_ADD(Word o, Word *S2)
{
      *S2 = COMP(o,*S2);
      return;
}

static Word S2_GET(Word *S2)
{
      Word s2;
      ADV(*S2,&s2,S2);
      return (s2);
}


static Word S2_EMPTY(Word S2)
{
      return ( (S2 == NIL) );
}

/*--------- Is p a factor of q? ----------------*/
static Word ISPFACQ(Word p, Word q)
{
      Word l_p,R,r;
      l_p = LELTI(p,PO_LABEL);
      for(R = LELTI(q,PO_PARENT); R != NIL; R = RED(R)) {
	r = FIRST(R);
	if ( (FIRST(r) == PO_FAC) &&
	    EQUAL(LELTI(THIRD(r),PO_LABEL),l_p) )
	  return (1); }
      return (0);
}
/*--------- Is p the derivative of q? ----------------*/
static Word ISPDERQ(Word p, Word q)
{
      Word l_p,R,r;
      l_p = LELTI(p,PO_LABEL);
      for(R = LELTI(q,PO_PARENT); R != NIL; R = RED(R)) {
	r = FIRST(R);
	if ( (FIRST(r) == PO_DER) &&
	    EQUAL(LELTI(THIRD(r),PO_LABEL),l_p) )
	  return (1); }
      return (0);
}
/*--------- List of derivative factor  indices. --------*/

static Word LIST_OF_DI(Word o, Word J, Word P)
{
      Word i,P_o,h,d,Lp,L;

/* Is P_o (the pol with label o) linear in x_i?. */
i = SECOND(o);
P_o = POLFLAB(o,P);
if ( PDEG(LELTI(P_o,PO_POLY)) < 2 )
  return (NIL);

/* Has the derivative of P_o already been computed? */
h = LIST3(PO_DER,0,P_o);
d = PPWITHHIST(J,i,h);
if (! d)
  return (0);

/* Make list of derivative factor indices. */
Lp = LIST_OF_FACS(d,P);
for(L = NIL; Lp != NIL; Lp = RED(Lp)) 
  L = COMP(LELTI(FIRST(Lp),PO_LABEL),L);
return (L);
}

/*------ KCONST! ----------*/

void KCONST(Word J, Word P, Word G, Word *K_, Word *KT_)
{
      Word S1,S2,Gp,o,L,l,KT,K,i,j;

/* Initialization. */
      S1 = NIL; S2 = NIL;
      for(Gp = G; Gp != NIL; Gp = RED(Gp)) {
	o = LELTI(FIRST(Gp),PO_LABEL); S1_ADD(o,&S1); }

/* The Loop. */
      while ( ! S1_EMPTY(S1) ) {
	o = S1_GET(&S1);
	L =  LIST_OF_DI(o,J,P);
	S2_ADD(LIST2(o,L),&S2);
	for(; L > NIL; L = RED(L)) {
	  l = FIRST(L);
	  if ( ! S2_IN(l,S2) ) {
	    S1_ADD(l,&S1); } } }

/* Construct list of derivatives. */
      KT = S2;
      for(K = NIL; ! S2_EMPTY(S2); ) {
	o = S2_GET(&S2);
	/*  FIRST2(RED(FIRST(o)),&i,&j);
	    K = COMP( LELTI(LELTI(P,i),j), K); } */
	K = COMP( POLFLAB(FIRST(o),P), K); }
      
/* Prepare to return. */
      *K_ = K;
      *KT_ = KT;
      return;
}
