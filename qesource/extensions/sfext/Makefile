##################################################################
#
# Makefile for sfext.a 
#
##################################################################

##################################################################
#  This section gives proper values to flags for opt vs. deb
#------------------
ifdef deb
LIB = sfextd.a
CC = ${CCd}
FLAGS = ${FLAGSd}
else
LIB = sfexto.a
CC = ${CCo}
FLAGS = ${FLAGSo}
endif
#------------------
##################################################################


INCLUDES  = \
		-I${saclib}/include \
		-I${qe}/source/ \
		-I.

VPATH = addpol:crcads:espcad:extlang:fewpol:formula:hoonch:\
	minhit:niavsf:pcadst:projpf:sacadd:sfcons:sort


##################################################################
#
# Here we list the object files we want in our library. 
#
##################################################################
O_addpol = \
$(LIB)(BPOLSETS.o) \
$(LIB)(CFLCELLLIST.o) \
$(LIB)(CLEAN_BIGLOOP.o) \
$(LIB)(STRIPPED_BIGLOOP.o) \
$(LIB)(ICSIGDIFFLNSC.o) \
$(LIB)(KCONST.o) \
$(LIB)(MINPFSETNSC.o) \
$(LIB)(NEWDERIV.o)

O_crcads = \
$(LIB)(CADSCL.o) \
$(LIB)(CADSTATS.o) \
$(LIB)(CELLFINDEX.o) \
$(LIB)(CSN.o) \
$(LIB)(LPFZC.o) \
$(LIB)(LPFZCAL.o) \
$(LIB)(CRCELL.o) \
$(LIB)(CSORCELL.o) \
$(LIB)(CSORCELL_MOD.o) \
$(LIB)(FALSECELLWRITE.o) \
$(LIB)(TRUECELLWRITE.o) \
$(LIB)(LISTOFCWTV.o) \
$(LIB)(NUMSOLPOINTS.o) \
$(LIB)(RNCADRTV.o) \
$(LIB)(SPCADCBDD.o) \
$(LIB)(SOLSETDIM.o) \
$(LIB)(LPFOWCS.o)

O_espcad = \
$(LIB)(ESPCADCRNV.o) \
$(LIB)(ESPCADWRITE.o) \
$(LIB)(PCAD2ESPCAD.o) \
$(LIB)(ESPCADLSNC.o)

O_extlang = \
$(LIB)(ADDROOTKFUNC.o) \
$(LIB)(CELLDSORT.o) \
$(LIB)(ESCELLWR.o) \
$(LIB)(SCAD2ESCAD.o) \
$(LIB)(ESCCPLIST1.o) \
$(LIB)(ESCMHSCONST1.o) \
$(LIB)(ESCMINHITSET.o) \
$(LIB)(ESCADCL.o) \
$(LIB)(LTFOCWTVMARK.o) \
$(LIB)(SCFILTER.o) \
$(LIB)(SCCONFLICTQ.o) \
$(LIB)(ESCSLKMF.o) \
$(LIB)(PARTLIST.o) \
$(LIB)(SPLITBYPART.o) \
$(LIB)(CLOSESTINDEX.o) \
$(LIB)(VECTOR_DIF.o) \
$(LIB)(SETCADTV2MARK.o) \
$(LIB)(SETMARK2FMA.o) \
$(LIB)(CONVEXPROP.o) \
$(LIB)(EXPROP.o) \
$(LIB)(UNIVPROP.o) \
$(LIB)(TEMPWR.o)

O_fewpol = \
$(LIB)(CSORTSS.o) \
$(LIB)(ICSIGDIFFL.o) \
$(LIB)(MINPFSET.o) \
$(LIB)(SIGEQUALOL.o) \
$(LIB)(PWUDSCWCP.o) \
$(LIB)(TDTOD.o)

O_formula = \
$(LIB)(FMAIWRITE.o) \
$(LIB)(FMAWRITE.o) \
$(LIB)(FMAWRITEp.o) \
$(LIB)(FMASMOOTH.o) \
$(LIB)(FMA2DNF.o) \
$(LIB)(FMA2QUNF.o) \
$(LIB)(FMACELLEVAL.o) \
$(LIB)(FMADMQ.o) \
$(LIB)(FTYPEINFO.o) \
$(LIB)(SETTV2FMA.o) \
$(LIB)(FMAREAD.o)  \
$(LIB)(FMAATOMREAD.o) \
$(LIB)(POLINDEX2SIGINDEX.o) \
$(LIB)(FMALEVEL.o) \
$(LIB)(FMASORT.o) \
$(LIB)(FMA_REMCONST.o) \
$(LIB)(FMAOPCOMBINE.o) \
$(LIB)(FMAWRITELATEX.o) \
$(LIB)(IPDWRITELATEX.o) \
$(LIB)(FMAWRITENEWLINE.o) \
$(LIB)(FMAWRITEQEIN.o) \
$(LIB)(FMAPOLLIST.o) \
$(LIB)(TEST.o) \
$(LIB)(FMATRYDISTRIBUTE.o) \
$(LIB)(FMASTRENGTHEN.o)


