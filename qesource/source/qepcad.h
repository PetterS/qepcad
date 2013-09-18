/*=======================================================
                    qepcad.h                                        
========================================================*/
#ifndef QEPCAD_H
#define QEPCAD_H
#include <stdio.h>
#include <string>
using namespace std;

/*-- Saclib is a C library, so we need C-style linkage --*/
extern "C" {
#include "saclib.h"
}

/*-- Other system headers -------------------------------*/
#include "saclib/replacesac.h"
#include "saclib/gcword.h"
#include "main/qepcadcls.h"

/* ----------------------------------------*/
/*            Algorithms                   */
/* ----------------------------------------*/
#include "sysolve/sysolve.h"
Word ADJ2(Word C);
Word ADJ2SL(Word n, Word s, Word N, Word S, Word L);
void ADJINFOWR();
void AFCSBM(Word M, Word A, Word *B_, Word *G_);
void AFCSBMDB(Word M, Word Ps, Word *Bs_, Word *Es_);
void AFLWR(Word M, Word I, Word N, Word a, Word A, Word d);
void AFMSBM(Word M, Word A, Word B, Word *C_, Word *E_, Word *F_);
void AFPDWR(Word r, Word A, Word V, Word N);
void AFWR(Word A, Word a);
Word AFPNIPDB(Word Mb, Word B);
void AFUPGCDB(Word M, Word A, Word B, Word *C_, Word *Ab_, Word *Bb_);
void AFUPLM(Word M, Word A, Word *L_, Word *P_);
void AFUPRWR(Word a, Word v, Word A, Word I);
Word AFUPSFNDB(Word M, Word B, Word *t_, Word *Bt_, Word *F_);
Word APPEND(Word P, Word k, Word R);
void APPENDEC(Word P, Word k, Word R, Word *Ps_, Word *F_);
void ATOMFLWR(Word N, Word V, Word A);
void ATOMFRDR(Word V, Word *F_, Word *t_);
void ATOMFWR(Word V, Word A);
void BEGINQEPCAD(int &argc, char**& argv);
Word CAPTURE(Word P, Word M);
Word CATOMQFF(Word F);
void CATTRNRDR(Word *V_, Word *t_);
void CATTRNWR(Word A);
Word CELLATTR(Word c, Word A);
Word CELLCOMP(Word c1, Word c2, Word S);
Word CELLDEG(Word c);
Word CELLDIM(Word c);
void CELLFIDX(Word x, Word c, Word *cp_, Word *t_);
Word CELLNA(Word I, Word D);
void CELLRDR(Word D, Word *c_, Word *t_);
Word CHKCONS( Word n, Word s, Word N, Word S, Word L, Word a, Word *sp_, Word *Np_, Word *Sp_, Word *Lp_);
void CHSCN(Word M, Word I, Word N, Word J, Word t, Word S, Word *S1_, Word *K1_);
Word COMMNT();
void COMMNTRD();
Word CONVERT(Word s, Word k);
void CONWR(Word V, Word C);
Word CSSP(Word a, Word b);
Word CVCOMP(Word c1, Word c2);
void DBADD(Word D, Word K, Word C, Word *Dp_);
Word DBSRCH(Word D, Word K);
void DBSTATWR(Word D, Word M);
Word DELINPOL(Word k, Word A, Word M, Word b);
Word DELINPOLR(Word k, Word A, Word b);
Word DESCENDANT(Word c, Word x, Word kp);
void DESIREDRDR(Word *F_, Word *t_);
void DESIREDWR(Word C);
void DIELOC();
Word DIFTMUL(Word N1, Word N2);
void DISCONWR(Word V, Word F);
Word DMAFUPNR(Word p,Word M,Word A,Word B);
void DNFWR(Word V, Word F);
void DNFLPWR(Word N, Word V, Word F);
void DNFLWR(Word N, Word V, Word F);
Word DSCOMP(Word c1, Word c2);
void EC(Word c, Word L, Word E, Word Bs);
void EC1(Word c, Word L, Word Bs);
void EC2CWF(Word P,Word t,Word *F_e,Word *F_n,Word *F_s);
Word ECLEVEL(Word L);
void ECR(Word c, Word L, Word E, Word Bs);
void ENDQEPCAD();
void ESPIWR(Word T1, Word T0);
Word ESPORD();
Word ESPRESSO(Word T_t, Word T_f);
Word EXPAFEQ(Word L);
Word EXPAFGT(Word L);
Word EXPAFGTS(Word L);
Word EXPAFLT(Word L);
Word EXPAFLTS(Word L);
Word EXTRACT(Word r, Word F);
void EXTRACTS(Word F, Word A, Word *Ap_);
void FGWRITE(Word A, Word n);
void FILINE();
void FILLIN(Word n, Word vs, Word S_r, Word S_s, Word R_c, Word R_s, Word *v_);
void FIRSTCOMB(Word n, Word r, Word *R_);
void FIRSTLEXI(Word l, Word *R_);
void FIRSTPRD(Word n, Word *v_, Word *S_r_, Word *S_s_, Word *R_c_, Word *R_s_);
void FNDTS(Word M, Word N, Word *t_, Word *S_, Word *U_);
void FNDTSDB(Word Mb, Word Nb, Word *t_, Word *S_, Word *U_);
void FPSIGTBL(Word c, Word f, Word T_t, Word T_f, Word *Tp_t_, Word *Tp_f_);
void FREADR(Word V, Word f, Word *Fs_, Word *t_);
void FSIGTBL(Word c, Word f, Word T_t, Word T_f, Word *Tp_t_, Word *Tp_f_);
void FWRITE(Word V, Word Fs);
void GADJINF(Word c, Word *S_, Word *Ns_, Word *s_, Word *n_);
Word GENPIMP(Word H_t, Word H_f);
void GETRP(Word S1, Word t, Word U, Word *Ms_, Word *Ns_);
void GETRPDB(Word S1, Word t, Word U, Word *Ms_, Word *Ns_);
Word GETWORD();
void GREADR(Word *a_, Word *t_);
Word GROUPSAMEPJ(Word r, Word J);
void HELPFRD();
void HELPWR(Word I);
void INITCTRL();
void INITDB();
void INITIO();
void INITSTAT();
void INITSYS();
void INPUTRD(Word *Fs_, Word *V_);
Word IPDSCRQE(Word r,Word A);
Word IPFZT(Word r, Word A);
Word IPRESQE(Word r,Word A,Word B);
Word IPALLPARTIALS(Word k, Word P, Word t, Word m);
Word IPDSCRPRS(Word r, Word A);
void IPFACDB(Word r, Word P, Word *s_, Word *c_, Word *L_);
void IPFSBM(Word r, Word A, Word *B_, Word *G_);
Word IPFZT1(Word r, Word A);
void IPLDWR(Word V, Word A);
Word IPLFAC(Word k, Word J);
void IPLLDWR(Word V, Word A);
void IPLLDWRMOD(Word V, Word A);
void IPLSRP(Word A, Word *s_, Word *P_);
Word IPRESPRS(Word r, Word A, Word B);
Word IPRNEVAL(BDigit r, Word P, BDigit t, Word b);
Word ISATOMF(Word F);
Word ISDESIRED(Word c, Word C);
Word ISNULL(Word L);
Word ISPRIMIT(Word s);
void IUPRWR(Word v, Word A, Word I);
Word IXCOMP(Word c1, Word c2);
void LABELWR(Word N, Word I);
Word LCM(Word L, Word M);
void LGOPRDR(Word *p_, Word *t_);
void LGOPWR(Word p);
Word LOAR(Word k, Word Q, Word F);
Word LPFTOLRLP(Word r, Word L);
Word LPFZCALL(Word c, Word P, Word D);
Word LUNION(Word L1, Word L2);
Word LVCOMP(Word c1, Word c2);
Word MAFDIF(Word p,Word a,Word b);
Word MAFHOM(Word p,Word M,Word a);
Word MAFINV(Word p,Word M,Word a);
Word MAFPROD(Word p,Word M,Word a,Word b);
Word MAFUPDIF(Word p,Word A,Word B);
Word MAFUPEPROD(Word p,Word M,Word a,Word A);
Word MAFUPGCD(Word p,Word M,Word A,Word B);
Word MAFUPMON(Word p, Word M, Word A);
Word MAFUPNR(Word p, Word M, Word A, Word B);
Word MATCHWORD(Word A, Word B);
Word MBPROD(Word A, Word B);
Word MCELL(Word a1, Word a2, Word a3, Word a4, Word a5, Word a6, Word a7, Word a8, Word a9, Word a10);
Word MKMUL(Word E, Word k);
Word MMFLR(Word L);
void MODCR(Word b, Word G, Word Ms, Word Ns, Word *bs_);
void MODCRDB(Word b, Word S1, Word Ms, Word Ns, Word *b1_);
Word MPOLY(Word a1, Word a2, Word a3, Word a4, Word a5);
Word MUPNR(Word p,Word A,Word B);
Word MVLMA(Word H_t, Word H_f);
Word MVLMASF(Word H_t, Word H_f);
Word NEGRLOP(Word T);
void NEXTCELL(Word D, Word c, Word *cp_, Word *t_);
void NEXTCOMB(Word n, Word r, Word Rs, Word *R_, Word *q_);
void NEXTLEXI(Word l, Word Rs, Word *R_, Word *q_);
void NEXTPRD(Word n, Word vs, Word Ss_r, Word Ss_s, 
			   Word Rs_c, Word Rs_s, Word *v_, 
			   Word *S_r_, Word *S_s_, 
			   Word *R_c_, Word *R_s_, Word *q_);
