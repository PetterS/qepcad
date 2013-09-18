##################################################################
#
# Master Makefile for QEPCAD with extensions.
#
# This simply calls qepcad's make, and the master-make for the
# extensions.
##################################################################
SHELL = /bin/csh
MAKE       =  make  # You must use gmake, but it may not be
                    # called gmake on your system, so change this

CCo        =  g++
FLAGSo = -O4

CCd        =  g++
FLAGSd = -g

MFlags	= "CCo=${CCo}" "FLAGSo=${FLAGSo}"\
          "CCd=${CCd}" "FLAGSd=${FLAGSd}"\
          "MAKE=${MAKE}"

both:   opt deb

opt:
	@echo Making the optimized libraries ...
	cd extensions; ${MAKE} opt ${MFlags}
	@echo Making optimized qepcad
	cd source; ${MAKE} opt ${MFlags}

deb:
	@echo Making the debugging libraries ...
	cd extensions; ${MAKE} deb ${MFlags}
	@echo Making debugging qepcad
	cd source; ${MAKE} deb ${MFlags}

clean:	
	pushd >/dev/null source ; 'rm' -f qepcad qepcadd qepcad.a qepcadd.a ; popd >/dev/null
	pushd >/dev/null extensions ; 'rm' -f */*.a ; popd >/dev/null
	pushd >/dev/null plot2d ; 'rm' -f ADJ_2D_plot ; popd >/dev/null
	pushd >/dev/null cad2d ; 'rm' -f cad2d cad2dd cad2d.a cad2dd.a ; popd >/dev/null
