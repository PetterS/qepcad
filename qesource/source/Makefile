#############################################################################
#
#  Makefile for qepcad system.
#
#  (c) Copyright 1994 Research Institute for Symbolic Computation  
#                     Hoon Hong
#
#  Modified by Chris Brown, 2002. NOTE: You MUST use gmake with this file!
#############################################################################


#      Adjust these during installation
#      Note: These settings are overridden by any
#      settings in a "make" that calls this recursively
# ======================================================
CCo        =  g++
FLAGSo = -O4

CCd        =  g++
FLAGSd = -g

# ============================================================
# The readline library is in different places on solaris, i.e.
# not in /usr/lib ... also, it depends on curses.
# ============================================================
ifeq (${OSTYPE},solaris)
SPECIFLAGS =	-I/opt/sfw/include
SPECLFLAGS =	-lcurses # on solaris you have to link curses to get readline!
endif

# ============================================================
#     Do not touch below unless you know what you are doing
# ============================================================

INCLUDES  =	-I${saclib}/include \
		${SPECIFLAGS} \
		-I.

EXTLIBS   =	${qe}/extensions/sfext/sfexto.a \
		${qe}/extensions/lift2D/lift2Do.a \
		${qe}/extensions/newadj/newadjo.a \
		${qe}/extensions/adj2d/adj2do.a \
		${qe}/extensions/rend/rendo.a \
		${saclib}/lib/saclibo.a \
		-lreadline \
		${SPECLFLAGS}


EXTLIBSD  =	${qe}/extensions/sfext/sfextd.a \
		${qe}/extensions/lift2D/lift2Dd.a \
		${qe}/extensions/newadj/newadjd.a \
		${qe}/extensions/adj2d/adj2dd.a \
		${qe}/extensions/rend/rendd.a \
		${saclib}/lib/saclibd.a \
		-lreadline \
		${SPECLFLAGS}

NAME      =  qepcad
LIB       =  $(NAME).a
LIBD      =  $(NAME)d.a
EXE       =  $(NAME)
EXED      =  $(NAME)d

# ============================================================
#     Files from the primary QEPCAD program
# ============================================================

OBJS_DB = \
$(LIB)(db/AFCSBMDB.o) \
$(LIB)(db/AFPNIPDB.o) \
$(LIB)(db/AFUPGCDB.o) \
$(LIB)(db/AFUPSFNDB.o) \
$(LIB)(db/DBADD.o) \
$(LIB)(db/DBSRCH.o) \
$(LIB)(db/DBSTATWR.o) \
$(LIB)(db/FNDTSDB.o) \
$(LIB)(db/GETRPDB.o) \
$(LIB)(db/IPFACDB.o) \
$(LIB)(db/MODCRDB.o) \
$(LIB)(db/SUBSTDB.o) \
$(LIB)(db/SINGULAR.o)

OBJS_IO = \
$(LIB)(io/OW.o) \
$(LIB)(io/AFLWR.o) \
$(LIB)(io/AFPDWR.o) \
$(LIB)(io/AFUPRWR.o) \
$(LIB)(io/AFWR.o) \
$(LIB)(io/ATOMFLWR.o) \
$(LIB)(io/ATOMFRDR.o) \
$(LIB)(io/ATOMFWR.o) \
$(LIB)(io/BKSP.o) \
$(LIB)(io/CATTRNRDR.o) \
$(LIB)(io/CATTRNWR.o) \
$(LIB)(io/CELLRDR.o) \
$(LIB)(io/CELLWR.o) \
$(LIB)(io/CELLSWR.o) \
$(LIB)(io/COMMNT.o) \
$(LIB)(io/COMMNTRD.o) \
$(LIB)(io/CONWR.o) \
$(LIB)(io/CREAD.o) \
$(LIB)(io/CWRITE.o) \
$(LIB)(io/DESIREDRDR.o) \
$(LIB)(io/DESIREDWR.o) \
$(LIB)(io/DIELOC.o) \
$(LIB)(io/DISCONWR.o) \
$(LIB)(io/DNFWR.o) \
$(LIB)(io/DNFLPWR.o) \
$(LIB)(io/DNFLWR.o) \
$(LIB)(io/DSTATWR.o) \
$(LIB)(io/FGWRITE.o) \
$(LIB)(io/FILINE.o) \
$(LIB)(io/FREADR.o) \
$(LIB)(io/FWRITE.o) \
$(LIB)(io/GETWORD.o) \
$(LIB)(io/GREADR.o) \
$(LIB)(io/IPLDWR.o) \
$(LIB)(io/IPLLDWR.o) \
$(LIB)(io/IPLLDWRMOD.o) \
$(LIB)(io/IUPRWR.o) \
$(LIB)(io/LABELWR.o) \
$(LIB)(io/LGOPRDR.o) \
$(LIB)(io/LGOPWR.o) \
$(LIB)(io/PARENTWR.o) \
$(LIB)(io/PCADWR.o) \
$(LIB)(io/PCADSWR.o) \
$(LIB)(io/PIMPTBLWR.o) \
$(LIB)(io/PLABELWR.o) \
$(LIB)(io/PRODWR.o) \
$(LIB)(io/QFFLPWR.o) \
$(LIB)(io/QFFLWR.o) \
$(LIB)(io/QFFRDR.o) \
$(LIB)(io/QFFWR.o) \
$(LIB)(io/QFRDR.o) \
$(LIB)(io/QFWR.o) \
$(LIB)(io/RLOPRDR.o) \
$(LIB)(io/RLOPWR.o) \
$(LIB)(io/SAMPLEWR.o) \
$(LIB)(io/SIGNLWR.o) \
$(LIB)(io/SIGNWR.o) \
$(LIB)(io/STACKMWR.o) \
$(LIB)(io/STATWR.o) \
$(LIB)(io/TAB.o) \
$(LIB)(io/TRMODEWR.o) \
$(LIB)(io/TRUTHWR.o) \
$(LIB)(io/VLREADR.o) \
$(LIB)(io/VREADR.o) \
$(LIB)(io/VWRITE.o) \
$(LIB)(io/XREADR.o)

