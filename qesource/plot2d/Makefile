######################################################
# Makefile for ADJ2D_plot, the program called by
# QEPCADB to render CAD's of R^2.
#
# You may need to adjust the GLBASE, GLUTBASE and
# XLIBDIR variables in order to compile and link on
# your particular system.
######################################################

### X ##################################################
ifeq (${OSTYPE},solaris)
XLIBDIR = /usr/X11R6/lib
XLIBS = -L$(XLIBDIR) -lX11 -lXext -lXmu -lXi
else
XLIBDIR = /usr/X11R6/lib
XLIBS = -L$(XLIBDIR) -lX11 -lXext #-lXmu -lXi
endif

### OPEN GL ##########################################
GLBASE = /usr
GLINCDIR = $(GLBASE)/include
GLLIBDIR = $(GLBASE)/lib
GLLIBS = -L$(GLLIBDIR) -lGLU -lGL

### GLUT ##############################################
GLUTBASE = /usr
GLUTINCDIR = $(GLUTBASE)/include
GLUTLIBDIR = $(GLUTBASE)/lib
GLUTLIBS = -L$(GLUTLIBDIR) -lglut

### INCLUDE & LINK COMMANDS ############################
INCD = -I$(GLINCDIR) -I$(GLUTINCDIR)
LIBS = $(GLUTLIBS) $(GLLIBS) $(XLIBS) -lpthread -lm 

### MAKE THE PROGRAM! ##################################
plot:	
	g++ -O4 $(INCD) plot.cc -o ADJ2D_plot $(LIBS)
