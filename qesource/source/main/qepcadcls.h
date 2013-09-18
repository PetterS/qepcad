#define MNV    30  /* Maximum Number of Variables = 30 */
#define MNV1   31  /* One more for C arrary. */

class QEPCADContext
{
public:
  string SingularPath;
};
extern QEPCADContext* GVContext;

class QepcadCls
{
public:
  /* ------------------------------------------------------------------------*/
  /*                          Intermediate results                           */
  /* ------------------------------------------------------------------------*/

  GCWord GVVL;         /* Variable List */
  GCWord GVF;          /* Input Formula */
  GCWord GVQ;          /* Quantifier List */
  GCWord GVQFF;        /* Quantifier-free formula part of the input */
  GCWord GVNQFF;       /* Normalized quantifier-free formula part */
  GCWord GVNIP;        /* Input Normalized Polynomials */
  GCWord GVLV;         /* Current Level */
  GCWord GVPF;         /* Projection Factors */
  GCWord GVPJ;         /* Projection Polynomials */
  GCWord GVPC;         /* Current Partial CAD */
  GCWord GVNV;         /* Number of variables */
  GCWord GVNFV;        /* Number of Free Variables */
  GCWord GVEQNCONST;   /* Equational constraints. */
  GCWord GVPIVOT;      /* List of pivot constraints at each level. */
  GCWord GVEQN2A;      /* Equational constraints to append. */
  GCWord GVECS;        /* Stack of indices in ECLI.   */
  GCWord GVECPI;       /* Previous index in ECLI.   */
  GCWord GVUA;         /* Unnormalized formula for assumptions. */
  GCWord GVNA;         /* Normalized formula for assumptions. */
  GCWord GVWL;         /* List of "witnesses", i.e. cells true by trial eval in a SAT problem. */

  /* ------------------------------------------------------------------------*/
  /*                      Program control                                    */
  /* ------------------------------------------------------------------------*/
  GCWord PCAFUPBRI;   /* 0 for AFUPBRI, 1 for AFUPHIBRI. */
  GCWord PCNSTEP;     /* Number of steps to be skipped */
  GCWord PCFINISH;    /* 'y' if finish, 'n' otherwise */
  GCWord PCMC;        /* 'y' if a cell is  chosen manually, 
		     * 'n' otherwise */
  GCWord PCMCC;       /* The cell manually chosen */
  GCWord PCTCN;       /* 'y' if trivial conversion is treated, 
		     * 'n' otherwise */
  GCWord PCRSP;       /* 'y' if rational sample point is treated, 
		     * 'n' otherwise */
  GCWord PCFULL;      /* 'y' if a full CAD is to be build */
  GCWord PCPROJOP;    /* Projection operators */       
  GCWord PCCCS;       /* Cell Choice Strategy for cells of level >= f. */
  GCWord PCCCSF;      /* Cell Choice Strategy for cells of level < f. */
  GCWord PCDESIRED;   /* Desired cell condition */
  GCWord PCUSEDES;    /* 'y' if use the desired condition, 'n' otherwise. */
  GCWord PCNUMDEC;    /* Number of decimal digits for 
		       * approximating algebraic numbers. */
  GCWord PCSIMPLIFY;  /* 'b' if bottom-up is used.   
		       * 't' if top-down is used. */
  GCWord PCEQC;       /* 1 if equational contraint specified.
		       * 0 otherwise. */
  GCWord PCPROPEC;    /* Propagation of equational constraints. */
  
  GCWord PCSEARCHOK;     /* 'y' if the search for true/false cell succeeded, 'n' otherwise. */
  GCWord PCSEARCHTRUE;   /* 'y' if the search for true cell should be done, 'n' otherwise. */
  GCWord PCSEARCHFALSE;  /* 'y' if the search for false cell should be done, 'n' otherwise. */

  GCWord PCCHFLAG;    /* Choose flag:  0 -> use normal CHCELL, 1 -> use niaveCHCELL. 10/11/97*/
  GCWord PCMZERROR;   /* Allow measure zero error in solution formula: 1 -> yes, 0 -> no */


