#
# FILE
#   Makefile for SACLIB User's Guide.
#

SACSRC = \
saclib.tex\
cAN.tex\
cAsI.tex\
cAsIA.tex\
cAsMA.tex\
cAsRA.tex\
cCFC.tex\
cGCD.tex\
cI.tex\
cISAC.tex\
cLA.tex\
cLP.tex\
cNIWsCGV.tex\
cNIWsGC.tex\
cPAsDIPA.tex\
cPAsI.tex\
cPAsIPA.tex\
cPAsMPA.tex\
cPAsMR.tex\
cPAsPIO.tex\
cPAsRPA.tex\
cPF.tex\
cRRC.tex\
fLIST.tex\
fSPACE.tex

# Files to be made.

guide: ../saclib.dvi ../saclocal.dvi

kwic:  ../sackwic.dvi

all: guide kwic

# The User's guide.

../saclib.dvi: $(SACSRC) saclib.sty saclib.ind
	latex saclib.tex
	latex saclib.tex
	mv saclib.dvi ../saclib.dvi

# The local guide.

../saclocal.dvi: saclocal.tex saclib.sty
	latex saclocal.tex
	latex saclocal.tex
	mv saclocal.dvi ../saclocal.dvi

# The KWIC index.

../sackwic.dvi: sackwic.tex KWIC.tex saclib.sty
	latex sackwic.tex
	mv sackwic.dvi ../sackwic.dvi

KWIC.tex:
	${saclib}/bin/mktexkwic

# The index file.
# Requires 'makeindex'.

saclib.ind: $(SACSRC) saclib.sty
	latex saclib.tex
	latex saclib.tex
	makeindex saclib.idx

# Cleanup.

clean:
	rm *.err *.log *.dvi *.aux *.toc *.lof *.lot *.idx cor[e]
