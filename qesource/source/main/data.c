/*******************************************************/
/*    qepcad.c  (global variables)                     */
/*******************************************************/
#include <stdio.h>
#include "qepcad.h"

#include "db/SINGULAR.h"
SingularServer *GVpSingularServer = 0;

/* -----------------------------------------------*/
/*            Data-bases                          */
/* -----------------------------------------------*/
Word DBAFCSBM;      /* Database for AFCSBM */   
Word DBAFPNIP;      /* Database for AFPNIP */
Word DBAFUPGC;      /* Database for AFUPGC */
Word DBAFUPSFN;     /* Database for AFUPSFN */
Word DBFNDTS;       /* Database for FNDTS */
Word DBGETRP;       /* Database for GETRP */
Word DBMODCR;       /* Database for MODCR */
Word DBIPFAC;       /* Database for IPFAC */
Word DBTIME;        /* Atcuall computation begin time */
Word DBINFO;        /* Info of the item found */
Word DBSUBST;       /* Database for SUBST */


/* ------------------------------------------------------------------------*/
/*                              Commmand                                   */
/* ------------------------------------------------------------------------*/
Word COMMANDS;     /* Holds Info about commands */
Word COMCLASS;     /* Holds command classifications and descriptions. */
#define MaxNumCommands         200
char               *Helps[MaxNumCommands];


/* ------------------------------------------------------------------------*/
/*                          Intermediate results                           */
/* ------------------------------------------------------------------------*/
Word GVMCOMM;      /* Main comment. */

/* ------------------------------------------------------------------------*/
/*                     Algorithm  trace control                             */
/* ------------------------------------------------------------------------*/
Word TCPROJ;   /* Projection Operation */
Word TCIPLFAC; /* Complete Factorization */


/* ------------------------------------------------------------------------*/
/*                    Data trace control                                   */
/* ------------------------------------------------------------------------*/
Word TCPC;      /* Partial CAD */
Word TCPROD;    /* Product generated */
Word TCPIMP;    /* Prime Implicant */
Word TCPIMPTBL; /* Prime Implicant Table */
Word TCEPIMP;   /* Essential Prime Implicant */ 
Word TCSTAT;    /* Statistics at the end */
Word TCDSTAT;   /* Dissertation statistics at the end */


/* ------------------------------------------------------------------------*/
/*                      Program control                                    */
/* ------------------------------------------------------------------------*/
Word PCIGS;       /* Implicant Generation Strategy */
Word PCDBUSE;
Word PCDBLIMIT;
Word PCRESALG;    /* Choice of resultant algorithm. */
Word PCIPFZT;     /* 'y' if IPFZT is turned on, 'n' otherise. */
Word PCVERBOSE;   /* Verbose mode: 0 means not verbose, 1 means verbose 06/19/02 */
Word PCCONTINUE;   /* Flag to show that the "continue" command has been issued. */


/* ------------------------------------------------------------------------*/
/*                         Statistics                                      */
/* ------------------------------------------------------------------------*/

/* Statictics on QEPCAD */
Word BTMQEPCAD;     /* Time at which QECAD was called */


/* Statistics on Databases */
Word TMDBMNG;     /* Time for Database management */
Word TMDBSAV;     /* Time Saved by using databases */


/* ------------------------------------------------------------------------*/
/*                          Input and output                               */
/* ------------------------------------------------------------------------*/
#define ISIZE  70
/* char IBUFF[ISIZE];    /\* The size of input buffer for errory display. *\/ */
/* Word  IPOS;           /\* The position of the last character read. *\/ */
/* Word  ECHO;           /\* Echo the input if 1. *\/ */
/* Word  WASBKSP;        /\* 1 if there was backspace. *\/ */
FILE *INSTREAM;       /* Input stream. */
FILE *OUTSTREAM;      /* Output stream. */
string *OUTSTRING;    /* Output string. */
string *INSTRING;     /* Input string. */
int i_INSTRING;       /* Index in input string. */
Word  OPOS;           /* The position of the last character written. */
Word NOECHOSWITCHSET = FALSE; /* Set to true if command-line switch */

/* -------------------------------------------------------------------------*/
/*                     Report the global variables to GC.                   */
/* -------------------------------------------------------------------------*/
void QEGLOBALS()
{
  PCRESALG = MODULAR;
  PCVERBOSE = 0;

  GCGLOBAL(&DBAFCSBM);     /* Database for AFCSBM */   
  GCGLOBAL(&DBAFPNIP);     /* Database for AFPNIP */
  GCGLOBAL(&DBAFUPGC);     /* Database for AFUPGC */
  GCGLOBAL(&DBAFUPSFN);    /* Database for AFUPSFN */
  GCGLOBAL(&DBFNDTS);      /* Database for FNDTS */
  GCGLOBAL(&DBGETRP);      /* Database for GETRP */
  GCGLOBAL(&DBMODCR);      /* Database for MODCR */
  GCGLOBAL(&DBIPFAC);      /* Database for IPFAC */
  GCGLOBAL(&DBINFO);       /* Info of the item found */
  GCGLOBAL(&DBSUBST);      /* Database for SUBST */
  GCGLOBAL(&COMMANDS);     /* Holds Info about commands */
  GCGLOBAL(&COMCLASS);     /* Holds command classifications and descriptions. */

  GCGLOBAL(&GVMCOMM);      /* Main comment. */
  GCGLOBAL(&TCPROJ);       /* Projection Operation */
  GCGLOBAL(&TCIPLFAC);     /* Complete Factorization */
  GCGLOBAL(&PCIGS);        /* Implicant Generation Strategy */
}


