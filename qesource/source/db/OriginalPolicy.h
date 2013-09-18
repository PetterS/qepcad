/***************************************************************
 * This is Hoon's original policy, which uses his "database" and
 * the PCRESALG variable.
 ***************************************************************/
#ifndef _ORIGINAL_POLICY_
#define _ORIGINAL_POLICY_
#include "db/CAPolicy.h"

class OriginalPolicy : public CAPolicy
{
public:
  virtual void IPFAC(Word r, Word P, Word *s_, Word *c_, Word *L_)
  {
    Word L,c,s;
    /* hide s; */
Step1: /* Process. */
    if (PCDBUSE == 'n')
    {
      IPFAC(r,P,&s,&c,&L);
      goto Return;
    }
    if (DBSRCH(DBIPFAC,LIST2(r,P)) == 0)
    {
      ::IPFAC(r,P,&s,&c,&L);
      DBADD(DBIPFAC,LIST2(r,P),LIST3(s,c,L),&DBIPFAC);
    }
    else
      FIRST3(DBINFO,&s,&c,&L);
    goto Return;
    
  Return: /* Prepare for return. */
    *s_ = s;
    *c_ = c;
    *L_ = L;
    return;
  }

  virtual Word IPRES(Word r, Word A, Word B)
  {
    Word R;
    
Step1: /* Determine method to use. */
    switch (PCRESALG) {
    case MODULAR: R = ::IPRES(r,A,B); break;
    case SUBRES:  R = IPRESPRS(r,A,B); break; 
    case BEZOUT:  R = IPRESBEZ(r,A,B); break; }
    
  Return: /* Prepare for return. */
    return(R);
  }

  virtual Word IPDSCR(Word r, Word A)
  {
    Word D;
    
  Step1: /* Determine method to use. */
    switch (PCRESALG) {
    case MODULAR: D = ::IPDSCR(r,A); break;
    case SUBRES:  D = IPDSCRPRS(r,A); break; 
    case BEZOUT:  D = IPDSCRBEZ(r,A); break; }
    
  Return: /* Prepare for return. */
    return(D);
  }
  
  virtual const string name() { return "OriginalPolicy"; }
  bool supports(const string &s)
  {
    return s == "IPFAC" || s == "IPRES" || s == "IPDSCR";
  }

};

#endif