Word NORMAF(Word A);
Word NORMAFS(Word Fh);
Word NORMAL(Word s);
Word NORMQFF(Word Fh);
Word NQFFAND(Word F, Word G);
Word NQFFOR(Word F, Word G);
void OUTPUTWR(Word t, Word F_e, Word F_n, Word F_s, Word V);
void PARENTWR(Word P);
void PCADWR(Word c);
void PCADSWR(Word c);
Word PFCOICQ(Word r, Word A, Word c, Word P, Word D);
Word PFPRDQ(Word P);
void PIMPTBLWR(Word C, Word R, Word V);
void PLABELWR(Word P);
Word PLDEG(Word P);
Word PLPOS(Word P, Word i);
Word PPPRDQ(Word P);
void PQFF(Word F, Word L, Word *Lp_);
void PRDADJINFO();
void PRDCC();
Word PRDLEN(Word A);
void PRDTRACEA();
void PRDTRACED();
void PRESPFWR();
void PRESPPWR();
void PRHELP(Word W);
void PRIGS();
void PRINTBANNER();
void PRLDB();
void PRODWR(Word v);
void PROMPT();
void PROPAGATE(Word D, Word c, Word k, Word f, Word Q);
void PRQUIT();
void PRTRACEA();
void PRTRACED();
void PRUDB();
void PRWHATIS();
void PSIGTBL(Word c, Word f, Word T_t, Word T_f, Word *Tp_t_, Word *Tp_f_);
void PSIMREP(Word r, Word P, Word *rs_, Word *Ps_);
void QEGLOBALS();
const char* QEPCADBVersion();
Word QFFFSOP(Word H, Word P, Word f);
void QFFLPWR(Word N, Word V, Word F);
void QFFLWR(Word N, Word V, Word F);
void QFFRDR(Word V, Word *F_, Word *t_);
void QFFWR(Word V, Word F);
bool qfrCheckNonVanishing(BDigit r, Word P, Word A, Word F, Word V);
bool qfrCheckNonNullified(BDigit r, Word P, Word A, Word F, Word V);
void QFRDR(Word *q_, Word *t_);
void QFWR(Word q);
Word RCFAFC(Word b);
Word REPLACE(Word f, Word F, Word Fp);
void RLOPRDR(Word *p_, Word *t_);
void RLOPWR(Word p);
Word RMCAFS(Word F);
Word RMCAON(Word F);
Word RMCONS(Word r, Word J);
Word RMLREOP(Word F);
Word RMMPF(Word P, Word k);
Word RMMPJ(Word J, Word k);
Word RMNOTOP(Word F);
Word RMNOTOPN(Word F);
Word RNFAF(Word a);
Word RVSPTSVSP(BDigit r, Word P, BDigit s);
void SALGF(Word f, Word F, Word *G_, Word *H_);
void SAMPLEWR(Word r, Word s, Word PCNUMDEC);
Word SELPIMP(Word m, Word V);
void SEPLAB(Word k, Word C, Word *Cb_, Word *Ch_);
void SETUPSYS();
Word SIGNB(Word B, Word I);
Word SIGNL(Word c, Word L);
void SIGNLWR(Word x);
void SIGNP(Word c, Word k, Word B, Word I, Word E, Word L);
void SIGNP1(Word c, Word P1, Word I);
void SIGNPR(Word c, Word k, Word B, Word I, Word E, Word s);
void SIGNWR(Word s);
Word SIGSUB(Word A, Word B);
void SIGTBL(Word c, Word f, Word T_t, Word T_f, Word *Tp_t_, Word *Tp_f_);
Word SIMPLE(Word s);
void SIMPLEQE(Word A, Word I, Word B, Word J, Word *G_, Word *s_, Word *t_, Word *K_, Word *a_, Word *b_, Word *T1_, Word *T2_);
Word SIMPLIFY(Word T_t, Word T_f, Word F, Word P, Word f);
void SOLUTION(Word D, Word F, Word P, Word f, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_);
Word SOPFST(Word T);
Word SOSRSUBS(Word L);
Word SOSRSUPS(Word L);
void SPFRPSFT(Word P, Word c, Word k, Word *R_, Word *F_);
Word SSCOMP(Word c1, Word c2);
Word STACKMULT(Word C);
void STACKMWR(Word M);
Word STFSOP(Word H);
BDigit SUBSET(Word A, Word B);
Word SUBSTDB(Word c, Word k, Word M, Word b, Word B, QepcadCls &Q);
Word SVPOWR(Word A, Word G);
Word SVPROD(Word A, Word B);
void TAB(Word n);
void TCHILD(Word c, Word *A1_, Word *A0_, Word *E1_, Word *E0_);
Word TCHILD4C(Word c);
Word TCHILD4FDE(Word c);
Word TCHILD4FDA(Word c);
Word TCHILD4EXk(Word c, Word k);
void TREPIMP(Word rh, Word Vh);
void TREPROJ(Word k, Word P_k);
void TRMODEWR(Word M);
void TRPC(Word c);
void TRPIMP(Word v, Word T);
void TRPIMPTBL(Word C, Word R, Word V);
void TRPROD(Word v);
void TRUTHWR(Word t);
void TRXPROJ(Word Ths, Word k, Word P_k, Word J);
Word TYPEAF(Word A);
Word TYPEQFF(Word F);
Word VALIDLBL(Word L, Word P);
void VLREADR(Word *V_, Word *t_);
void VREADR(Word *v_, Word *t_);
void VWRITE(Word v);
void XREADR(Word *L_, Word *t_);
Word IPALLPARTIALS(Word k, Word P, Word t, Word m);
Word PFPRDQ(Word P);
Word PPPRDQ(Word P);
Word DELINPOL(Word k, Word A, Word M, Word b);
Word DELINPOLR(Word k, Word A, Word b);
void KTHSECTIONTRUE(Word c, Word j, Word k, Word op, Word i);
void SETTRUTHVALUE(Word t, Word I, Word c);