  /* Statistics on Normalization Phase */
Word TMNORMQFF;     /* Time for Normalization Phase, NORMQFF */

/* Statistics on Projection Phase */
Word TMPROJECT[MNV1];   /* Time for Projection Phase, PROJECT */
Word   TMPROJ[MNV1];       /* Time for Projection Operation,  PROJ */
Word     TMIPFZT[MNV1];      /* Time for Finite Zero Test, IPFZT */
Word   TMIPLFAC[MNV1];     /* Time for Complete Factorization, IPLFAC */
Word   TMAPPEND[MNV1];     /* Time for Appending, APPEND */

/* Statistics on Truth Invariant CAD Construction Phase */
Word TMTICAD[MNV1];     /* Time for Truth invariant CAD Construnction Phase, TICAD */
Word   TMCHOOSE[MNV1];    /* Time for Choosing a cell, CHOOSE */
Word   TMCONVERT[MNV1];   /* Time for Conversion, CONVERT */
Word     TMTCN[MNV1];       /* Time for Trivial Conversion */
Word     TMNORMAL[MNV1];    /* Time for NORMAL, NORMAL */
Word     TMSIMPLE[MNV1];    /* Time for SIMPLE, SIMPLE */
Word   TMCONSTRUCT[MNV1]; /* Time for stack construction, CONSTRUCT */
Word     TMSUBST[MNV1];     /* Time for substituting on irrational sample point, SUBST */
Word     TMAFUPLM[MNV1];    /* Time for computing ldcf and monic associates, AFUPLM */
Word     TMAFCSBM[MNV1];    /* Time for computing coarsest squarefree basis, AFCSBM */
Word     TMAFUPBRI[MNV1];    /* Time for isolating real roots of algebraic polynomials using AFUPBRI. */
Word     TMAFUPHIBRI[MNV1]; /* Time for isolating real roots of algebraic polynomials using AFUPHIBRI.*/
Word     TMAFUPSIBRI[MNV1]; /* Time for isolating real roots of algebraic polynomials using AFUPSIBRI.*/
Word     TMEC[MNV1];        /* Time for establishing children on irration, EC */
Word     TMSIGNP[MNV1];     /* Time for computing projection signatures, SIGNP */
Word     TMRCFAFC[MNV1];    /* Time for converting to rational polynomials, RCFAFC */
Word     TMSUBSTR[MNV1];    /* Time for substituting on rational sample point, SUBSTR */
Word     TMIPLSRP[MNV1];    /* Time for computing signs and similar int; polys, IPLSRP */
Word     TMIPFSBM[MNV1];    /* Time for computing finest squarefree basis, IPFSBM */
Word     TMIPLRRI[MNV1];    /* Time for integral poly real root isolation,  IPLRRI */
Word     TMECR[MNV1];       /* Time for establishing children on rational, ECR, EC1 */
Word     TMSIGNPR[MNV1];    /* Time for computing projection signature, SIGNPR, SIGNP1 */  
Word   TMEVALUATE[MNV1];  /* Time for trial evaluataion, EVALUATE */
Word   TMPROPAGATE[MNV1]; /* Time for propagation, PROPAGATE */
Word   TMAPEQC[MNV1];     /* Time for applying equational constraints, APEQC */

/* Statistics on Solution Formula Construction Phase */
Word TMSOLUTION;      /* Time for Solution Formula Construction Phase */
Word   TMSIGTBL;        /* Time for building signature tables, SIGTBL */
Word   TMSIGINS;        /* Time for computing the signature intersection, SIGINS */
Word   TMMVLMASF;       /* Time for MVLMA, MVLMASF */
Word     TMGENIMP;        /* Time for generating implicants, GENIMP */
Word     TMSELIMP;        /* Time for selecting implicants, SELIMP */

/* New Solution formula construction statistics */
Word TMSFCONST;

/* Statatics, Counting */
Word NMNIP[MNV1];      /* Number of normalized input polynomials */
Word NMPF[MNV1];       /* Number of projection factors */
Word NMPJ[MNV1];       /* Number of projection polynomials */
Word NMSTACK[MNV1];    /* Number of Stacks */
Word NMSTACKR[MNV1];   /* Number of Stack over a Rational sample point */
Word NMCELL[MNV1];     /* Number of Cells */
Word NMCONVERT[MNV1];  /* Number of Conversion */
Word NMTCONVERT[MNV1]; /* Number of Trivial Conversion */
Word NMFPF;            /* Number of Projection factors of level <= f */
Word NMPRPT;           /* Number of propgation solution signatures */
Word NMPRPF;           /* Number of propagation non-solution signatures */
Word NMPRPC;           /* Number of compatible propagation signatures */
Word NMGENPRD;         /* Number of products generated */
Word NMGENIMP;         /* Number of implicants generated */
Word NMSELIMP;         /* Number of implicants selected */
Word NMATOM;           /* Number of atomic formulas in the solution qff */



/* ------------------------------------------------------------------------*/
/*                    MEMBER FUNCITONS                                     */
/* ------------------------------------------------------------------------*/
  
