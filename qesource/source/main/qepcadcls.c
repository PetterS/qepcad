#include "qepcad.h"

void QepcadCls::SETINPUTFORMULA(Word V, Word Fs)
{
  /* Set input-related variables */
  GVVL = V;
  GVF = Fs;
  FIRST4(Fs,&(GVNV.W),&(GVNFV.W),&(GVQ.W),&(GVQFF.W));
  
  /* Set default projection operator to modified McCallum */
  PCPROJOP = NIL;
  for (int k = GVNV; k >= 2; k--)
    PCPROJOP = COMP('p',PCPROJOP);
}

QepcadCls::QepcadCls(Word V, Word Fs)
{
  INITGLOBALS();
  INITSTATS();
  SETINPUTFORMULA(V,Fs);
}

void QepcadCls::SETASSUMPTIONS(Word F)
{
  Word Fp = CHANGEASSUMPTIONSLEVEL(F,GVNFV,1);
  if (Fp == TRUE || Fp == UNDET) return;
  GVUA = Fp;
}

Word QepcadCls::GETDEFININGFORMULA(char opt)
{
  Word SF;
  switch(opt)
  {
  case 'T': /* Tarski formula */
    SF = SFC3f(GVPC,GVPF,GVPJ,GVNFV,LIST10(0,0,0,1,0,3,2,4,1,5));
    break;
  case 'E': /* Extended Language Formula */
    SF = SFC3f(GVPC,GVPF,GVPJ,GVNFV,CCONC(LIST10(1,0,0,1,0,3,2,4,1,5),LIST1(-1)));
    break;
  case 'F': /* Full Dim only Formula */
    SF = SFCFULLDf(GVPC,GVPF,GVPJ,GVNFV);
    break;
  default:
    FAIL("GETDEFININGFORMULA","Error!  Unknown option!\n");
    break;
  }
  Word SFp = FMA2QUNF(SF,GVPF);
  return SFp;
}