/* -----------------------------------------------*/
/*             Basic constants                    */
/* -----------------------------------------------*/

/* Strict Relational Operators */
#define LTOP   1
#define EQOP   2
#define GTOP   4

/* Other Relational Operators */
#define GEOP   6
#define NEOP   5
#define LEOP   3
      
/* Other Extended Relational Operators */
#define CDOP   0
#define TAOP   7

/* Indexed root */
#define IROOT  101
  
/* Logical Operators */
#define ANDOP     11
#define OROP      12
#define NOTOP     13
#define RIGHTOP   14
#define LEFTOP    15
#define EQUIOP    16

/* Quantifiers */
#define UNIVER    20
#define EXIST     21
#define CONTQ     22
#define FULLDE    23
#define FULLDA    24
#define EXISTk    25

/* Truth values */
#define TRUE    1
#define FALSE   0
#define UNDET   2
#define NA      3 /* This is for cells in free-variable space that contradict assumptions! */

/* Truth Determination Mechanisms */
#define BYTEV   0
#define BYPRP   1
#define BYEQC   2
#define TOPINF  3
#define MANSET  4
#define NOTDET  5

/* Sign */
#define POSITIVE    1
#define ZERO        0
#define NEGATIVE   -1

/* Solution Flag */
#define EQU      1
#define INEQU    0
      