  void INITGLOBALS();
  void INITSTATS();
  QepcadCls() { INITGLOBALS(); INITSTATS(); }

  /*********************************************************************************
   ************ BEGIN USER's QEPCADB "API" *****************************************
   *********************************************************************************/
  // QepcadCls(V,Fs): V is the variable list, Fs is the quantified formula structure.
  // Fs = (n,k,L_Q,F), where n is the number of variables, k is the number of free
  // variables, L_Q is the list of quantifiers in left-to-right order, and F is the
  // quantifier-free formula.
  QepcadCls(Word V, Word Fs);

  // V is the variable list, Fs is the quantified formula structure.
  // Fs = (n,k,L_Q,F), where n is the number of variables, k is the number of free
  // variables, L_Q is the list of quantifiers in left-to-right order, and F is the
  // quantifier-free formula.
  void SETINPUTFORMULA(Word V, Word Fs);

  // If F is a QEPCAD unnormalized formula, the "assumptions" for CAD construction
  // are set to that formula.  F is also allowed to have values TRUE or UNDET,
  // though not FALSE.
  void SETASSUMPTIONS(Word F);

  // Noninteractively constructs a CAD.  This assumes that the input formula and
  // any assumptions have already been set.
  void CADautoConst();

  // Returns a defining formula for the set represented by the CAD in
  // the QEPCAD unnormalized formula format.  You can print such formulas
  // with the QFFWR function.
  Word GETDEFININGFORMULA(char opt='T');
  /*********************************************************************************
   ************ END USER's QEPCADB "API" *******************************************
   *********************************************************************************/

  /* MAIN */
  void QEPCAD(Word Fs, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_);

  /* PROJECT */
  void PROJECT(Word r, Word A, Word *P_, Word *J_);
  Word PROJ(Word k, Word P_k);
  Word PROJMCEC(Word k, Word A);
  Word PROJMCmod(Word k, Word A);
  Word PROJMCECmod(Word r, Word A);
  Word PROPCONS(Word k, Word Q, Word F);
  void UDEQNCONST(Word D);
  Word PROJCO(Word r, Word A);
  Word PROJHO(Word r, Word A);
  Word PROJLA(Word r, Word A);
  Word PROJMC(Word r, Word A);
  Word PROJMCx(Word r, Word A);

  /* TICAD */
  Word TICAD(Word Q, Word F, Word f, Word P, Word A);
  Word ACCCVBC(Word k, Word c, Word M, Word B1, Word b, Word* B1h=0);
  Word ACCCVBCR(Word k, Word c, Word B1, Word b, Word* B1h=0);
  Word NZFOPQR(Word c, Word k, Word b, Word A);
  Word NZFOPQ(Word c, Word k, Word M, Word b, Word A);
  void APEQC(Word c, Word k, Word P);
  void CONSTRUCT(Word c, Word k, Word f, Word Ps, Word As);
  void CONSTRUCT1(Word c, Word k, Word f, Word Ps, Word As);
  void CONSTRUCTR(Word c, Word k, Word f, Word Ps, Word As);
  void CONSTRUCTI(Word c, Word k, Word f, Word Ps, Word As);
  Word CONVERT(Word s, Word k);
  Word CELLSQ(Word c, Word k, Word h, Word j);
  void CHOOSE(Word D, Word *t_, Word *c_);
  void CHCELL(Word cs, Word *c_, Word *t_);
  void ECLI(Word D, Word *c_, Word *t_);
  BDigit SCREEN(Word c); 
  BDigit SCREENBYQUANTIFIER(Word c); 
  Word ISFECLI(Word D);
  Word INITPCAD();
  void EVALUATE(Word c, Word k, Word F, Word A);
  Word QFFTEV(Word F, Word c, Word k);
  Word SUBST(Word c, Word k, Word M, Word b, Word B);
  Word SUBSTR(Word c, Word k, Word b, Word B);


