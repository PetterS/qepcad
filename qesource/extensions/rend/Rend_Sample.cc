/*************************************************************
 **
 **  Rend_Sample.cc
 **
 **
 *************************************************************/
#include "Rend_Sample.h"  

/*************************************************************
 **  Class Rend_Sample Function Definitions
 *************************************************************/
Rend_Sample_1DS::Rend_Sample_1DS(Word C,Word P)
{
  Word T,i,t1,t2,t3,j1,j2,s1,s2,s;

  //-- Set P_index --//
  for(i = 1, s = FIRST(LELTI( C, SIGNPF )); FIRST(s) != 0; i++, s = RED(s));
  P_index = THIRD( LELTI( LELTI(LELTI(P,1),i) , PO_LABEL) );

  //-- Set A to the minpol of sample point, and I to isolating int --/
  T = LELTI( C , SAMPLE );
  FIRST3(T,&t1,&t2,&t3); // t3 is a LIST of ANF elements.
  ANFAF(t1,t2,FIRST(t3),&(A.W),&T);
  FIRST2(T,&j1,&j2);
  j1 = RNLBRN(j1);
  j2 = RNLBRN(j2);
  I.W = LIST2( j1 , j2 );

  //-- Set t to the trend. --//
  s1 = IUPBRES(A.W,j1);
  s2 = IUPBRES(A.W,j2);
  if (s1 == 0) {
    t = 0;
    I.W = LIST2(j1,j1); }
  else if (s2 == 0) {
    t = 0;
    I.W = LIST2(j2,j2); }
  else
    t = s2;	 
}


Rend_Sample_1DS::~Rend_Sample_1DS()
{
  
}

/*************************************************************
 **  Refines I to 2^k or less, and returns binary rational 
 **  middle of interval.
 *************************************************************/
Word Rend_Sample_1DS::coordinate(int k)
{
  Word P,J,j1,j2,js1,js2,s1,s2;

  P = A.W; J = I.W;

Step1: /* Refine root to desired accuracy.  Note: I'm assuming
that J is a binary rational. */
  if (t != 0)
    J = IPIIRB(P,J,t,k);

Step2: /* Save interval refinement and return. */
  I.W = J;
  FIRST2(J,&j1,&j2);
  return LBRNP2PROD(LBRNSUM(j1,j2),-1);

}

Word Rend_Sample_1DS::round(int k, int roundup)
{
  Word P,J,j1,j2,js1,js2,s1,s2;

  P = A.W; J = I.W;

Step1: /* Refine root to desired accuracy.  Note: I'm assuming
that J is a binary rational. */
  if (t != 0)
    J = IPIIRB(P,J,t,k);

Step2: /* Save interval refinement and return. */
  I.W = J;
  FIRST2(J,&j1,&j2);
  return (roundup) ? j2 : j1;
}

/*************************************************************
 **  weakcompare
 *************************************************************/
Word Rend_Sample_1DS::weakcompare(Word R)
{
  Word i1,i2;
  FIRST2(I.W,&i1,&i2);
  if ( ICOMP(R, LBRNRN(i1) ) <= 0 )
    return -1;
  if ( ICOMP(R, LBRNRN(i2) ) >= 0 )
    return 1;
  return 0;
}



/*************************************************************
 **  Class Rend_Sample_1DO Function Definitions
 *************************************************************/
Rend_Sample_1DO::Rend_Sample_1DO(Rend_Cell *dad)
{
  Word i;
  i = dad -> index;
  l = &(dad -> parent -> child[i-1]);
  r = &(dad -> parent -> child[i+1]);
  L.W = NIL;
}


Rend_Sample_1DO::~Rend_Sample_1DO()
{
  
}


Word Rend_Sample_1DO::coordinate(int k)
{
  Word e,j1,j2,J,kp = k;
  do {
    j1 = l -> sample -> round(kp,1);
    j2 = r -> sample -> round(kp,0);
    kp--;
  } while(LBRNCOMP(j1,j2) >= 0);

  /*  e = LBRNFIE(1,k-1);
  if (l -> index != AD2D_N_In )
    j1 = LBRNSUM(j1,e);
  if (r -> index != AD2D_Infy)
    j2 = LBRNDIF(j2,e);
    */

  J = LIST2(j1,j2);
  return J;
}