/* Return Flag */
#define OK      1
#define ERROR   0
      
/* Cell */
#define LEVEL      1     /* If you change this, update MCELL also. */
#define CHILD      2
#define ASSIGNED   3
#define TRUTH      4
#define SAMPLE     5
#define INDX       6
#define SIGNPF     7
#define HOWTV      8
#define DEGSUB     9
#define MULSUB     10
      
/* Partial Orderings */
#define HLORD      1
#define LLORD      2
#define GIORD      3
#define LIORD      4
#define SRORD      5
#define SNORD      6
#define TCORD      7
#define NCORD      8
#define GDORD      9
#define LDORD      10

/* Cell attribute IDs */
#define CALEVEL      -1
#define CADIMENSION  -2
#define CADEGREE     -3
#define CALCINDEX    -4
#define CAPARITY     -5

#define CAINDEX0     -1000  /* All the value below this is reserved for 
                               index(i). */


/* Polynomial attributes */
#define PO_POLY       1     /* If you change this, update MPOLY also. */
#define PO_LABEL      2
#define PO_PARENT     3
#define PO_TYPE       4
#define PO_STATUS     5

#define PO_RES        10
#define PO_DIS        11
#define PO_LCO        12
#define PO_TCO        13
#define PO_FAC        14
#define PO_DER        15
#define PT_NUL        16
#define PT_PRJ        17
#define PT_DEL        18

#define PO_REMOVE     0
#define PO_KEEP       1

#define PO_ECON       1
#define PO_OTHER      2
#define PO_POINT      3

/* Resultant structure. */
#define RES_PO_1      4
#define RES_PO_2      6

/* Algorithm to use for resultant and discriminant computations. */
#define MODULAR       1
#define SUBRES        2
#define BEZOUT        3


/* -----------------------------------------------------------------------*/
/*                              Macros                                    */
/* -----------------------------------------------------------------------*/ 
#define LBLINDEX(L)    THIRD(L)                       /* ??? */
#define LBLLEVEL(L)    SECOND(L)                      /* ??? */
#define MKLABEL(a,b,c)  LIST3(LFS(a),(b),(c))         /* ??? */
#define SIGINS(A,B)     USINT((A),(B))



/* -----------------------------------------------------------------------*/
/*                              Data-bases                                */
/* -----------------------------------------------------------------------*/ 
extern Word DBAFCSBM;      /* Database for AFCSBM */   
extern Word DBAFPNIP;      /* Database for AFPNIP */
extern Word DBAFUPGC;      /* Database for AFUPGC */
extern Word DBAFUPSFN;     /* Database for AFUPSFN */
extern Word DBFNDTS;       /* Database for FNDTS */
extern Word DBGETRP;       /* Database for GETRP */
extern Word DBMODCR;       /* Database for MODCR */
extern Word DBIPFAC;       /* Database for IPFAC */
extern Word DBSUBST;       /* Database for SUBST. */

extern Word DBTIME;        /* Atcuall computation begin time */
extern Word DBINFO;        /* Info of the item found */


/* ------------------------------------------------------------------------*/
/*                              Commmand                                   */
/* ------------------------------------------------------------------------*/
extern Word COMMANDS;     /* Holds Info about commands */
extern Word COMCLASS;     /* Holds command classifications and descriptions. */


/* ------------------------------------------------------------------------*/
/*                          Intermediate results                           */
/* ------------------------------------------------------------------------*/
extern Word GVMCOMM;      /* Main comment */

/* ------------------------------------------------------------------------*/
/*                    Algorithm  trace control                             */
/* ------------------------------------------------------------------------*/
extern Word TCPROJ;   /* Projection Operation */
extern Word TCIPLFAC; /* Complete Factorization */