  /* IO */
  void DSTATWR();
  void STATWR();
  void SAMPLEWR(Word c);
  void CELLWR(Word c);
  void CELLSWR(Word c);

  /* SACLIB */
  Word IPFZT(Word r, Word A);
  Word IPPSCT(Word r, Word A, Word B, Word S);

  /* USERINT */
  Word GETCID(Word P, Word W);
  void GFPCSTAT(Word c, Word *p1_, Word *p0_, Word *t1_, Word *t0_, Word *l_);
  void PRAFUPBRI();
  void PRAPPROX();
  void PRCCS();
  void PRCCSF();
  void PRCHPIVOT();
  void PRDC();
  void PRDCS();
  void PRDDESIRED();
  void PRDESIRED();
  void PREQNCONST();
  void PREQNCONSTPOLY();
  void PRDEQNCONST();
  void PRDF();
  void PRDFPCSTAT();
  void PRDIP();
  void PRDLFI();
  void PRDLPI();
  void PRDLV();
  void PRDNQFF();
  void PRDPC();
  void PRDPCS();
  void PRDPF();
  void PRDPJ();
  void PRDQ();
  void PRDQFF();
  void PRDSEARCH();
  void PRDSET();
  void PRDSTACK();
  void PRDVL();
  void PREQNCONSTL();
  void PRFINISH();
  void PRGO();
  void PRIPFZT();
  void PRMCC(Word *t_);
  void PRPROJOP();
  void PRPROPEC();
  void PRRESALG();
  void PRRMPF();
  void PRRMPJ();
  void PRRSP();
  void PRSEARCH();
  void PRSIMPLIFIER();
  void PRSTEP(Word *t_);
  void PRTCN();
  void PRUSEDESIRED();
  void USERINT(Word P, Word W);
  Word INTERACT();

  /* SFEXT */
  void CLEAN_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_);
  void STRIPPED_BIGLOOP(Word Jb, Word Pb, Word P0, Word D0, Word N, Word *P_, Word *D_);
  void CADSTATS(Word C, Word P);
  void CSORCELLTR(Word c, Word Pp, Word PpO, Word PpN);
  void CSORCELLTR_MOD(Word c, Word Pp, Word PpO, Word PpN, Word P);
  void CONSTRUCTmod(Word c,Word k,Word f,Word Ps);
  Word PFSUFFCOEF(Word q, Word P, Word J);
  Word RNCADRTV(Word D, Word P, Word Q, Word N);
  void SFC1(Word D, Word P, Word J, Word n, Word sfm);
  void SFC2(Word D, Word P, Word J, Word n, Word sfm);
  void SFC3(Word D, Word P, Word J, Word n, Word L);
  Word SFC3f(Word D, Word P, Word J, Word n, Word L);
  void SFC4(Word D, Word P, Word J, Word n, Word L);
  void SFCFULLD(Word D, Word P, Word J, Word n);
  Word SFCFULLDf(Word D, Word P, Word J, Word n);
  void FALSECELLWRITE(Word D);
  void TRUECELLWRITE(Word D);
  void REPLACE_WITH_SIMPLE(Word D, Word P, Word flag);
  void SEPPIVNONPIV(Word Q_k, Word k, Word *PP_, Word *NP_);
  void PROJMCECCLOSURE(Word P, Word J, Word Q);
  void SOLEXTINT();

  /* ADJ2D */
  Word ADJ_2D_PART(Word c, Word c_l, Word c_r, Word P, Word J);
  void ADJ_2D_CONSTRUCT(Word c, Word P2);
  void TV2D(Word D, Word P, Word J);
  Word C1DTOEDGELIST(Word cl, Word cm, Word cr, Word P, Word J);
  Word ADJGRAPHCONS(Word D, Word P, Word J);
  void CLOSURE2D(Word D, Word P, Word J);
  void BOUNDARY2D(Word D, Word P, Word J);

  /* rend */
  void PLOT2DCAD2FILE(Word D, Word P, Word J);
  void DISP2DCAD(Word D, Word P, Word J);

  /* new */
  void QEPCADauto(Word Fs, Word *t_, Word *F_e_, Word *F_n_, Word *F_s_);
  void PROJECTauto(Word r, Word A, Word *P_, Word *J_);
  Word TICADauto(Word Q, Word F, Word f, Word P, Word A);

};