/*************************************************************
 **  Class Rend_Sample_2DS
 *************************************************************/
Rend_Sample_2DS::Rend_Sample_2DS(Word C)
{
  Word T,i,t1,t2,t3,j1,j2,s1,s2,s;
  Word tB,tJ,tA,tI,d1,d2,d3,d4,d5;

  //-- Set A to the minpol of sample point, and I to isolating int --/
  T = LELTI( C , SAMPLE );

  if (! ISPRIMIT(T)) {
    //-- The sample point is not in primitive representation. --//
    FIRST5(T,&tB,&tJ,&tA,&tI,&d1);
    I.W = LIST2(RNLBRN(FIRST(tJ)),RNLBRN(SECOND(tJ)));
    A.W = T; }
  else {
    //-- The sample point is in primitive representation. --//
    FIRST3(T,&t1,&t2,&t3); 
    t3 = SECOND(t3); // t3 is a LIST of ANF elements. 
    ANFAF(t1,t2,t3,&(A.W),&(tJ)); 
    I.W = LIST2(RNLBRN(FIRST(tJ)),RNLBRN(SECOND(tJ)));

    //-- Set t to the trend. --//
    FIRST2(I.W,&j1,&j2);
    s1 = IUPBRES(A.W,j1);
    s2 = IUPBRES(A.W,j2);
    if (s1 == 0) {
      t = 0;
      I.W = LIST2(j1,j1); }
    else if (s2 == 0) {
      t = 0;
      I.W = LIST2(j2,j2); }
    else
    t = s2;
  }
}


Rend_Sample_2DS::~Rend_Sample_2DS()
{
  
}

/*************************************************************
 **  Refines I to 2^k or less, and returns binary rational 
 **  lower endpoint.
 *************************************************************/
Word Rend_Sample_2DS::coordinate(int k)
{
  Word J,j1,j2,JL,S,tB,tJ,tA,tI,d1,i;

  
Step1: /* Initialize and decide if refinement is even necessary. */
  S = A.W; J = I.W;
  if (EQUAL(FIRST(J),SECOND(J)))
    return FIRST(J);
  if (LSILW(J) <= k)
    return LSIM(FIRST(J),SECOND(J));
  
Step2: /* Further refinement required. */
  if (ISLIST(FIRST(S))) {
    FIRST5(S,&tB,&tJ,&tA,&tI,&d1);
    for(i = LSILW(J); i > k; i--)
      tJ = AFUPIIR(tA,tI,tB,tJ);
    J = LIST2(RNLBRN(FIRST(tJ)),RNLBRN(SECOND(tJ)));
    I.W = J;
    A.W = LIST5(tB,tJ,tA,tI,d1); }
  else {
    /* Refine root to desired accuracy.  Note: I'm assuming
       that J is a binary rational. */
    if (t != 0)
      J = IPIIRB(S,J,t,k);

    /* Save interval refinement and return. */
    I.W = J;  }

  if (EQUAL(FIRST(J),SECOND(J)))
    return FIRST(J);
  return LSIM(FIRST(J),SECOND(J));

}


/*************************************************************
 **  Class Rend_Sample_2DC
 *************************************************************/
Rend_Sample_2DC::Rend_Sample_2DC(Word C,Word P)
{
  Word i,s;
  //-- Set P_index --//
  for(i = 1, s = FIRST(LELTI( C, SIGNPF )); FIRST(s) != 0; i++, s = RED(s));
  P_index = THIRD( LELTI( LELTI(LELTI(P,2),i) , PO_LABEL) );

  L.W = NIL;

}

Rend_Sample_2DC::~Rend_Sample_2DC()
{
  
}

Word Rend_Sample_2DC::coordinate(int k)
{
  return L.W;
}
  
void Rend_Sample_2DC::add_point(Word p)
{
  L.W = COMP(p,L.W);
}

void Rend_Sample_2DC::clear_points()
{
  L.W = NIL;
}

/*************************************************************
 **  Class Rend_Sample_BR
 *************************************************************/
Rend_Sample_BR::Rend_Sample_BR(Word a)
{
  N.W = a;
}

Rend_Sample_BR::~Rend_Sample_BR()
{
  
}

Word Rend_Sample_BR::coordinate(int k)
{
  return N.W;
}
  


