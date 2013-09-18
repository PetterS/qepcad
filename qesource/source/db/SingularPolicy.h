#ifndef _SINGULAR_POLICY_
#define _SINGULAR_POLICY_
#include "db/CAPolicy.h"
#include "db/SINGULAR.h"

class SingularPolicy : public CAPolicy
{
public:
  void IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_)
  {
    GVSB["Singular"]->IPFAC(r,P,s_,c_,L_);
  }

  Word IPRES(Word r, Word A, Word B)
  {
    return GVSB["Singular"]->IPRES(r,A,B);
  }

  Word IPDSCR(Word r, Word A)
  {
    return GVSB["Singular"]->IPDSCR(r,A);
  }

  Word IPFACTGB(Word r, Word I, Word N)  
  {
    return GVSB["Singular"]->IPFACTGB(r,I,N);
  }
  Word CONSTORDTEST(Word r, Word A, Word L) 
  {
    return GVSB["Singular"]->CONSTORDTEST(r,A,L);
  }
  const string name() { return "SingularPolicy"; }

  bool supports(const string &s)
  {
    return s == "IPFAC" || s == "IPRES" || s == "IPDSCR" || s == "IPFACTGB" || s == "CONSTORDTEST"; 
  }
};

#endif