OBJS_MAIN = \
$(LIB)(main/BEGINQEPCAD.o) \
$(LIB)(main/ENDQEPCAD.o) \
$(LIB)(main/INITCTRL.o) \
$(LIB)(main/INITDB.o) \
$(LIB)(main/INITIO.o) \
$(LIB)(main/INITSTAT.o) \
$(LIB)(main/INITSYS.o) \
$(LIB)(main/INPUTRD.o) \
$(LIB)(main/MAIN.o) \
$(LIB)(main/PRINTBANNER.o) \
$(LIB)(main/QEPCAD.o) \
$(LIB)(main/SETUPSYS.o) \
$(LIB)(main/FAIL.o) \
$(LIB)(main/data.o) \
$(LIB)(main/QEPCADauto.o) \
$(LIB)(main/qepcadcls.o) \
$(LIB)(main/CADautoConst.o)

OBJS_NORMQFF = \
$(LIB)(normqff/EXPAFEQ.o) \
$(LIB)(normqff/EXPAFGT.o) \
$(LIB)(normqff/EXPAFGTS.o) \
$(LIB)(normqff/EXPAFLT.o) \
$(LIB)(normqff/EXPAFLTS.o) \
$(LIB)(normqff/ISATOMF.o) \
$(LIB)(normqff/NEGRLOP.o) \
$(LIB)(normqff/NORMAF.o) \
$(LIB)(normqff/NORMAFS.o) \
$(LIB)(normqff/NORMQFF.o) \
$(LIB)(normqff/PQFF.o) \
$(LIB)(normqff/RMCAFS.o) \
$(LIB)(normqff/RMCAON.o) \
$(LIB)(normqff/RMLREOP.o) \
$(LIB)(normqff/RMNOTOP.o) \
$(LIB)(normqff/RMNOTOPN.o) \
$(LIB)(normqff/TYPEAF.o) \
$(LIB)(normqff/TYPEQFF.o)

OBJS_PROJ = \
$(LIB)(proj/APPEND.o) \
$(LIB)(proj/APPENDEC.o) \
$(LIB)(proj/ECLEVEL.o) \
$(LIB)(proj/EXTRACT.o) \
$(LIB)(proj/EXTRACTS.o) \
$(LIB)(proj/GROUPSAMEPJ.o) \
$(LIB)(proj/IPDSCRPRS.o) \
$(LIB)(proj/IPDSCRQE.o) \
$(LIB)(proj/IPLFAC.o) \
$(LIB)(proj/IPRESQE.o) \
$(LIB)(proj/LCM.o) \
$(LIB)(proj/LOAR.o) \
$(LIB)(proj/LUNION.o) \
$(LIB)(proj/MPOLY.o) \
$(LIB)(proj/PROJ.o) \
$(LIB)(proj/PROJCO.o) \
$(LIB)(proj/PROJHO.o) \
$(LIB)(proj/PROJLA.o) \
$(LIB)(proj/PROJMC.o) \
$(LIB)(proj/PROJMCx.o) \
$(LIB)(proj/PROJMCmod.o) \
$(LIB)(proj/PROJMCECmod.o) \
$(LIB)(proj/PROJECT.o) \
$(LIB)(proj/PROJMCEC.o) \
$(LIB)(proj/PROPCONS.o) \
$(LIB)(proj/UDEQNCONST.o) \
$(LIB)(proj/SEPLAB.o) \
$(LIB)(proj/PROJECTauto.o)

OBJS_SYSOLVE = \
$(LIB)(sysolve/ASSUMPTIONSRATVEVAL.o) \
$(LIB)(sysolve/CHANGEASSUMPTIONSLEVEL.o) \
$(LIB)(sysolve/COEFFSYS.o) \
$(LIB)(sysolve/EVALSYS.o) \
$(LIB)(sysolve/FINDRATCOORD.o) \
$(LIB)(sysolve/IPRSOL.o) \
$(LIB)(sysolve/LBMIPL.o) \
$(LIB)(sysolve/LOSETSBF.o) \
$(LIB)(sysolve/LPSILB.o) \
$(LIB)(sysolve/PRINTCOEFFSYSTEM.o) \
$(LIB)(sysolve/QFRCALLS.o) \
$(LIB)(sysolve/SIMPLIFYSYS.o) \
$(LIB)(sysolve/SIMPLIFYSYSLIST.o) \
$(LIB)(sysolve/SYSSOLVE.o) \
$(LIB)(sysolve/SYSTOUNNORMFORMULA.o) \
$(LIB)(sysolve/VERIFYCONSTSIGN.o)

