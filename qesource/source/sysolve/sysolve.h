#ifndef _SYSOLVE_HEADER_
#define _SYSOLVE_HEADER_

Word ASSUMPTIONSRATVEVAL(Word A, BDigit i, Word R, BDigit r);
Word CHANGEASSUMPTIONSLEVEL(Word A, BDigit r, BDigit necflag);
Word COEFSYS(BDigit r, Word A);
Word EVALSYS(Word S, BDigit t, Word R);
void FINDRATCOORD(Word S, Word* t_, Word *R_, Word *P_);
Word IPRSOL(BDigit r, Word P);
Word LBMIPL(Word L, BDigit r);
Word LOSETSBF(Word S, BDigit r);
Word LPSILB(BDigit r, Word S);
void PRINTCOEFFSYS(BDigit r, Word S, Word Vp = 0);
Word SIMPLIFYSYS(BDigit r, Word S, Word RC, Word A);
Word SIMPLIFYSYSLIST(BDigit r, Word L, Word A);
Word SYSSOLVECAD(BDigit r, Word L, Word A, Word Vp, QepcadCls &Q);
Word SYSTOUNNORMFORMULA(BDigit r, Word L);
BDigit VERIFYCONSTSIGN(BDigit r, Word P, BDigit s, Word A = 1);

#endif
