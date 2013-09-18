#ifndef _ADJ2D_HEADER_
#define _ADJ2D_HEADER_

/* Header file for 2D adjacency code. */
#include "qepcad.h"

/* AD2D_Cell definitions. */
#define AD2D_Index 1
#define AD2D_Mult  2

/* Package definitions. */
#define AD2D_FAIL 0
#define AD2D_Infy BETA - 1
#define AD2D_N_In -1
#define AD2D_ErrI -2

/* C Function Prototypes */
Word AD2DC_CONS(Word c, Word P);
Word AD2DS_CONS(Word c, Word P);
Word ADD_2_SOL(Word a, Word S);
Word ADJ_2D(Word c, Word c_l, Word c_r, Word P, Word J);
Word ADJ_2D1(Word c, Word c_l, Word P, Word J);
Word ADJ_2D1P1(Word U, Word V, Word w_l, Word B);
Word ADJ_2D1P2(Word U, Word V, Word w_l, Word B);
Word ADJ_2D1P3(Word U, Word w_l, Word B);
Word ADJ_2D1_COMPLETE(Word c, Word c_l, Word c_r, Word P, Word J);
Word ADJ_2D1_SIMPLE(Word U, Word V, Word w_l, Word B);
Word CWD_VECTOR_Q(Word u, Word v);
Word EQUAL_ON_ONES(Word u, Word v);
Word LDCOEFMASK(Word c, Word P, Word J);
Word LDCOEFMASK(Word c, Word P, Word J);
Word Mystery_f(Word L, Word R, Word M);
Word P1(Word U, Word V, Word W, Word v_l, Word B);
Word P2(Word x_l, Word x_r, Word U, Word V, Word W, Word v_l, Word B);
Word P3(Word U, Word V, Word W, Word v_l, Word B);
Word P4(Word U, Word V, Word W, Word v_l, Word B);
Word SUM_NORM_SP(Word v);
Word VECTOR_DIF(Word u, Word v);
Word VECTOR_DIF_S(Word u, Word v, Word *f);
Word VECTOR_LTEQ(Word u, Word v);
Word VECTOR_NEG(Word u);
Word VECTOR_ODD_E(Word v_);
Word VECTOR_SEMI_COMP(Word u, Word v);
Word VECTOR_SUM(Word u, Word v);
Word VECTOR_S_PROD(Word s, Word v);
Word ZERO_VECTOR(Word n);
Word ADJ_2D1P2(Word U, Word V, Word w_l, Word B);
void ADJ_2D_TEST(Word D, Word P, Word J);
Word ACMADJ2D(Word c, Word c_l, Word c_r, Word P);
Word LBRIIBISECT(Word I, Word p, Word t, Word *J_);
Word DNCAC(Word e, Word I, Word P);
Word LLBRSPFSS(Word c);
Word LLSISS(Word c);
Word RIIFACMA(Word I, Word A, Word t, Word P, Word J, Word K);
Word  RIIFACMABR(Word P, Word J, Word K, Word *H, Word *I);
Word SPRLC(Word c);
Word ADJ2DITOEL(Word L, Word c1, Word c0);
Word CCTV(Word C);
void CTVPROPUP(Word C, Word t, Word N, Word by);
void TVCLOSURE1D(Word D, Word P, Word J, Word k, Word t);
void TVCLOSURE1DS(Word D, Word P, Word J, Word k, Word t);
void TVCCOSBSVAI(Word C0, Word C1, Word L);
#endif