OBJS_TICAD = \
$(LIB)(ticad/ECLI.o) \
$(LIB)(ticad/ISFECLI.o) \
$(LIB)(ticad/CELLNA.o) \
$(LIB)(ticad/ACCCVBC.o) \
$(LIB)(ticad/ACCCVBCR.o) \
$(LIB)(ticad/AFCSBM.o) \
$(LIB)(ticad/AFMSBM.o) \
$(LIB)(ticad/AFUPLM.o) \
$(LIB)(ticad/AFUPMPR.o) \
$(LIB)(ticad/APEQC.o) \
$(LIB)(ticad/CELLATTR.o) \
$(LIB)(ticad/CELLCOMP.o) \
$(LIB)(ticad/CELLSQ.o) \
$(LIB)(ticad/CHCELL.o) \
$(LIB)(ticad/CHOOSE.o) \
$(LIB)(ticad/CHSCN.o) \
$(LIB)(ticad/CONSTRUCT.o) \
$(LIB)(ticad/CONVERT.o) \
$(LIB)(ticad/CSSP.o) \
$(LIB)(ticad/CVCOMP.o) \
$(LIB)(ticad/DELINPOL.o) \
$(LIB)(ticad/DELINPOLR.o) \
$(LIB)(ticad/PFPRDQ.o) \
$(LIB)(ticad/PPPRDQ.o) \
$(LIB)(ticad/IPALLPARTIALS.o) \
$(LIB)(ticad/DESCENDANT.o) \
$(LIB)(ticad/DMAFUPNR.o) \
$(LIB)(ticad/DSCOMP.o) \
$(LIB)(ticad/EC.o) \
$(LIB)(ticad/EC1.o) \
$(LIB)(ticad/ECR.o) \
$(LIB)(ticad/EVALUATE.o) \
$(LIB)(ticad/FNDTS.o) \
$(LIB)(ticad/GETRP.o) \
$(LIB)(ticad/INITPCAD.o) \
$(LIB)(ticad/IPFSBM.o) \
$(LIB)(ticad/IPLSRP.o) \
$(LIB)(ticad/ISDESIRED.o) \
$(LIB)(ticad/ISPRIMIT.o) \
$(LIB)(ticad/IXCOMP.o) \
$(LIB)(ticad/LVCOMP.o) \
$(LIB)(ticad/LPFTOLRLP.o) \
$(LIB)(ticad/LPFZCALL.o) \
$(LIB)(ticad/MAFDIF.o) \
$(LIB)(ticad/MAFHOM.o) \
$(LIB)(ticad/MAFINV.o) \
$(LIB)(ticad/MAFPROD.o) \
$(LIB)(ticad/MAFUPDIF.o) \
$(LIB)(ticad/MAFUPEPROD.o) \
$(LIB)(ticad/MAFUPGCD.o) \
$(LIB)(ticad/MAFUPMON.o) \
$(LIB)(ticad/MAFUPNR.o) \
$(LIB)(ticad/MCELL.o) \
$(LIB)(ticad/MKMUL.o) \
$(LIB)(ticad/MODCR.o) \
$(LIB)(ticad/MUPNR.o) \
$(LIB)(ticad/NORMAL.o) \
$(LIB)(ticad/NZFOPQ.o) \
$(LIB)(ticad/NZFOPQR.o) \
$(LIB)(ticad/PFCOICQ.o) \
$(LIB)(ticad/PLPOS.o) \
$(LIB)(ticad/PROPAGATE.o) \
$(LIB)(ticad/QFFTEV.o) \
$(LIB)(ticad/RCFAFC.o) \
$(LIB)(ticad/SETTRUTHVALUE.o) \
$(LIB)(ticad/SIGNB.o) \
$(LIB)(ticad/SIGNL.o) \
$(LIB)(ticad/SIGNP.o) \
$(LIB)(ticad/SIGNP1.o) \
$(LIB)(ticad/SIGNPR.o) \
$(LIB)(ticad/SIMPLEQE.o) \
$(LIB)(ticad/SPFRPSFT.o) \
$(LIB)(ticad/SSCOMP.o) \
$(LIB)(ticad/STACKMULT.o) \
$(LIB)(ticad/SUBST.o) \
$(LIB)(ticad/SUBSTR.o) \
$(LIB)(ticad/TCHILD.o) \
$(LIB)(ticad/TICAD.o) \
$(LIB)(ticad/TICADauto.o)