O_pcadst = \
$(LIB)(CADCL.o) \
$(LIB)(CADFPCAD.o) \
$(LIB)(CADFPCADWI.o) \
$(LIB)(CELLSCPCELL.o) \
$(LIB)(PCELLHOWTV.o) \
$(LIB)(CATV.o) \
$(LIB)(CCADCON.o) \
$(LIB)(CCADCONEXT.o) \
$(LIB)(CCADCONFPFS.o) \
$(LIB)(CCADCONmod.o) \
$(LIB)(CHTVQ.o) \
$(LIB)(CTSEQ.o) \
$(LIB)(LTFOCWTV.o) \
$(LIB)(LTFOCALWTV.o) \
$(LIB)(PCADCFCADC.o) \
$(LIB)(PCADCINDEX.o) \
$(LIB)(PCADCL.o) \
$(LIB)(PCADCSV.o) \
$(LIB)(PCADSCANL.o) \
$(LIB)(PCADSTATS.o) \
$(LIB)(PCADWRITE.o) \
$(LIB)(PLCAD.o) \
$(LIB)(SCADDSCON.o) \
$(LIB)(SIMPLE_CAD_INFO.o) \
$(LIB)(REPLACE_WITH_SIMPLE.o)

O_projpf = \
$(LIB)(ADD2PROJFACS.o) \
$(LIB)(ADD2PROJPOLS.o) \
$(LIB)(LIST_OF_FACS.o) \
$(LIB)(LPFSETINTERSECT.o) \
$(LIB)(LPFSETMINUS.o) \
$(LIB)(PFDISCRIM.o) \
$(LIB)(LLIFIP.o) \
$(LIB)(PFPIPFL.o) \
$(LIB)(PFRES.o) \
$(LIB)(PFSREORDER.o) \
$(LIB)(PFSREORDERREV.o) \
$(LIB)(PFSSUNION.o) \
$(LIB)(PFSUFFCOEF.o) \
$(LIB)(PFSUNION.o) \
$(LIB)(PMINHITSETWPTS.o) \
$(LIB)(POLFLAB.o) \
$(LIB)(PPF.o) \
$(LIB)(PPFLPROJ.o) \
$(LIB)(PPFMINHITSET.o) \
$(LIB)(PPFMINHITSETEXT.o) \
$(LIB)(PPROJFWRITE.o) \
$(LIB)(PPWITHHIST.o) \
$(LIB)(PROJCLOSUREMCEC.o) \
$(LIB)(QPPPFL.o) \
$(LIB)(SEPPIVNONPIV.o)

O_sfcons = \
$(LIB)(DOPFSUFF.o) \
$(LIB)(NAIVEDOPFSUFF.o) \
$(LIB)(ESPCADDOPFSUFF.o) \
$(LIB)(NAIVESF.o) \
$(LIB)(IMPCONS.o) \
$(LIB)(MINCOVBF.o) \
$(LIB)(LISTOTA.o) \
$(LIB)(LISTOETA.o) \
$(LIB)(NECCONDS.o) \
$(LIB)(GEOTEST.o) \
$(LIB)(GEOPARTII.o) \
$(LIB)(CYLFORM.o) \
$(LIB)(CYLIMPFORM.o)\
$(LIB)(SFC1.o) \
$(LIB)(SFC2.o) \
$(LIB)(SFC3.o) \
$(LIB)(SFC3f.o) \
$(LIB)(SFC4.o) \
$(LIB)(SFCFULLD.o) \
$(LIB)(SFCFULLDf.o) \
$(LIB)(SOLEXTINT.o)

O_sort = \
$(LIB)(GIS.o) \
$(LIB)(GISL.o) \
$(LIB)(GMS.o) \
$(LIB)(GMSL.o) \
$(LIB)(GMSDS.o) \
$(LIB)(GMSDSL.o) \
$(LIB)(BVC.o) \
$(LIB)(BVIS.o) \
$(LIB)(BVCI1.o) \
$(LIB)(BVISI1.o)

O_minhit = \
$(LIB)(MINHITSET.o) \
$(LIB)(RSFHSP.o) \
$(LIB)(ENUMMINHITSET.o) \
$(LIB)(MINHITSETSR.o) \
$(LIB)(ENUMMINHITSETSR.o) \
$(LIB)(MINHITSETSRDR.o) \
$(LIB)(MINWHITSET.o)


##################################################################
#
# Embarassingly enough, this lists everything!
#
##################################################################

sfext:		$(O_addpol) $(O_crcads) $(O_espcad) $(O_extlang) $(O_fewpol) $(O_formula)\
		$(O_minhit) $(O_pcadst)  $(O_projpf) $(O_sfcons) $(O_sort)

%.o:		%.c
		$(CC) $(FLAGS) $(INCLUDES) -c $?






