##################################################################
#
# Makefile for adj2D.a 
#
# Updated: 3/4/97 -- Chris Brown
#
##################################################################

##################################################################
#  This section gives proper values to flags for opt vs. deb
#------------------
ifdef deb
LIB = adj2dd.a
CC = ${CCd}
FLAGS = ${FLAGSd}
else
LIB = adj2do.a
CC = ${CCo}
FLAGS = ${FLAGSo}
endif
#------------------
##################################################################


INCLUDES  = \
		-I${saclib}/include \
		-I${qe}/source \
		-I${qe}/extensions/sfext \
		-I.

VPATH = 	oldadj:sac_ext:truthbytop


##################################################################
#
# Here we list the object files we want in our library. 
#
##################################################################

O_adj2d = \
$(LIB)(testfunc.o) \
$(LIB)(ADJ_2D.o) \
$(LIB)(ADJ_2D_PART.o) \
$(LIB)(AD2DC_CONS.o) \
$(LIB)(AD2DS_CONS.o) \
$(LIB)(LDCOEFMASK.o) \
$(LIB)(VECTOR_LTEQ.o) \
$(LIB)(VECTOR_SUM.o) \
$(LIB)(VECTOR_DIF_S.o) \
$(LIB)(VECTOR_SEMI_COMP.o) \
$(LIB)(VECTOR_S_PROD.o) \
$(LIB)(VECTOR_NEG.o) \
$(LIB)(SUM_NORM_SP.o) \
$(LIB)(CWD_VECTOR_Q.o) \
$(LIB)(ZERO_VECTOR.o) \
$(LIB)(EQUAL_ON_ONES.o) \
$(LIB)(ADD_2_SOL.o) \
$(LIB)(Mystery_f.o) \
$(LIB)(ADJ_2D_CONSTRUCT.o) \
$(LIB)(P1.o) \
$(LIB)(P2.o) \
$(LIB)(P3.o) \
$(LIB)(P4.o) \
$(LIB)(ADJ_2D1_COMPLETE.o) \
$(LIB)(ADJ_2D1.o) \
$(LIB)(ADJ_2D1_SIMPLE.o) \
$(LIB)(ADJ_2D1P1.o) \
$(LIB)(ADJ_2D1P2.o) \
$(LIB)(ADJ_2D1P3.o)\
$(LIB)(VECTOR_ODD_E.o)

O_oldadj = \
$(LIB)(LLBRSPFSS.o) \
$(LIB)(DNCAC.o) \
$(LIB)(LLSISS.o) \
$(LIB)(RIIFACMA.o)\
$(LIB)(ACMADJ2D.o)\
$(LIB)(RIIFACMABR.o) \
$(LIB)(SPRLC.o)

O_sacext = \
$(LIB)(LBRNMAX.o) \
$(LIB)(LBRNMIN.o) \
$(LIB)(PCFE.o) \
$(LIB)(IUPLBREVAL.o)\
$(LIB)(IPLBREVAL.o)\
$(LIB)(IUPSOPOR.o)\
$(LIB)(IUPSOPORFIL.o)\
$(LIB)(RRCOMPSRI.o)\
$(LIB)(ADJNNA.o)\
$(LIB)(IBPIDFV.o)\
$(LIB)(IPMP2.o)\
$(LIB)(RRLBRNCOMP.o)\
$(LIB)(IPRRILBRI.o)\
$(LIB)(IUPTSII.o)

O_tbytop = \
$(LIB)(TVCLOSURE1D.o) \
$(LIB)(TVCLOSURE1DS.o) \
$(LIB)(CCTV.o) \
$(LIB)(CTVPROPUP.o) \
$(LIB)(TVCCOSBSVAI.o) \
$(LIB)(GRAPHMODULE.o) \
$(LIB)(TV2D.o) \
$(LIB)(C1DTOEDGELIST.o) \
$(LIB)(ADJ2DITOEL.o) \
$(LIB)(ADJGRAPHCONS.o) \
$(LIB)(CLOSURE2D.o) \
$(LIB)(BOUNDARY2D.o)



##################################################################
#
# Embarassingly enough, this lists everything!
#
##################################################################

adj2d:		$(O_adj2d) $(O_oldadj) $(O_sacext) $(O_tbytop)

%.o:		%.c
		$(CC) $(FLAGS) $(INCLUDES) -c $?

