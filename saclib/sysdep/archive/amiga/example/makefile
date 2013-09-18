# =========================
#  Makefile for the example
# =========================

CFLAGS  = -ISACLIB:include
LDFLAGS =
MLIB = OBJ:sac${EXTENSION}/main.o -l SACLIB:lib/saclib${EXTENSION}.lib
LIB = -l SACLIB:lib/saclib${EXTENSION}.lib
LIBD = -l SACLIB:lib/saclibd.lib

all: ipfac init itime

ipfac: ipfac.o
        ${CC} $(LDFLAGS) ipfac.o $(MLIB) -o ipfac

init: init.o
        ${CC} $(LDFLAGS) init.o $(LIB) -o init

itime: itime.o
        ${CC} $(LDFLAGS) itime.o $(MLIB) -o itime

