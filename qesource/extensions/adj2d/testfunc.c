/*
Function for testing the performance of the adjacency algorithm.
*/
#include "adj2D.h"
#include "adj2D.h"
#include "stdio.h"

void ADJ_2D_TEST(Word D, Word P, Word J)
{
  Word t,S,c_l,c,c_r,L,k;
  Word i,I = 100, t1, t2, L1, L2, f1, f2;
  float T,TT;

  /**** 3 Stack method! ****/
    S = LELTI(D,CHILD);
    k = 0;
    TT = 0.0;
    SWRITE("\n3-Stack method");
    SWRITE("\n---------------------");
    for(ADV(S,&c_l,&S); S != NIL; c_l = c_r) {
      k++;
      ADV2(S,&c,&c_r,&S);
      if (LELTI(c,CHILD) == NIL || 
	  (LELTI(c_l,CHILD) == NIL && LELTI(c_r,CHILD) == NIL) )
	continue;
      printf("\n  Stack%3d ",2*k);

      if (LELTI(c_l,CHILD) == NIL || LELTI(c_r,CHILD) == NIL) {
	t = 0;
	L = LIST2(0,0); }
      else {

	t = ACLOCK();
	for(i = 0; i < I; i++)
	  L = ADJ_2D(c,c_l,c_r,P,J);
	t = ACLOCK() - t;
	T = t / (float)I;
	printf("%8.3fms",T);
	TT += T; }
      
      if (LENGTH(L) > 1) printf(" [Failure]");
      else    printf(" [Success]"); }
    SWRITE("\n---------------------");
    printf("\n  Total %11.3fms",TT); 
  

  /**** 2 Stack method! ****/
    S = LELTI(D,CHILD);
    k = 0;
    TT = 0.0;
    SWRITE("\n\n2-Stack method");
    SWRITE("\n---------------------");
    for(ADV(S,&c_l,&S); S != NIL; c_l = c_r) {
      k++;
      ADV2(S,&c,&c_r,&S);
      if (LELTI(c,CHILD) == NIL || 
	  (LELTI(c_l,CHILD) == NIL && LELTI(c_r,CHILD) == NIL) )
	continue;
      printf("\n  Stack%3d ",2*k);

      if (LELTI(c_l,CHILD) == NIL) {
	f1 = 1;
	t1 = 0; }
      else {
	t1 = ACLOCK();
	for(i = 0; i < I; i++)
	  L1 = ADJ_2D1(c,c_l,P,J);
	t1 = ACLOCK() - t1;
	f1 = LENGTH(L1) > 1 ? 1 : 0; }
     
      if (LELTI(c_r,CHILD) == NIL) {
	f2 = 1;
	t2 = 0; }
      else {
	t2 = ACLOCK();
	for(i = 0; i < I; i++)
	  L2 = ADJ_2D1(c,c_r,P,J);
	t2 = ACLOCK() - t2;
	f2 = LENGTH(L2) > 1 ? 1 : 0; }

      printf("%8.3fms",(t1 + t2) / (float)I);
      printf("  left %8.3fms",t1 / (float)I);
      if (f1) printf(" [Failure]");
      else    printf(" [Success]");
      printf("  right %8.3fms",t2 / (float)I);
      if (f2) printf(" [Failure]");
      else    printf(" [Success]");
      TT += (t1 + t2) / (float) I; }
    SWRITE("\n---------------------");
    printf("\n  Total %11.3fms",TT);
	
  
    /**** ACM method! ****/
    S = LELTI(D,CHILD);
    k = 0;
    TT = 0.0;
    SWRITE("\n\nACM method");
    SWRITE("\n---------------------");
    for(ADV(S,&c_l,&S); S != NIL; c_l = c_r) {
      k++;
      ADV2(S,&c,&c_r,&S);
      if (LELTI(c,CHILD) == NIL || 
	  (LELTI(c_l,CHILD) == NIL && LELTI(c_r,CHILD) == NIL) )
	continue;
      printf("\n  Stack%3d ",2*k);

      t = ACLOCK();
      for(i = 0; i < I; i++)
	L = ACMADJ2D(c,c_l,c_r,P);
      t = ACLOCK() - t;
      T = t / (float)I;
      printf("%8.3fms",T);
      TT += T; }
    SWRITE("\n---------------------");
    printf("\n  Total %11.3fms",TT);

    
    SWRITE("\n\n"); 
  
    return;
}
