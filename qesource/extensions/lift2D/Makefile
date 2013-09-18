##################################################################
#
# Makefile for lift2D.a 
#
# Updated: 7/3/2001 -- Chris Brown
#
##################################################################

##################################################################
#  This section gives proper values to flags for opt vs. deb
#------------------
ifdef deb
LIB = lift2Dd.a
CC = ${CCd}
FLAGS = ${FLAGSd}
else
LIB = lift2Do.a
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


##################################################################
#
# Here we list the object files we want in our library. 
#
##################################################################

O_lift2D = \
$(LIB)(PFSRRQ2D.o)\
$(LIB)(PFSRDQ2D.o)\
$(LIB)(CELLLEFTSIB.o) \
$(LIB)(CELLRIGHTSIB.o) \
$(LIB)(CELLSRRQ2D.o) \
$(LIB)(CELLSRDQ2D.o) \
$(LIB)(LIFTSRR2D.o) \
$(LIB)(modHIPRRISD.o)\
$(LIB)(modHIPRRID.o)\
$(LIB)(modIBPRRIOAP.o)\
$(LIB)(LIFTSRD2D.o)\
$(LIB)(IBPRRIOAP.o) \
$(LIB)(IBPRRIOAPSF.o) \
$(LIB)(IBPELBRISIPR.o) \
$(LIB)(IBPESISIPR.o) \
$(LIB)(modIBPRRIOAPSF.o) \
$(LIB)(modSIPRRISD.o) \
$(LIB)(modSIPRRID.o)

##################################################################
#
# Embarassingly enough, this lists everything!
#
##################################################################

lift2D:		$(O_lift2D)

%.o:		%.c
		$(CC) $(FLAGS) $(INCLUDES) -c $?