OBJS_USERINT = \
$(LIB)(userint/CELLFIDX.o) \
$(LIB)(userint/ESPIWR.o) \
$(LIB)(userint/ESPORD.o) \
$(LIB)(userint/GETCID.o) \
$(LIB)(userint/GFPCSTAT.o) \
$(LIB)(userint/HELPFRD.o) \
$(LIB)(userint/HELPWR.o) \
$(LIB)(userint/INTERACT.o) \
$(LIB)(userint/PRAFUPBRI.o) \
$(LIB)(userint/PRAPPROX.o) \
$(LIB)(userint/PRCCS.o) \
$(LIB)(userint/PRCCSF.o) \
$(LIB)(userint/PRDC.o) \
$(LIB)(userint/PRDCC.o) \
$(LIB)(userint/PRDCS.o) \
$(LIB)(userint/PRDDESIRED.o) \
$(LIB)(userint/PRDESIRED.o) \
$(LIB)(userint/PRDF.o) \
$(LIB)(userint/PRDFPCSTAT.o) \
$(LIB)(userint/PRDIP.o) \
$(LIB)(userint/PRDLFI.o) \
$(LIB)(userint/PRDLPI.o) \
$(LIB)(userint/PRDLV.o) \
$(LIB)(userint/PRDNQFF.o) \
$(LIB)(userint/PRDPC.o) \
$(LIB)(userint/PRDPCS.o) \
$(LIB)(userint/PRDPF.o) \
$(LIB)(userint/PRDPJ.o) \
$(LIB)(userint/PRDQ.o) \
$(LIB)(userint/PRDQFF.o) \
$(LIB)(userint/PRDSEARCH.o) \
$(LIB)(userint/PRDSET.o) \
$(LIB)(userint/PRDSTACK.o) \
$(LIB)(userint/PRDTRACEA.o) \
$(LIB)(userint/PRDTRACED.o) \
$(LIB)(userint/PRDVL.o) \
$(LIB)(userint/PREQNCONST.o) \
$(LIB)(userint/PRFINISH.o) \
$(LIB)(userint/PRGO.o) \
$(LIB)(userint/PRHELP.o) \
$(LIB)(userint/PRIPFZT.o) \
$(LIB)(userint/PRIGS.o) \
$(LIB)(userint/PRLDB.o) \
$(LIB)(userint/PRMCC.o) \
$(LIB)(userint/PROMPT.o) \
$(LIB)(userint/PRPROJOP.o) \
$(LIB)(userint/PRQUIT.o) \
$(LIB)(userint/PRRMPF.o) \
$(LIB)(userint/PRRMPJ.o) \
$(LIB)(userint/PRRSP.o) \
$(LIB)(userint/PRSEARCH.o) \
$(LIB)(userint/PRSIMPLIFIER.o) \
$(LIB)(userint/PRSTEP.o) \
$(LIB)(userint/PRTCN.o) \
$(LIB)(userint/PRTRACEA.o) \
$(LIB)(userint/PRTRACED.o) \
$(LIB)(userint/PRUDB.o) \
$(LIB)(userint/PRUSEDESIRED.o) \
$(LIB)(userint/PRWHATIS.o) \
$(LIB)(userint/RMMPF.o) \
$(LIB)(userint/RMMPJ.o) \
$(LIB)(userint/PRCHPIVOT.o) \
$(LIB)(userint/PRDEQNCONST.o) \
$(LIB)(userint/PREQNCONSTL.o) \
$(LIB)(userint/PRPROPEC.o) \
$(LIB)(userint/PRRESALG.o) \
$(LIB)(userint/USERINT.o)

OBJS_UTIL = \
$(LIB)(util/CELLDEG.o) \
$(LIB)(util/CELLDIM.o) \
$(LIB)(util/MATCHWORD.o) \
$(LIB)(util/MBPROD.o) \
$(LIB)(util/MMFLR.o) \
$(LIB)(util/PLDEG.o) \
$(LIB)(util/PSIMREP.o) \
$(LIB)(util/RMCONS.o) \
$(LIB)(util/RNFAF.o) \
$(LIB)(util/SVPOWR.o) \
$(LIB)(util/SVPROD.o) \
$(LIB)(util/VALIDLBL.o)

#  To replace saclib routines. 
OBJS_SACLIB = \
$(LIB)(saclib/GCSI.o) \
$(LIB)(saclib/gcword.o) \
$(LIB)(saclib/IPFZT.o) \
$(LIB)(saclib/IPFZT1.o) \
$(LIB)(saclib/IPPSCT.o) \
$(LIB)(saclib/IPRNEVAL.o) \
$(LIB)(saclib/RVSPTSVSP.o) \
$(LIB)(saclib/SOSRSUBS.o) \
$(LIB)(saclib/SOSRSUPS.o) \
$(LIB)(saclib/SUBSET.o)


