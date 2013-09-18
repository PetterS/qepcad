/*
Arnon-Collins-McCallum adjecncy for 2-D CAD's

c  : a single-point cell in the 1D CAD.
A  : a primitive squarefree integral polynomial.
I  : a logarithmic standard interval isolating a root of A.
     This root is the cell c.  We have a restriction on I
     that it be contained in the union of c and its left and
     right neighbors.  We don't allow a 1-point interval.
P  : the projection factor set.

*/
#include "oldadj.h"

Word ACMADJ2D(Word c, Word c_l, Word c_r, Word P)
{
  Word P_2,L,t,i,x1,x2,s,e,Q,y1,y2,p,M,b,Ip,ip1,ip2,i1,i2,i_l,i_r;
  Word H,h1,h2,p1,p2,p3,d,J,K,G,I,A,R,pp,ep,j1,j2,P1,P2,Sol,k,nl,nr,il,ir;

Step0: /* Shouldn't even have been called. */ 
  if (LENGTH(LELTI(c,CHILD)) <= 0) {
    Sol = NIL;
    goto Return; }

Step1: /* Get (A,I) defining c. */
  s = LELTI(c,SAMPLE);
  FIRST3(s,&M,&I,&b);
  ANFAF(M,I,LAST(b),&A,&Ip);
  FIRST2(Ip,&ip1,&ip2);
  i1 = RNLBRN(ip1);
  i2 = RNLBRN(ip2);

Step2: /* Get sample points for c_l and c_r. */
  i_l = RNLBRN(SPRLC(c_l));
  i_r = RNLBRN(SPRLC(c_r));

Step3: /* Either I is an open SI containing c, or H and I are consecutive
SI's such that H = (h1,h2) and I = (i1,i2) and h2 = i1 = coordinate of c. */
  if (LBRNCOMP(i1,i2) != 0) {
    H = 0;
    t = LBRNSIGN(IUPLBREVAL(A,i2)); if (t == 0) SWRITE("Error in ACMADJ2D\n");
    while(LBRNCOMP(i1,i_l) < 0 || LBRNCOMP(i_r,i2) < 0) {
      i = LSIM(i1,i2);
      s = LBRNSIGN(IUPLBREVAL(A,i));
      if (s == 0) {
	i1 = i; i2 = i; break; }
      if (s == t)
	i2 = i;
      else
	i1 = i; } }
  if (LBRNCOMP(i1,i2) == 0) {
    h2 = i1;
    p1 = SECOND(LBRNDIF(i1,i_l));
    p2 = SECOND(LBRNDIF(i_r,i1));
    if (i1 == 0) p3 = 1; else p3 = SECOND(i1);
    p = 4 + IMAX(p1,IMAX(p2,p3)); /* The 4 is arbitrary. */
    d = LBRNFIE(1,-p);
    h1 = LBRNDIF(h2,d);
    i2 = LBRNSUM(i1,d);
    H = LIST2(h1,h2); }
  I = LIST2(i1,i2);


Step4: /* Initialize main loop. */
  P_2 = LELTI(P,2);
  L = LLSISS(c);

if (L == NIL) {
  Sol = ASYS1(A,H,I,P_2,c_l,c_r);
  goto Return;
}

  R = NIL;
  ep = FIRST(L);

Step5: /* Loop over each section cell in the stack. */
  for(i = 2; L != NIL; i += 2) {
    ADV(L,&e,&L);

    x1 = 0;
    x2 = 0;
    FIRST3(e,&s,&J,&K);
    for(Q = P_2; s != NIL; s = RED(s), Q = RED(Q)) {
      if (FIRST(s) == 0) {
	p = LELTI(FIRST(Q),PO_POLY);
	
	if (H == 0) {
	  G = RIIFACMA(I,A,t,p,J,K); I = G; }
	else
	  G = RIIFACMABR(p,J,K,&H,&I);
	FIRST2(DNCAC(e,G,p),&y1,&y2);
	x1 += y1;
	x2 += y2; } }
    R = COMP(LIST2(x1,x2),R); }
  R = INV(R);
    
Step6: /* Determine number of negative asymptotes. */
  J = SECOND(ep);
  j2 = FIRST(J);
  i2 = SECOND(I);
  if (H == 0)
    i1 = FIRST(I);
  else
    i1 = FIRST(H);

  x1 = 0; x2 = 0;
  /*  for(Q = P_2; s != NIL; s = RED(s), Q = RED(Q)) { OLD WAY */
  for(Q = P_2; Q != NIL; Q = RED(Q)) {
    p = LELTI(FIRST(Q),PO_POLY);
    pp = PTMV(2,p);

    P1 = IPIPP(1,IPLBREVAL(2,pp,i1));
    P2 = IPIPP(1,IPLBREVAL(2,pp,i2));
  
    j1 = LBRNNEG(IUPLRB(P1));
    if (LBRNCOMP(j1,j2) < 0)
      x1 += LENGTH(IPRRILBRI(P1,LIST2(j1,j2)));

    j1 = LBRNNEG(IUPLRB(P2));
    if (LBRNCOMP(j1,j2) < 0)
      x2 += LENGTH(IPRRILBRI(P2,LIST2(j1,j2))); }
    
Step7: /* Construct adjacency assignment list. */
  Sol = NIL;
  k = FIRST(LELTI(c,INDX));
  nl = LENGTH(LELTI(c_l,CHILD));
  nr = LENGTH(LELTI(c_r,CHILD));
  il = 2;
  ir = 2;
  while(x1 > 0) {
    Sol= COMP(LIST2(LIST2(k-1,il),LIST2(k,AD2D_N_In)),Sol);
    il += 2;
    x1--; }
  while(x2 > 0) {
    Sol= COMP(LIST2(LIST2(k,AD2D_N_In),LIST2(k+1,ir)),Sol);
    ir += 2;
    x2--; }
  for(i = 2; R != NIL; i += 2, R = RED(R)) {
    FIRST2(FIRST(R),&x1,&x2);
    while(x1 > 0) {
      Sol= COMP(LIST2(LIST2(k-1,il),LIST2(k,i)),Sol);
      il += 2;
      x1--; }
    while(x2 > 0) {
      Sol= COMP(LIST2(LIST2(k,i),LIST2(k+1,ir)),Sol);
      ir += 2;
      x2--; } }

  while(il < nl) {
    Sol= COMP(LIST2(LIST2(k-1,il),LIST2(k,AD2D_Infy)),Sol);
    il += 2; }
  while(ir < nr) {
    Sol= COMP(LIST2(LIST2(k,AD2D_Infy),LIST2(k+1,ir)),Sol);
    ir += 2; }

Return: /* Prepare to return. */
  return Sol;
}