/* ------------------------------------------------------------------------*/
/*                    Data trace control                                   */
/* ------------------------------------------------------------------------*/
extern Word TCPC;      /* Partial CAD */
extern Word TCPROD;    /* Product generated */
extern Word TCPIMP;    /* Prime Implicant */
extern Word TCPIMPTBL; /* Prime Implicant Table */
extern Word TCEPIMP;   /* Essential Prime Implicant */ 
extern Word TCSTAT;    /* Statistics at the end */
extern Word TCDSTAT;   /* Dissertation statistics at the end */
extern Word PCIPFZT;   /* 'y' if IPFZT is turned on, 'n' otherise. */
extern Word PCVERBOSE;/* Verbose mode: 0 means not verbose, 1 means verbose 06/19/02 */


/* ------------------------------------------------------------------------*/
/*                       Program control                                   */
/* ------------------------------------------------------------------------*/
extern int experimentalExtensionFlag;
extern  Word PCIGS;       /* Implicant Generation Strategy */
extern  Word PCDBUSE;     /* 'y' if Databases are used 'n' otherwise */
extern  Word PCDBLIMIT;   /* Limit for Database Entry */
extern  Word PCRESALG;    /* Choice of resultant algorithm. */
extern  Word PCCONTINUE;   /* Flag to show that the "continue" command has been issued. */

/* ------------------------------------------------------------------------*/
/*                              Statistics                                 */
/* ------------------------------------------------------------------------*/
#define MNV    30  /* Maximum Number of Variables = 30 */
#define MNV1   31  /* One more for C arrary. */

/* Statictics on QEPCAD */
extern Word BTMQEPCAD;     /* Time at which QECAD was called */

/* Statistics on Normalization Phase */
extern Word TMNORMQFF;     /* Time for Normalization Phase, NORMQFF */

/* Statistics on Projection Phase */
extern Word TMPROJECT[MNV1];   /* Time for Projection Phase, PROJECT */
extern Word   TMPROJ[MNV1];       /* Time for Projection Operation,  PROJ */
extern Word     TMIPFZT[MNV1];      /* Time for Finite Zero Test, IPFZT */
extern Word   TMIPLFAC[MNV1];     /* Time for Complete Factorization, IPLFAC */
extern Word   TMAPPEND[MNV1];     /* Time for Appending, APPEND */

/* Statistics on Truth Invariant CAD Construction Phase */
extern Word TMTICAD[MNV1];     /* Time for Truth invariant CAD Construnction Phase, TICAD */
extern Word   TMCHOOSE[MNV1];    /* Time for Choosing a cell, CHOOSE */
extern Word   TMCONVERT[MNV1];   /* Time for Conversion, CONVERT */
extern Word     TMTCN[MNV1];       /* Time for Trivial Conversion */
extern Word     TMNORMAL[MNV1];    /* Time for NORMAL, NORMAL */
extern Word     TMSIMPLE[MNV1];    /* Time for SIMPLE, SIMPLE */
extern Word   TMCONSTRUCT[MNV1]; /* Time for stack construction, CONSTRUCT */
extern Word     TMSUBST[MNV1];     /* Time for substituting on irrational sample point, SUBST */
extern Word     TMAFUPLM[MNV1];    /* Time for computing ldcf and monic associates, AFUPLM */
extern Word     TMAFCSBM[MNV1];    /* Time for computing coarsest squarefree basis, AFCSBM */
extern Word     TMAFUPBRI[MNV1];    /* Time for isolating real roots of algebraic polynomials using AFUPBRI.*/
extern Word     TMAFUPHIBRI[MNV1];    /* Time for isolating real roots of algebraic polynomials using AFUPHIBRI.*/
extern Word     TMAFUPSIBRI[MNV1];    /* Time for isolating real roots of algebraic polynomials using AFUPSIBRI.*/

extern Word     TMEC[MNV1];        /* Time for establishing children on irration, EC */
extern Word     TMSIGNP[MNV1];     /* Time for computing projection signatures, SIGNP */
extern Word     TMRCFAFC[MNV1];    /* Time for converting to rational polynomials, RCFAFC */
extern Word     TMSUBSTR[MNV1];    /* Time for substituting on rational sample point, SUBSTR */
extern Word     TMIPLSRP[MNV1];    /* Time for computing signs and similar int; polys, IPLSRP */
extern Word     TMIPFSBM[MNV1];    /* Time for computing finest squarefree basis, IPFSBM */
extern Word     TMIPLRRI[MNV1];    /* Time for integral poly real root isolation,  IPLRRI */
extern Word     TMECR[MNV1];       /* Time for establishing children on rational, ECR, EC1 */
extern Word     TMSIGNPR[MNV1];    /* Time for computing projection signature, SIGNPR, SIGNP1 */  
extern Word   TMEVALUATE[MNV1];  /* Time for trial evaluataion, EVALUATE */
extern Word   TMPROPAGATE[MNV1]; /* Time for propagation, PROPAGATE */
extern Word   TMAPEQC[MNV1];  /* Time to apply equational constraints, APEQC */