OBJS_DBd = \
$(LIBD)(db/AFCSBMDB.o) \
$(LIBD)(db/AFPNIPDB.o) \
$(LIBD)(db/AFUPGCDB.o) \
$(LIBD)(db/AFUPSFNDB.o) \
$(LIBD)(db/DBADD.o) \
$(LIBD)(db/DBSRCH.o) \
$(LIBD)(db/DBSTATWR.o) \
$(LIBD)(db/FNDTSDB.o) \
$(LIBD)(db/GETRPDB.o) \
$(LIBD)(db/IPFACDB.o) \
$(LIBD)(db/MODCRDB.o) \
$(LIBD)(db/SUBSTDB.o) \
$(LIBD)(db/SINGULAR.o)

OBJS_IOd = \
$(LIBD)(io/OW.o) \
$(LIBD)(io/AFLWR.o) \
$(LIBD)(io/AFPDWR.o) \
$(LIBD)(io/AFUPRWR.o) \
$(LIBD)(io/AFWR.o) \
$(LIBD)(io/ATOMFLWR.o) \
$(LIBD)(io/ATOMFRDR.o) \
$(LIBD)(io/ATOMFWR.o) \
$(LIBD)(io/BKSP.o) \
$(LIBD)(io/CATTRNRDR.o) \
$(LIBD)(io/CATTRNWR.o) \
$(LIBD)(io/CELLRDR.o) \
$(LIBD)(io/CELLWR.o) \
$(LIBD)(io/CELLSWR.o) \
$(LIBD)(io/COMMNT.o) \
$(LIBD)(io/COMMNTRD.o) \
$(LIBD)(io/CONWR.o) \
$(LIBD)(io/CREAD.o) \
$(LIBD)(io/CWRITE.o) \
$(LIBD)(io/DESIREDRDR.o) \
$(LIBD)(io/DESIREDWR.o) \
$(LIBD)(io/DIELOC.o) \
$(LIBD)(io/DISCONWR.o) \
$(LIBD)(io/DNFWR.o) \
$(LIBD)(io/DNFLPWR.o) \
$(LIBD)(io/DNFLWR.o) \
$(LIBD)(io/DSTATWR.o) \
$(LIBD)(io/FGWRITE.o) \
$(LIBD)(io/FILINE.o) \
$(LIBD)(io/FREADR.o) \
$(LIBD)(io/FWRITE.o) \
$(LIBD)(io/GETWORD.o) \
$(LIBD)(io/GREADR.o) \
$(LIBD)(io/IPLDWR.o) \
$(LIBD)(io/IPLLDWR.o) \
$(LIBD)(io/IPLLDWRMOD.o) \
$(LIBD)(io/IUPRWR.o) \
$(LIBD)(io/LABELWR.o) \
$(LIBD)(io/LGOPRDR.o) \
$(LIBD)(io/LGOPWR.o) \
$(LIBD)(io/PARENTWR.o) \
$(LIBD)(io/PCADWR.o) \
$(LIBD)(io/PCADSWR.o) \
$(LIBD)(io/PIMPTBLWR.o) \
$(LIBD)(io/PLABELWR.o) \
$(LIBD)(io/PRODWR.o) \
$(LIBD)(io/QFFLPWR.o) \
$(LIBD)(io/QFFLWR.o) \
$(LIBD)(io/QFFRDR.o) \
$(LIBD)(io/QFFWR.o) \
$(LIBD)(io/QFRDR.o) \
$(LIBD)(io/QFWR.o) \
$(LIBD)(io/RLOPRDR.o) \
$(LIBD)(io/RLOPWR.o) \
$(LIBD)(io/SAMPLEWR.o) \
$(LIBD)(io/SIGNLWR.o) \
$(LIBD)(io/SIGNWR.o) \
$(LIBD)(io/STACKMWR.o) \
$(LIBD)(io/STATWR.o) \
$(LIBD)(io/TAB.o) \
$(LIBD)(io/TRMODEWR.o) \
$(LIBD)(io/TRUTHWR.o) \
$(LIBD)(io/VLREADR.o) \
$(LIBD)(io/VREADR.o) \
$(LIBD)(io/VWRITE.o) \
$(LIBD)(io/XREADR.o)

OBJS_MAINd = \
$(LIBD)(main/BEGINQEPCAD.o) \
$(LIBD)(main/ENDQEPCAD.o) \
$(LIBD)(main/INITCTRL.o) \
$(LIBD)(main/INITDB.o) \
$(LIBD)(main/INITIO.o) \
$(LIBD)(main/INITSTAT.o) \
$(LIBD)(main/INITSYS.o) \
$(LIBD)(main/INPUTRD.o) \
$(LIBD)(main/MAIN.o) \
$(LIBD)(main/PRINTBANNER.o) \
$(LIBD)(main/QEPCAD.o) \
$(LIBD)(main/SETUPSYS.o) \
$(LIBD)(main/FAIL.o) \
$(LIBD)(main/data.o) \
$(LIBD)(main/QEPCADauto.o) \
$(LIBD)(main/qepcadcls.o) \
$(LIBD)(main/CADautoConst.o)