Word ASYS1(Word M, Word H, Word I, Word P2, Word c_l, Word c_r)
{
  Word P,p,t,i1,i2,L1p,L2p,L1n,L2n,n1p,n1n,n2p,n2n,p1,p2,L1,L2,J,j,z,Sol,i,L,S,Ip;

Step1: /* Refine I so that for each p in P_2 p(x,0) has no sign variations in I. */
  if (H != 0)
    I = ASYS2(M,H,I,P2);
  else {
    t = LBRNSIGN(IUPLBREVAL(M,SECOND(I))); /* Get trend of M in I. */
    for(P = P2; P != NIL; P = RED(P)) {
      p = LELTI(FIRST(P),PO_POLY);
      p = IPEVAL(2,p,2,0);
      while(TSVSLI(p,I)) {
	if (LBRIIBISECT(I,M,t,&J)) {
	  FIRST2(I,&i1,&i2);
	  I = ASYS2(M,LIST2(i1,FIRST(J)),LIST2(FIRST(J),i2),P2);
	  goto Step2; }
	else 
	  I = J; } }
    if (LBRIIBISECT(I,M,t,&J)) {
      FIRST2(I,&i1,&i2);
      j = FIRST(J);
      I = LIST2(LSIM(i1,j),LSIM(j,i2)); }
    else
      I = J; }

Step2: /* Get number of roots each way. */
  FIRST2(I,&i1,&i2);
  L1p = NIL; L1n = NIL; L2p = NIL; L2n = NIL; 
  for(P = CINV(P2); P != NIL; P = RED(P)) {
    p = LELTI(FIRST(P),PO_POLY);
    p1 = IPBREI(2,p,1,LBRNRN(i1));
    p2 = IPBREI(2,p,1,LBRNRN(i2));
    
    for(n1p = 0, n1n = 0, L1 = IPRRID(IPPGSD(1,p1)); L1 != NIL; L1 = RED(L1))
      if (LBRNCOMP(SECOND(FIRST(L1)),0) <= 0)
	n1n++;
      else
	n1p++;

    for(n2p = 0, n2n = 0, L2 = IPRRID(IPPGSD(1,p2)); L2 != NIL; L2 = RED(L2))
      if (LBRNCOMP(SECOND(FIRST(L2)),0) <= 0)
	n2n++;
      else
	n2p++;
    L1p = COMP(n1p,L1p);
    L1n = COMP(n1n,L1n);
    L2p = COMP(n2p,L2p);
    L2n = COMP(n2n,L2n); }

Step3: /* Make assignments. */
  Sol = NIL;
  z = ZERO_VECTOR(LENGTH(P2));
  Ip = LAST(LELTI(c_l,INDX));
  for(i = 2, L = RED(LELTI(c_l,CHILD)); L != NIL; L = RED2(L), i += 2) {
    if (!VECTOR_LTEQ(L1n,z)) {
      Sol = COMP(LIST2(LIST2(Ip,i),LIST2(Ip+1,AD2D_N_In)),Sol);
      for(j = 1,S  = FIRST(LELTI(FIRST(L),SIGNPF)); S != NIL; S = RED(S),j++) {
	if (FIRST(S) == 0)
	  SLELTI(L1n,j,LELTI(L1n,j) - 1); } }
    else
      Sol = COMP(LIST2(LIST2(Ip,i),LIST2(Ip+1,AD2D_Infy)),Sol); }

  Ip = LAST(LELTI(c_r,INDX));
  for(i = 2, L = RED(LELTI(c_r,CHILD)); L != NIL; L = RED2(L), i += 2) {
    if (!VECTOR_LTEQ(L2n,z)) {
      Sol = COMP(LIST2(LIST2(Ip-1,AD2D_N_In),LIST2(Ip,i)),Sol);
      for(j = 1,S  = FIRST(LELTI(FIRST(L),SIGNPF)); S != NIL; S = RED(S),j++) {
	if (FIRST(S) == 0)
	  SLELTI(L2n,j,LELTI(L2n,j) - 1); } }
    else
      Sol = COMP(LIST2(LIST2(Ip-1,AD2D_Infy),LIST2(Ip,i)),Sol); }

  return Sol;
}