/* Statistics on Solution Formula Construction Phase */
extern Word TMSOLUTION;      /* Time for Solution Formula Construction Phase */
extern Word   TMSIGTBL;        /* Time for building signature tables, SIGTBL */
extern Word   TMSIGINS;        /* Time for computing the signature intersection, SIGINS */
extern Word   TMMVLMASF;       /* Time for MVLMA, MVLMASF */
extern Word   TMGENIMP;        /* Time for generating implicants, GENIMP */
extern Word   TMSELIMP;        /* Time for selecting implicants, SELIMP */

extern Word   TMSFCONST;       /* New S.F. construction timing info */

/* Statatics, Counting */
extern Word NMNIP[MNV1];      /* Number of normalized input polynomials */
extern Word NMPF[MNV1];       /* Number of projection factors */
extern Word NMPJ[MNV1];       /* Number of projection polynomials */
extern Word NMSTACK[MNV1];    /* Number of Stacks */
extern Word NMSTACKR[MNV1];   /* Number of Stack over a Rational sample poWord */
extern Word NMCELL[MNV1];     /* Number of Cells */
extern Word NMCONVERT[MNV1];  /* Number of Conversion */
extern Word NMTCONVERT[MNV1]; /* Number of Trivial Conversion */
extern Word NMFPF;            /* Number of Projection factors of level <= f */
extern Word NMPRPT;           /* Number of propgation solution signatures */
extern Word NMPRPF;           /* Number of propagation non-solution signatures */
extern Word NMPRPC;           /* Number of compatible propagation signatures */
extern Word NMGENPRD;         /* Number of products generated */
extern Word NMGENIMP;         /* Number of implicants generated */
extern Word NMSELIMP;         /* Number of implicants selected */
extern Word NMATOM;           /* Number of atomic formulas in the solution qff */

/* Statistics on Databases */
extern Word TMDBMNG;     /* Time for Database management */
extern Word TMDBSAV;     /* Time Saved by using databases */


/* ------------------------------------------------------------------------*/
/*                    Input and output                                     */
/* ------------------------------------------------------------------------*/
#define ISIZE  70
/* extern char IBUFF[ISIZE];    /\* The size of input buffer for errory display. *\/ */
/* extern Word IPOS;            /\* The position of the last character read. *\/ */
/* extern Word ECHO;            /\* Echo the input if 1. *\/ */
/* extern Word WASBKSP;         /\* 1 if there was backspace. *\/ */
extern FILE *INSTREAM;       /* Input stream. */
extern string *INSTRING;     /* Input string. */
extern int i_INSTRING;
extern FILE *OUTSTREAM;      /* Output stream. */
extern string *OUTSTRING;    /* Output string. */
extern Word OPOS;            /* The position of the last character written. */
extern Word NOECHOSWITCHSET; /* Set to true if command-line switch */

void PushInputContext(istream &in);
void PopInputContext();
void InputContextInit(istream& defaultin);
Word setECHO(Word k);
Word setWASBKSP(Word k);
void PushOutputContext(ostream &out);
void PopOutputContext();
void OutputContextInit();


/* -------------------------------------------------------------------------*/

/* ----------------------------------------*/
/*            Handy Macros                 */
/* ----------------------------------------*/
#include "main/formulaAPI.h"