OBJS_NORMQFFd = \
$(LIBD)(normqff/EXPAFEQ.o) \
$(LIBD)(normqff/EXPAFGT.o) \
$(LIBD)(normqff/EXPAFGTS.o) \
$(LIBD)(normqff/EXPAFLT.o) \
$(LIBD)(normqff/EXPAFLTS.o) \
$(LIBD)(normqff/ISATOMF.o) \
$(LIBD)(normqff/NEGRLOP.o) \
$(LIBD)(normqff/NORMAF.o) \
$(LIBD)(normqff/NORMAFS.o) \
$(LIBD)(normqff/NORMQFF.o) \
$(LIBD)(normqff/PQFF.o) \
$(LIBD)(normqff/RMCAFS.o) \
$(LIBD)(normqff/RMCAON.o) \
$(LIBD)(normqff/RMLREOP.o) \
$(LIBD)(normqff/RMNOTOP.o) \
$(LIBD)(normqff/RMNOTOPN.o) \
$(LIBD)(normqff/TYPEAF.o) \
$(LIBD)(normqff/TYPEQFF.o)

OBJS_PROJd = \
$(LIBD)(proj/APPEND.o) \
$(LIBD)(proj/APPENDEC.o) \
$(LIBD)(proj/ECLEVEL.o) \
$(LIBD)(proj/EXTRACT.o) \
$(LIBD)(proj/EXTRACTS.o) \
$(LIBD)(proj/GROUPSAMEPJ.o) \
$(LIBD)(proj/IPDSCRPRS.o) \
$(LIBD)(proj/IPDSCRQE.o) \
$(LIBD)(proj/IPLFAC.o) \
$(LIBD)(proj/IPRESQE.o) \
$(LIBD)(proj/LCM.o) \
$(LIBD)(proj/LOAR.o) \
$(LIBD)(proj/LUNION.o) \
$(LIBD)(proj/MPOLY.o) \
$(LIBD)(proj/PROJ.o) \
$(LIBD)(proj/PROJCO.o) \
$(LIBD)(proj/PROJHO.o) \
$(LIBD)(proj/PROJLA.o) \
$(LIBD)(proj/PROJMC.o) \
$(LIBD)(proj/PROJMCx.o) \
$(LIBD)(proj/PROJMCmod.o) \
$(LIBD)(proj/PROJMCECmod.o) \
$(LIBD)(proj/PROJECT.o) \
$(LIBD)(proj/PROJMCEC.o) \
$(LIBD)(proj/PROPCONS.o) \
$(LIBD)(proj/UDEQNCONST.o) \
$(LIBD)(proj/SEPLAB.o) \
$(LIBD)(proj/PROJECTauto.o)

OBJS_SYSOLVEd = \
$(LIBD)(sysolve/ASSUMPTIONSRATVEVAL.o) \
$(LIBD)(sysolve/CHANGEASSUMPTIONSLEVEL.o) \
$(LIBD)(sysolve/COEFFSYS.o) \
$(LIBD)(sysolve/EVALSYS.o) \
$(LIBD)(sysolve/FINDRATCOORD.o) \
$(LIBD)(sysolve/IPRSOL.o) \
$(LIBD)(sysolve/LBMIPL.o) \
$(LIBD)(sysolve/LOSETSBF.o) \
$(LIBD)(sysolve/LPSILB.o) \
$(LIBD)(sysolve/PRINTCOEFFSYSTEM.o) \
$(LIBD)(sysolve/QFRCALLS.o) \
$(LIBD)(sysolve/SIMPLIFYSYS.o) \
$(LIBD)(sysolve/SIMPLIFYSYSLIST.o) \
$(LIBD)(sysolve/SYSSOLVE.o) \
$(LIBD)(sysolve/SYSTOUNNORMFORMULA.o) \
$(LIBD)(sysolve/VERIFYCONSTSIGN.o)

