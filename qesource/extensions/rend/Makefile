##################################################################
#
# Makefile for plot stuff
#
##################################################################

##################################################################
#  This section gives proper values to flags for opt vs. deb
#------------------
ifdef deb
LIB = rendd.a
CCpp = ${CCd}
FLAGS = ${FLAGSd}
else
LIB = rendo.a
CCpp = ${CCo}
FLAGS = ${FLAGSo}
endif
#------------------
##################################################################


INCLUDES  = \
		-I${saclib}/include \
		-I${qe}/source \
		-I${qe}/extensions/sfext \
		-I${qe}/extensions/adj2d \
		-I.


O_rend = \
$(LIB)(LBRNQORD.o) \
$(LIB)(SSILRCRI.o) \
$(LIB)(CONMIRCAD.o) \
$(LIB)(PLOT_2D_CAD.o) \
$(LIB)(PLOT2DCAD2FILE.o) \
$(LIB)(Rend_Sample.o) \
$(LIB)(Rend_Cell.o) \
$(LIB)(Rend_Win.o) \
$(LIB)(ADD_POINTS.o) \
$(LIB)(FILL_2D.o) \
$(LIB)(WRITE_PLOT.o) \
$(LIB)(WRITE_PS.o) \
$(LIB)(WRITE_PS_COLOR.o) \
$(LIB)(WRITE_EPS.o) \
$(LIB)(WRITE_PS_STANDARD.o) \
$(LIB)(WRITE_PS_INTERACTIVE.o) \
$(LIB)(WRITE_PS_RAJI.o) \
$(LIB)(ZOOM_OUT.o) \
$(LIB)(GET_COORDS.o) \
$(LIB)(CH_VIEW_WIN.o) \
$(LIB)(CH_VIEW_WIN_COOR.o) \
$(LIB)(DISP2DCAD.o)


rend:		$(O_rend)

%.o:		%.cc
		$(CCpp) $(FLAGS) $(INCLUDES) -c $?

%.o:		%.c
		$(CCpp) $(FLAGS) $(INCLUDES) -c $?