/* -------------------------------------------------------------------------*/
/*                     Report the global variables to GC.                   */
/* -------------------------------------------------------------------------*/
void QepcadCls::INITGLOBALS()
{
  /******************************************************
   ** Initialize program control variables
   ******************************************************/
  GVECPI = 0;
  GVUA = NIL;
  GVNA = NIL;
  GVWL = -1; /* -1 means uninit, 0 means inactive, NIL makes active */

  PCAFUPBRI = 1;
    
  /* Uses the fast cell choice mechanism.  the "selected cells"
     option works with fast cell choice, but the ordering stragies
     do not! */
  PCCHFLAG = 1;
  
  PCMZERROR = 0; /* By default do NOT allow any error!! */
  
  PCCCS = LIST3(TCORD,LDORD,HLORD);
  PCCCSF = LIST1(LLORD);
  PCIGS = 'r';
  PCFINISH = 'n';
  PCNSTEP = 1;
  PCMC = 'n';
  PCTCN = 'y';
  PCRSP = 'y';
  PCFULL = 'n';
  PCDESIRED = LIST3(EQOP,0,0);
  PCUSEDES  = 'n';
  PCIPFZT = 'y';
  PCNUMDEC = 10;
  PCSIMPLIFY = 'b';
  PCEQC  = 0;
  
  PCPROPEC = FALSE;
  
  PCSEARCHOK = 'n';
  PCSEARCHTRUE = 'n';
  PCSEARCHFALSE = 'n';
  
}

void QepcadCls::INITSTATS()
{
  Word i;
Step1: /* Statistics on Normalization Phase. */
       TMNORMQFF = 0;

Step2: /* Statistics on Projection Phase. */
       for (i = 1; i <= MNV; i++) TMPROJECT[i] = 0;
       for (i = 1; i <= MNV; i++) TMPROJ[i] = 0;
       for (i = 1; i <= MNV; i++) TMIPFZT[i] = 0;
       for (i = 1; i <= MNV; i++) TMIPLFAC[i] = 0;
       for (i = 1; i <= MNV; i++) TMAPPEND[i] = 0;
       for (i = 1; i <= MNV; i++) NMNIP[i] = 0;
       for (i = 1; i <= MNV; i++) NMPF[i] = 0;
       for (i = 1; i <= MNV; i++) NMPJ[i] = 0;

Step3: /* Statistics on Truth Invariant CAD Construction Phase. */
       for (i = 1; i <= MNV; i++) TMTICAD[i] = 0;
       for (i = 1; i <= MNV; i++) TMCHOOSE[i] = 0;
       for (i = 1; i <= MNV; i++) TMCONVERT[i] = 0;
       for (i = 1; i <= MNV; i++) TMTCN[i] = 0;
       for (i = 1; i <= MNV; i++) TMNORMAL[i] = 0;
       for (i = 1; i <= MNV; i++) TMSIMPLE[i] = 0;
       for (i = 1; i <= MNV; i++) TMCONSTRUCT[i] = 0;
       for (i = 1; i <= MNV; i++) TMSUBST[i] = 0;
       for (i = 1; i <= MNV; i++) TMAFUPLM[i] = 0;
       for (i = 1; i <= MNV; i++) TMAFCSBM[i] = 0;
       for (i = 1; i <= MNV; i++) TMAFUPBRI[i] = 0;
       for (i = 1; i <= MNV; i++) TMAFUPHIBRI[i] = 0;
       for (i = 1; i <= MNV; i++) TMSIGNP[i] = 0;
       for (i = 1; i <= MNV; i++) TMEC[i] = 0;
       for (i = 1; i <= MNV; i++) TMRCFAFC[i] = 0;
       for (i = 1; i <= MNV; i++) TMSUBSTR[i] = 0;
       for (i = 1; i <= MNV; i++) TMIPLSRP[i] = 0;
       for (i = 1; i <= MNV; i++) TMIPFSBM[i] = 0;
       for (i = 1; i <= MNV; i++) TMIPLRRI[i] = 0;
       for (i = 1; i <= MNV; i++) TMECR[i] = 0;
       for (i = 1; i <= MNV; i++) TMSIGNPR[i] = 0;
       for (i = 1; i <= MNV; i++) TMEVALUATE[i] = 0;
       for (i = 1; i <= MNV; i++) TMPROPAGATE[i] = 0;
       for (i = 1; i <= MNV; i++) TMAPEQC[i] = 0;
       for (i = 1; i <= MNV; i++) NMSTACK[i] = 0;
       for (i = 1; i <= MNV; i++) NMSTACKR[i] = 0;
       for (i = 1; i <= MNV; i++) NMCELL[i] = 0;
       for (i = 1; i <= MNV; i++) NMCONVERT[i] = 0;
       for (i = 1; i <= MNV; i++) NMTCONVERT[i] = 0;

Step4: /* Statistics on Solution Formula Construction Phase. */
       TMSOLUTION = 0;
       TMSIGTBL = 0;
       TMSIGINS = 0;
       TMMVLMASF = 0;
       TMGENIMP = 0;
       TMSELIMP = 0;
       NMFPF = 0;
       NMPRPT = 0;
       NMPRPF = 0;
       NMPRPC = 0;
       NMGENPRD = 0;
       NMGENIMP = 0;
       NMSELIMP = 0;
       NMATOM = 0;
       TMSFCONST = NIL;
}