OBJS_TICADd = \
$(LIBD)(ticad/ECLI.o) \
$(LIBD)(ticad/ISFECLI.o) \
$(LIBD)(ticad/CELLNA.o) \
$(LIBD)(ticad/ACCCVBC.o) \
$(LIBD)(ticad/ACCCVBCR.o) \
$(LIBD)(ticad/AFCSBM.o) \
$(LIBD)(ticad/AFMSBM.o) \
$(LIBD)(ticad/AFUPLM.o) \
$(LIBD)(ticad/AFUPMPR.o) \
$(LIBD)(ticad/APEQC.o) \
$(LIBD)(ticad/CELLATTR.o) \
$(LIBD)(ticad/CELLCOMP.o) \
$(LIBD)(ticad/CELLSQ.o) \
$(LIBD)(ticad/CHCELL.o) \
$(LIBD)(ticad/CHOOSE.o) \
$(LIBD)(ticad/CHSCN.o) \
$(LIBD)(ticad/CONSTRUCT.o) \
$(LIBD)(ticad/CONVERT.o) \
$(LIBD)(ticad/CSSP.o) \
$(LIBD)(ticad/CVCOMP.o) \
$(LIBD)(ticad/DELINPOL.o) \
$(LIBD)(ticad/DELINPOLR.o) \
$(LIBD)(ticad/PFPRDQ.o) \
$(LIBD)(ticad/PPPRDQ.o) \
$(LIBD)(ticad/IPALLPARTIALS.o) \
$(LIBD)(ticad/DESCENDANT.o) \
$(LIBD)(ticad/DMAFUPNR.o) \
$(LIBD)(ticad/DSCOMP.o) \
$(LIBD)(ticad/EC.o) \
$(LIBD)(ticad/EC1.o) \
$(LIBD)(ticad/ECR.o) \
$(LIBD)(ticad/EVALUATE.o) \
$(LIBD)(ticad/FNDTS.o) \
$(LIBD)(ticad/GETRP.o) \
$(LIBD)(ticad/INITPCAD.o) \
$(LIBD)(ticad/IPFSBM.o) \
$(LIBD)(ticad/IPLSRP.o) \
$(LIBD)(ticad/ISDESIRED.o) \
$(LIBD)(ticad/ISPRIMIT.o) \
$(LIBD)(ticad/IXCOMP.o) \
$(LIBD)(ticad/LVCOMP.o) \
$(LIBD)(ticad/LPFTOLRLP.o) \
$(LIBD)(ticad/LPFZCALL.o) \
$(LIBD)(ticad/MAFDIF.o) \
$(LIBD)(ticad/MAFHOM.o) \
$(LIBD)(ticad/MAFINV.o) \
$(LIBD)(ticad/MAFPROD.o) \
$(LIBD)(ticad/MAFUPDIF.o) \
$(LIBD)(ticad/MAFUPEPROD.o) \
$(LIBD)(ticad/MAFUPGCD.o) \
$(LIBD)(ticad/MAFUPMON.o) \
$(LIBD)(ticad/MAFUPNR.o) \
$(LIBD)(ticad/MCELL.o) \
$(LIBD)(ticad/MKMUL.o) \
$(LIBD)(ticad/MODCR.o) \
$(LIBD)(ticad/MUPNR.o) \
$(LIBD)(ticad/NORMAL.o) \
$(LIBD)(ticad/NZFOPQ.o) \
$(LIBD)(ticad/NZFOPQR.o) \
$(LIBD)(ticad/PFCOICQ.o) \
$(LIBD)(ticad/PLPOS.o) \
$(LIBD)(ticad/PROPAGATE.o) \
$(LIBD)(ticad/QFFTEV.o) \
$(LIBD)(ticad/RCFAFC.o) \
$(LIBD)(ticad/SETTRUTHVALUE.o) \
$(LIBD)(ticad/SIGNB.o) \
$(LIBD)(ticad/SIGNL.o) \
$(LIBD)(ticad/SIGNP.o) \
$(LIBD)(ticad/SIGNP1.o) \
$(LIBD)(ticad/SIGNPR.o) \
$(LIBD)(ticad/SIMPLEQE.o) \
$(LIBD)(ticad/SPFRPSFT.o) \
$(LIBD)(ticad/SSCOMP.o) \
$(LIBD)(ticad/STACKMULT.o) \
$(LIBD)(ticad/SUBST.o) \
$(LIBD)(ticad/SUBSTR.o) \
$(LIBD)(ticad/TCHILD.o) \
$(LIBD)(ticad/TICAD.o) \
$(LIBD)(ticad/TICADauto.o)

OBJS_USERINTd = \
$(LIBD)(userint/CELLFIDX.o) \
$(LIBD)(userint/ESPIWR.o) \
$(LIBD)(userint/ESPORD.o) \
$(LIBD)(userint/GETCID.o) \
$(LIBD)(userint/GFPCSTAT.o) \
$(LIBD)(userint/HELPFRD.o) \
$(LIBD)(userint/HELPWR.o) \
$(LIBD)(userint/INTERACT.o) \
$(LIBD)(userint/PRAFUPBRI.o) \
$(LIBD)(userint/PRAPPROX.o) \
$(LIBD)(userint/PRCCS.o) \
$(LIBD)(userint/PRCCSF.o) \
$(LIBD)(userint/PRDC.o) \
$(LIBD)(userint/PRDCC.o) \
$(LIBD)(userint/PRDCS.o) \
$(LIBD)(userint/PRDDESIRED.o) \
$(LIBD)(userint/PRDESIRED.o) \
$(LIBD)(userint/PRDF.o) \
$(LIBD)(userint/PRDFPCSTAT.o) \
$(LIBD)(userint/PRDIP.o) \
$(LIBD)(userint/PRDLFI.o) \
$(LIBD)(userint/PRDLPI.o) \
$(LIBD)(userint/PRDLV.o) \
$(LIBD)(userint/PRDNQFF.o) \
$(LIBD)(userint/PRDPC.o) \
$(LIBD)(userint/PRDPCS.o) \
$(LIBD)(userint/PRDPF.o) \
$(LIBD)(userint/PRDPJ.o) \
$(LIBD)(userint/PRDQ.o) \
$(LIBD)(userint/PRDQFF.o) \
$(LIBD)(userint/PRDSEARCH.o) \
$(LIBD)(userint/PRDSET.o) \
$(LIBD)(userint/PRDSTACK.o) \
$(LIBD)(userint/PRDTRACEA.o) \
$(LIBD)(userint/PRDTRACED.o) \
$(LIBD)(userint/PRDVL.o) \
$(LIBD)(userint/PREQNCONST.o) \
$(LIBD)(userint/PRFINISH.o) \
$(LIBD)(userint/PRGO.o) \
$(LIBD)(userint/PRHELP.o) \
$(LIBD)(userint/PRIPFZT.o) \
$(LIBD)(userint/PRIGS.o) \
$(LIBD)(userint/PRLDB.o) \
$(LIBD)(userint/PRMCC.o) \
$(LIBD)(userint/PROMPT.o) \
$(LIBD)(userint/PRPROJOP.o) \
$(LIBD)(userint/PRQUIT.o) \
$(LIBD)(userint/PRRMPF.o) \
$(LIBD)(userint/PRRMPJ.o) \
$(LIBD)(userint/PRRSP.o) \
$(LIBD)(userint/PRSEARCH.o) \
$(LIBD)(userint/PRSIMPLIFIER.o) \
$(LIBD)(userint/PRSTEP.o) \
$(LIBD)(userint/PRTCN.o) \
$(LIBD)(userint/PRTRACEA.o) \
$(LIBD)(userint/PRTRACED.o) \
$(LIBD)(userint/PRUDB.o) \
$(LIBD)(userint/PRUSEDESIRED.o) \
$(LIBD)(userint/PRWHATIS.o) \
$(LIBD)(userint/RMMPF.o) \
$(LIBD)(userint/RMMPJ.o) \
$(LIBD)(userint/PRCHPIVOT.o) \
$(LIBD)(userint/PRDEQNCONST.o) \
$(LIBD)(userint/PREQNCONSTL.o) \
$(LIBD)(userint/PRPROPEC.o) \
$(LIBD)(userint/PRRESALG.o) \
$(LIBD)(userint/USERINT.o)

