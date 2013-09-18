/*======================================================================
                             IEEENEIGH(F,d; F',t)

IEEE neighbor.

Inputs
    F : An IEEE double.
    d : -1 or +1.

Outputs
   F' : An IEEE double.  F' is the IEEE double that neighbors F in
        the positive or negative direction, according to whether d
        is positive or negative.
   t :  If t = 0, overflow or underflow occurred and F' is undefined.
======================================================================*/
#include "saclib.h"

void IEEENEIGH(F,d,Fp_,t_)
	ieee F;
        BDigit d;
        ieee *Fp_;
	BDigit *t_;
{
        BDigit s,e,a1,a0,sp,ep,ap1,ap0,t;
        ieee Fp;

Step1: /* Unpack. */
       e = F.rep.exp;
       a0 = F.rep.mant_l;
       a1 = F.rep.mant_h;
       if (F.rep.sign == 0) 
          s = 1; 
       else
          s = -1; 

Step2: /* F = 0. */
       if (e == 0 && a1 == 0 && a0 == 0) {
          ep = 0;
          ap1 = 0;
          ap0 = 1;
          if (d == -1)
             sp = 1;
          else
             sp = 0;
          goto Return; }
       sp = F.rep.sign; 
       if (s != d)
          goto Step4;

Step3: /* Away from zero. */
       if (a1 == 0xFFFFF && a0 == 0XFFFFFFFF) {
          if (e - BIAS == MAXEXP) {
             t = 0;
	     goto Return; }
          else {
             ap1 = 0;
             ap0 = 0;
             ep = e + 1; } }
       else if (a0 == 0xFFFFFFFF) {
          ap0 = 0;
          ap1 = a1+1;
          ep = e; }
       else {
          ap0 = a0 + 1; 
          ap1 = a1;
          ep = e; }
       goto Step5;

Step4: /* Towards zero. */
       if (a1 == 0 && a0 == 0) {
          if (e - BIAS == MINEXP) {
             t = 0;
	     goto Return; }
          else {
            ap0 = 0xFFFFFFFF;
            ap1 = 0xFFFFF;
            ep = F.rep.exp - 1; } }
       else if (a0 == 0) {
          ap0 = 0xFFFFFFFF;
          ap1 = a1 - 1;
          ep = F.rep.exp; }
       else {
          ap0 = a0 - 1;
          ap1 = a1;
          ep = e; }

Step5: /* Compose F'. */
        Fp.rep.sign = sp;
        Fp.rep.exp = ep;
        Fp.rep.mant_l = ap0;
        Fp.rep.mant_h = ap1;
	t = 1;

Return: /* Return F' and u. */
	*Fp_ = Fp;
	*t_ = t;
	return;
}
