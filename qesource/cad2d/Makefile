#############################################################################
#
#  Makefile for qepcad system.
#
#  (c) Copyright 1994 Research Institute for Symbolic Computation  
#                     Hoon Hong
#
#############################################################################


# ======================================================
#      Adjust these during installation
#      Note: These settings are overridden by any
#      settings in a "make" that calls this recursively
# ======================================================
CCo        =  g++
linkCCo    =  g++
FLAGSo = -O4

CCd        =  g++
linkCCd    =  g++
FLAGSd = -g -DNO_SACLIB_MACROS

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
		-I${qe}/source \
		${SPECIFLAGS} \
		-I.

EXTLIBS   =	${qe}/source/qepcad.a \
		${qe}/extensions/sfext/sfexto.a \
		${qe}/extensions/lift2D/lift2Do.a \
		${qe}/extensions/newadj/newadjo.a \
		${qe}/extensions/adj2d/adj2do.a \
		${qe}/extensions/rend/rendo.a \
		${qe}/extensions/sfext/sfexto.a \
		${qe}/source/qepcad.a \
		${saclib}/lib/saclibo.a \
		-lreadline \
		${SPECLFLAGS}


EXTLIBSD  =	${qe}/source/qepcadd.a \
		${qe}/extensions/sfext/sfextd.a \
		${qe}/extensions/lift2D/lift2Dd.a \
		${qe}/extensions/newadj/newadjd.a \
		${qe}/extensions/adj2d/adj2dd.a \
		${qe}/extensions/rend/rendd.a \
		${qe}/extensions/sfext/sfextd.a \
		${qe}/source/qepcadd.a \
		${saclib}/lib/saclibd.a \
		-lreadline \
		${SPECLFLAGS}


NAME      =  cad2d
LIB       =  $(NAME).a
LIBD      =  $(NAME)d.a
EXE       =  $(NAME)
EXED      =  $(NAME)d

OBJS = \
src/CAD2D.o \
src/CONSTRUCT.o \
src/MAIN.o \
src/PROJECT.o \
src/PRINTCAD2DBANNER.o \
src/TICAD.o


# ============================================================
#     Dependecies
# ============================================================

DEPENDENCIESo =    $(LIB)($(OBJS))

DEPENDENCIESd =    $(LIBD)($(OBJS))

# ============================================================
#     Make rules
# ============================================================
both:		opt deb

opt:		override CFLAGS = $(FLAGSo)
opt:		override CC = $(CCo)
opt:		$(DEPENDENCIESo)
		ranlib $(LIB)
		@echo Linking the optimized program......
		$(linkCCo) $(FLAGSo) $(INCLUDES) -o $(EXE) ../source/saclib/GCSI.c \
			$(LIB) $(EXTLIBS) $(LIB) $(EXTLIBS)

deb:		override CFLAGS = $(FLAGSd)
deb:		override CC = $(CCd)
deb:		$(DEPENDENCIESd)
		ranlib $(LIBD)
		@echo Linking the debugged program......
		$(linkCCd) $(FLAGSd) $(INCLUDES) -o $(EXED) ../source/saclib/GCSI.c \
			$(LIBD) $(EXTLIBSD) $(LIBD)  $(EXTLIBSD) 

.c.o:	
		$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<