OBJS_UTILd = \
$(LIBD)(util/CELLDEG.o) \
$(LIBD)(util/CELLDIM.o) \
$(LIBD)(util/MATCHWORD.o) \
$(LIBD)(util/MBPROD.o) \
$(LIBD)(util/MMFLR.o) \
$(LIBD)(util/PLDEG.o) \
$(LIBD)(util/PSIMREP.o) \
$(LIBD)(util/RMCONS.o) \
$(LIBD)(util/RNFAF.o) \
$(LIBD)(util/SVPOWR.o) \
$(LIBD)(util/SVPROD.o) \
$(LIBD)(util/VALIDLBL.o)

#  To replace saclib routines. 
OBJS_SACLIBd = \
$(LIBD)(saclib/GCSI.o) \
$(LIBD)(saclib/gcword.o) \
$(LIBD)(saclib/IPFZT.o) \
$(LIBD)(saclib/IPFZT1.o) \
$(LIBD)(saclib/IPPSCT.o) \
$(LIBD)(saclib/IPRNEVAL.o) \
$(LIBD)(saclib/RVSPTSVSP.o) \
$(LIBD)(saclib/SOSRSUBS.o) \
$(LIBD)(saclib/SOSRSUPS.o) \
$(LIBD)(saclib/SUBSET.o)

# ============================================================
#     Dependecies
# ============================================================

DEPENDENCIESo =    $(OBJS_DB) \
$(OBJS_IO) \
$(OBJS_MAIN) \
$(OBJS_NORMQFF) \
$(OBJS_PROJ) \
$(OBJS_SYSOLVE) \
$(OBJS_TICAD) \
$(OBJS_TUNE) \
$(OBJS_USERINT) \
$(OBJS_UTIL) \
$(OBJS_SACLIB)

DEPENDENCIESd =    $(OBJS_DBd) \
$(OBJS_IOd) \
$(OBJS_MAINd) \
$(OBJS_NORMQFFd) \
$(OBJS_PROJd) \
$(OBJS_SYSOLVEd) \
$(OBJS_TICADd) \
$(OBJS_TUNEd) \
$(OBJS_USERINTd) \
$(OBJS_UTILd) \
$(OBJS_SACLIBd)

# ============================================================
#     Make rules
# ============================================================
opt:		override CFLAGS = $(FLAGSo)
opt:		override CC = $(CCo)
opt:		$(DEPENDENCIESo)
		ranlib $(LIB)
		@echo Linking the optimized program......
		$(CCo) $(FLAGSo) $(INCLUDES) saclib/GCSI.c saclib/FAIL.c \
			$(LIB) $(EXTLIBS) $(LIB) $(EXTLIBS) -o $(EXE)


deb:		override CFLAGS = $(FLAGSd)
deb:		override CC = $(CCd)
deb:		$(DEPENDENCIESd)
		ranlib $(LIBD)
		@echo Linking the debugged program......
		$(CCd) $(FLAGSd) $(INCLUDES) saclib/GCSI.c saclib/FAIL.c \
			 $(LIBD) $(EXTLIBSD) $(LIBD)  $(EXTLIBSD) -o $(EXED) #\
			#/home/wcbrown/Downloads/duma_2_4_27/libduma.a -lpthread

#.c.o:	
%.o:	%.c
		$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<
