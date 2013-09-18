##################################################################
#
#
##################################################################

##################################################################
#  This section gives proper values to flags for opt vs. deb
#------------------
ifdef deb
LIB = newadjd.a
CC = ${CCd}
FLAGS = ${FLAGSd}
else
LIB = newadjo.a
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
#
##################################################################

O_newadj = \
$(LIB)(HAP1.o) \
$(LIB)(HAP2.o) \
$(LIB)(HAP3.o) \
$(LIB)(HA.o) \
$(LIB)(HALDCOEFMASK.o) \
$(LIB)(HAS_CONS.o) \
$(LIB)(HAC_CONS.o) \
$(LIB)(HATEST.o) 


##################################################################
#
# Embarassingly enough, this lists everything!
#
##################################################################

newadj:		$(O_newadj)

%.o:		%.c
		$(CC) $(FLAGS) $(INCLUDES) -c $?

