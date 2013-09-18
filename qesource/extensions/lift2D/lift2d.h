/******************************************
 ** Header file for 2D lifting extensions
 ******************************************/
#ifndef _LIFT2D_
#define _LIFT2D_

#include "qepcad.h"

/** Somehow FPCATCH is not in the saclib prototypes! **/
#ifdef __cplusplus
extern "C" {
  void FPCATCH();
}
#else
void FPCATCH();
#endif

Word CELLLEFTSIB(Word c, Word D);
Word CELLRIGHTSIB(Word c, Word D);
Word CELLSRDQ2D(Word c, Word P, Word *Q_);
Word CELLSRRQ2D(Word c, Word P);
void IBPELBRISIPR(Word A, Word I, BDigit p, BDigit *B);
void IBPESISIPR(Word A, BDigit *I, BDigit p, BDigit *B);
void IBPRRIOAP(Word M,Word I,Word B,Word k, Word *L_,BDigit *t_);
void IBPRRIOAPSF(Word M, Word I, Word B, BDigit p,BDigit k, Word *J_, Word *L_);
void IBPRRIOAPSF(Word M, Word I, Word B, BDigit p, BDigit k, Word *J_, Word *L_);
Word PPDLT(Word p, Word i, Word pt);
Word LIFT3DTEST(Word c, Word D, Word P, Word J);
Word LIFT2DNEW(Word c, Word D, Word P);
Word IUPIIRSF(Word M, Word I, BDigit p);
Word LIFTSRD2D(Word c, Word D, Word P, Word L);
Word LIFTSRR2D(Word c, Word D, Word P);
Word PFSRDQ2D(Word p,Word *L_);
Word PFSRRQ2D(Word p,Word *L_);
void modHIPRRID(BDigit n,interval *A, Word *L_,BDigit *t_);
void SIPWRITE(Word *P, BDigit p, BDigit k);
void modHIPRRID(BDigit n, interval *A, Word *L_, BDigit *t_);
Word modHIPRRISD(BDigit n, interval *A, Word a, Word b);
void modIBPRRIOAP(Word M, Word I, Word B, Word k, Word *L_, BDigit *t_);
void modIBPRRIOAPSF(Word M, Word I, Word B, Word p, Word k, BDigit *J_, BDigit *L_);
Word modSIPRRID(BDigit *A);
Word modSIPRRISD(BDigit *A, Word a, Word b);

#endif /* _LIFT2D_ */