Word ASYS2(Word M, Word H, Word I, Word P2)
{
  Word P,p,tH,tI,h1,h2,i1,i2,L1p,L2p,L1n,L2n,n1p,n1n,n2p,n2n,p1,p2,L1,L2,t;

  tH = -LBRNSIGN(IUPLBREVAL(M,FIRST(H)));
  tI = LBRNSIGN(IUPLBREVAL(M,SECOND(I)));

Step1: /* Refine I and H. */
  for(P = P2; P != NIL; P = RED(P)) {
    p = LELTI(FIRST(P),PO_POLY);
    p = IPEVAL(2,p,2,0);
    while(TSVSLI(p,H)) {
      FIRST2(H,&h1,&h2);
      H = LIST2(LSIM(h1,h2),h2); }
    while(TSVSLI(p,I)) {
      FIRST2(I,&i1,&i2);
      I = LIST2(LSIM(i1,i2),i2); } }
  FIRST2(H,&h1,&h2);
  FIRST2(I,&i1,&i2);
  I = LIST2(LSIM(h1,h2),LSIM(i1,i2));

  return I;
}

/* Logrithmic binary rational isolating interval bisection. */
Word LBRIIBISECT(Word I, Word p, Word t, Word *J_)
{
      Word f,i1,i2,i,s,J;
  
Step1: /* Initialize. */
      f = 0;
      FIRST2(I,&i1,&i2);
      i = LSIM(i1,i2);
      s = IUPBRES(p,i);

Step2: /* Construct refined interval. */
      if (s == 0) {
	f = 1;
	J = LIST2(i,i); }
      else if (s == t)
	J = LIST2(i1,i);
      else
	J = LIST2(i,i2);

Return: /* Prepare to return. */
      *J_ = J;
      return f;
}