/* ----------------------------------------*/
/*            Extensions                   */
/* ----------------------------------------*/
/* sfext */
void BPOLSETS(Word L_, Word D, Word P, Word *T_, Word *N_);
Word CFLCELLLIST(Word L_D);
Word ICSIGDIFFLNSC(Word **A, Word a, Word k);
void KCONST(Word J, Word P, Word G, Word *K_, Word *KT_);
Word MINPFSETNSC(Word P,Word S,Word D,Word K);
Word NEWDERIV(Word KT, Word P, Word Pb, Word Jb, Word Ph);
void STRIPPED_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_);
Word CADSCL(Word C, Word i);
Word CELLFINDEX(Word D, Word I);
Word CRCELL(Word d);
void CSN(Word c, Word D, Word *b_, Word *d_);
Word BZWAZ(Word a, Word b);
void LISTOFCWTV(Word C, Word *Lt_, Word *Lf_);
BDigit NUMSOLPOINTS(Word D, BDigit k);
Word LPFOWCS(Word C, Word B, Word P);
Word LPFZC(Word C, Word P);
Word LPFZCAL(Word D, Word C, Word P);
BDigit SOLSETDIM(Word D, BDigit k);
Word SPCADCBDD(Word L, Word d);
Word ESPCADCRNV(Word D);
Word ESPCADLSNC(Word D, Word i, Word P);
Word ESPCADCTLSNC(Word c1,Word c2,Word c3,Word i, Word P);
Word ESPCADCTPILSNC(Word c1,Word c2, Word c3, Word i, Word j,Word k, Word P);
Word FMAAFPIRN(Word i, Word j, Word k);
void ESPCADTEST();
void ESPCADWRITE(Word D, Word i);
Word PCAD2ESPCAD(Word P,Word Ps,Word Ds,Word A);
void ADDROOTKFUNC(Word i, Word j, Word k, Word C);
Word CELLDSORT(Word I_L);
Word CLOSESTINDEX(Word c, Word L);
Word ISCLOSEST2(Word c, Word L1, Word L2);
void CONVEXPROP(Word i, Word C);
Word ESCADCL(Word C, Word i);
Word ESCADTEST(Word P, Word C);
Word ESCCPLIST1(Word L, Word m);
void ESCELLWR(Word C);
Word ESCMHSCONST1(Word L, Word C, Word i);
Word ESCMINHITSET(Word L);
void ESCSLKMF(Word C, Word k);
void EXPROP(Word i, Word C);
Word FMA2DNF(Word F);
Word DNFPROD(Word A, Word B);
void FMAIWRITE(Word F);
Word GEOTEST(Word C,Word P,Word k,Word A);
void LTFOCWTVMARK(Word C, Word *Lt_, Word *Lf_);
Word OPARTLIST(Word n);
Word PARTLIST(Word n);
Word SCAD2ESCAD(Word P, Word Ps, Word Ds, Word A);
Word SCCONFLICTQ(Word L1, Word L2);
Word SCFILTER(Word c, Word d);
void SETCADTV2MARK(Word D);
void SETMARK2FMA(Word D, Word F, Word P);
Word SPLITBYPART(Word L, Word P, Word n);
void SC_SLKMF(Word C,Word k);;
Word SCFILTER(Word c,Word d);;
Word SCCONFLICTQ(Word L1,Word L2);;
Word SC_test(Word C, Word P, Word k);
void SC_SLKMF(Word C,Word k);;
Word SCFILTER(Word c,Word d);;
Word SCCONFLICTQ(Word L1,Word L2);;
Word SC_test1(Word C, Word P, Word k);
void TEMPWR(Word D, Word i);
void UNIVPROP(Word i, Word C);
Word VECTOR_DIF(Word u, Word v);
void SC_SLKMF(Word C,Word k);;
Word SCFILTER(Word c,Word d);;
Word SCCONFLICTQ(Word L1,Word L2);;
Word SC_test(Word C, Word P, Word k);
void CSORTSS(Word **A, Word a, Word L);
Word ICSIGDIFFL(Word **A, Word a, Word k);
Word MINPFSET(Word P, Word S, Word D, Word N);
Word PWUDSCWCP(Word D, Word P, Word N);
Word SIGEQUALOL(Word *A, Word *B, Word L);
void TDTOD(Word P, Word N, Word ***P2_, Word *P1_, Word *k_);
Word FMA2DNF(Word F);
Word FMA2QUNF(Word F, Word P);
Word DNFPROD(Word A, Word B);
void FMAATOMREAD(Word Q, Word V, Word *F_, Word *t_);
Word FMACELLEVAL(Word F, Word C, Word P);
void FMASTRENGTHEN(Word F, Word L, Word P);
Word FMADMQ(Word F,Word C,Word k,Word P);
Word singleFMADMQ(Word F,Word C,Word k,Word P);
void FMAIWRITE(Word F);
Word FMALEVEL(Word F);
Word FMAOPCOMBINE(Word F);
Word FMAQEXTAF(Word F) ;
Word FMAPOLLIST(Word F, Word P);
void FMAREAD(Word P,Word V, Word *F_,Word *t_);
Word FMASMOOTH(Word F);
Word FMASORT(Word F);
Word FMASORT2(Word F);
BDigit NUMATOMS(Word F);
Word FMADISTRIBUTE(Word F, Word C);
Word FMATRYDISTRIBUTE(Word F);
void FMAWRITE(Word F, Word P, Word V);
void FMAWRITELATEX(Word F, Word P, Word V);
void FMAWRITELATEXp(Word F, Word P, Word V, Word flag);
void FMAWRITENEWLINE(Word F, Word P, Word V, Word n);
void FMAWRITENEWLINEp(Word F, Word P, Word V, Word flag);
void FMAWRITEQEIN(Word F, Word P, Word V);
void FMAWRITEp(Word F, Word P, Word V, Word flag);
Word FMA_REMCONST(Word F);
Word FTYPEINFO(Word A);
void IPDWRITELATEX(Word r, Word A, Word V);
Word POLINDEX2SIGINDEX(Word P_i, Word j);
void SETTV2FMA(Word D, Word P, Word F, Word k);
void SETORDERfromFMA(Word D,Word P,Word F,Word o);
void SETORDER(Word D,Word P,Word V);
Word ENUMMINHITSET(Word A, Word B, Word P);
Word ENUMMINHITSETSRDR(Word A, Word B);
Word MINHITSET(Word A, Word B);
Word MINHITSETSR(Word A, Word B);
Word MINHITSETSRDR(Word A, Word B);
Word MINWEIGHTHITSET(Word A, Word B);
Word RSFHSP(Word A, Word *Ab_);
Word CADCL(Word C, Word i);
Word CADFPCAD(Word D, Word P, Word S, Word I, Word Pb);
Word CADFPCADWI(Word D, Word P, Word S, Word I, Word Pb);
Word CATV(Word c);
void CCADCON(Word n, Word P, Word C, Word *Ps_, Word *Cs_);
void CCADCONEXT(Word n, Word P, Word C, Word *Ps_, Word *Cs_, Word *N_);
void CCADCONFPFS(Word n, Word P, Word C, Word N, Word *Ps_, Word *Cs_);
void CCADCONmod(Word n, Word P, Word C, Word *Ps_, Word *Cs_);
Word CELLSCPCELL(Word C, Word P, Word Ps);
Word CHTVQ(Word cs, Word b);
Word CTSEQ(Word as, Word bs);
void LTFOCALWTV(Word C, Word n, Word *Lt_, Word *Lf_);
void LTFOCWTV(Word C, Word *Lt_, Word *Lf_);
Word PCADCFCADC(Word c, Word Cs);
Word PCADCINDEX(Word c);
Word PCADCL(Word Cs, Word i);
Word PCADCSV(Word cs, Word Ps);
Word PCADSCANL(Word Cs, Word i);
void PCADSTATS(Word C, Word P, Word n);
void PCADWRITE(Word Cs, Word Ps);
Word PCELLHOWTV(Word C, Word P, Word Ps);
void PLCAD(Word Cs, Word i, Word Ps, Word P);
Word SCADDSCON(Word C, Word A, Word n);
void SIMPLE_CAD_INFO(Word D, Word P, Word n, Word flag);
void ADD2PROJFACS(Word r, Word f, Word h, Word P);
void ADD2PROJPOLS(Word r, Word q, Word h, Word J, Word P, Word *Q_, Word *L_Q);
Word LIST_OF_FACS(Word Q, Word P_);
Word LLIFIP(Word P, Word i, Word n);
Word LPFSETINTERSECT(Word S, Word G);
Word LPFSETMINUS(Word S, Word G);
Word PFDISCRIM(Word q, Word P, Word J);
Word PFPIPFL(Word p, Word L);
Word PFRES(Word p, Word q, Word P, Word J);
Word PFSREORDER(Word A_, Word B_);
Word PFSREORDERREV(Word A, Word B);
Word PFSSUNION(Word A_, Word B_);
Word PFSUFFCOEF(Word q, Word P, Word J);
Word PFSUNION(Word S1, Word S2);
Word PMINHITSETWPTS(Word Q, Word P, Word H);
Word POLFLAB(Word o, Word P);
Word PPF(Word P);
void PPFLPROJ(Word L, Word i, Word P);
Word PPFMINHITSET(Word Q, Word P, Word i);
Word PPFMINHITSETEXT(Word Q, Word P, Word i, Word *N_);
void PPROJFWRITE(Word Ps);
Word PPWITHHIST(Word J, Word r, Word h);
Word QPPPFL(Word P, Word L);
Word CYLFORM(Word C, Word P, Word k, Word A);
Word CYLIMPFORM(Word C, Word P, Word k, Word A);
Word CLEANUPFORM(Word S,Word F,Word P);
Word UNIFORMTV(Word L,Word F,Word P);
Word CF(Word L,Word F,Word P);
Word DOPFSUFF(Word P, Word K);
Word ESPCADDOPFSUFF(Word P, Word K);
Word GEOPARTII(Word F, Word S, Word P, Word Fs);
Word GEODATA(Word c, Word A, Word P);
Word GEOHEURISTIC(Word a, Word b);
Word GEOMERGE(Word c,Word G,Word P);
Word GEOFIT(Word c,Word G,Word P);
Word ATOMFILTER(Word L_A,Word L_C,Word P);
Word LALCFEQ(Word L_A,Word L_C,Word P);
Word GEOPART(Word F,Word S,Word P,Word Fs);
Word FMACELLEXQ(Word F,Word C,Word P);
Word SRTI(Word C,Word P);
Word LSUNION(Word L);
Word ISHITSET(Word S,Word L);
Word PUF(Word F, Word k);
Word IMPCONS(Word c, Word L_F, Word L_A, Word P);
Word LISTOETA(Word P, Word i);
Word PLISTOETA(Word p, Word B);
Word LISTOTA(Word P, Word i);
Word MINCADASFC(Word D, Word P, Word *Ds_, Word *Ps_);
void MINCADASFC_STATS();
Word MINCADWIASFC(Word D, Word P, Word *Ds_, Word *Ps_);
void MINCADWIASFC_STATS();
Word MINCOVBF(Word L_C, Word L_F, Word P);
Word NAIVEDOPFSUFF(Word P, Word D, Word i);
Word IMPCONS(Word,Word,Word,Word);;
Word MINCOVBF(Word,Word,Word);;
Word NAIVESF(Word L_T, Word L_F, Word L_A, Word P);
Word NECCONDS(Word L_T, Word L_F, Word L_A, Word P);
Word DOPFSUFF_FULLD(Word P, Word K);
Word ESPCADDOPFSUFF_FULLD(Word P, Word K);
Word BVC(Word *u_, Word *v_, Word n);
Word BVCI1(Word *u_, Word *v_, Word n);
void BVIS(Word **A, Word m, Word n);
void BVISI1(Word **A, Word m, Word n);
void GIS(Word *A, Word m, Word (*C)(Word,Word));
Word GISL(Word A, Word (*C)(Word,Word));
void GMS(Word *A, Word m,Word (*C)(Word,Word));
Word GMSDS(Word *A, Word m, Word (*C)(Word,Word));
Word GMSDSL(Word A, Word (*C)(Word,Word));
Word GMSL(Word A, Word (*C)(Word,Word));

#endif

