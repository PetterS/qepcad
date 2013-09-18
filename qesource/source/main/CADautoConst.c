/*======================================================================
                      CADautoConst(Word Fs)

CAD Atuomatic (i.e. non-interactive) Construction

NOTE:  Assumes the QepcadCAD already has all the relvent fields
       initialized - i.e. GVF, etc.

Side Effects
This is a member function of a QepcadCls object.  Calling this function
actually constructs the CAD data structure associated to the object.
What gets constructed is a CAD for the formula Fs.  If the GVUA has
been set to something other than NIL, those assumptions are used.
======================================================================*/
#include "qepcad.h"

void QepcadCls::CADautoConst()
{
       Word A,D,F,F_e,F_n,F_s,Fh,J,P,Q,Ths,f,i,r,t, T;
       /* hide Ths,i,t; */
       Word cL,**cC,cr,ce,ci,*cT,cj,cs,cl,ct; /* Chris variables. */
       Word Cs,Ps,Qs,Pps,Cps,Qps,SF; /* Chris variables. */
       char c1,c2; /* Chris variables. */

Step1: /* Normalize. */
       FIRST4(GVF,&r,&f,&Q,&Fh);
       F = NORMQFF(Fh);
       if (GVUA != NIL) GVNA = NORMQFF(GVUA);
       GVNQFF = F;
       if (TYPEQFF(F) != UNDET) { goto Return; }

Step2: /* Projection. */
       if (GVUA != NIL) F = LIST3(ANDOP,GVNA,F);
       A = EXTRACT(r,F);
       if (GVUA != NIL) {
	 GVNA = SECOND(F);
	 F = THIRD(F); }
       GVNIP = A;
       GVPF = LLCOPY(A);
       GVLV = r;
       PROJECTauto(r,A,&P,&J);

Step3: /* Truth-invariant CAD. */
       D = TICADauto(Q,F,f,P,A);

Return: /* Prepare for return. */
       return;
}
