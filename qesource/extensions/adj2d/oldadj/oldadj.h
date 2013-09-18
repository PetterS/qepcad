#ifndef _OLDADJ2D_HEADER_
#define _OLDADJ2D_HEADER_

#include "adj2D.h"
#include "sac_ext/sac_ext.h"

Word ASYS1(Word M, Word H, Word I, Word P2, Word c_l, Word c_r);
Word ASYS2(Word M, Word H, Word I, Word P2);
Word SPRLC(Word c);
Word DNCAC(Word e, Word I, Word P);
Word LLBRSPFSS(Word c);
Word LLSISS(Word c);
Word RIIFACMA(Word I, Word A, Word t, Word P, Word J, Word K);
Word RIIFACMABR(Word P, Word J, Word K, Word *H, Word *I);

#endif
