#ifndef _SAC_EXT_HEADER_
#define _SAC_EXT_HEADER_

#include "qepcad.h"

Word ADJNNA(Word P, Word i1, Word i2, Word j, Word A, Word k1, Word k2);
Word IBPIDFV(Word P);
Word IPLBREVAL(Word r, Word A, Word a);
Word IPLBRLUPEVAL(Word r, Word A, Word a);
Word IPMP2(Word r, Word A, Word h);
Word IPRRILBRI(Word A, Word I);
Word IUPLBREVAL(Word A, Word a);
Word IUPSOPOR(Word A, Word B, Word i1, Word i2);
Word IUPSOPOR(Word A, Word B, Word i1, Word i2);
Word IUPSOPORFIL(Word A, Word B, Word R);
Word IUPTSII(Word A, Word I);
Word LBRNMAX(Word a, Word b);
Word LBRNMIN(Word a, Word b);
Word PCFE(Word A, Word k);
Word RRCOMPSRI(Word A, Word i1, Word i2, Word B, Word j1, Word j2, Word *i1s, Word *i2s, Word *j1s, Word *j2s);
Word RRLBRNCOMP(Word A, Word I, Word j, Word t);
void ANCOMPSRI(Word M, Word N, Word f, Word I_, Word J_, Word *c_, Word *i1s, Word *i2s, Word *j1s, Word *j2s);

#endif
