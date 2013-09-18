#include "qepcad.h"
#include "../../extensions/lift2D/lift2d.h"

class QepcadCls2D : public QepcadCls
{
public:
  QepcadCls2D(Word V, Word Fs) : QepcadCls(V,Fs) { }
  void CAD2D(Word Fs, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_);
  void CONSTRUCT(Word c,Word k,Word f,Word Ps_,Word As);
  void PROJECT(Word r, Word A,Word *P_, Word *J_);
  Word TICAD(Word Q,Word F,Word f,Word P,Word A);
};

void PRINTCAD2DBANNER();

