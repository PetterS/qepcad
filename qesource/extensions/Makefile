##################################################################
#
# Master Makefile for my extensions to QEPCAD.
#
##################################################################

both:	opt deb

opt:	
	@echo Making the optimized libraries ...
	cd sfext; $(MAKE)
	cd adj2d; $(MAKE)
	cd rend ; $(MAKE)
	cd newadj; $(MAKE)
	cd lift2D; $(MAKE)


deb:	
	@echo Making the debugging libraries ...
	cd sfext; $(MAKE) "deb=x"
	cd adj2d; $(MAKE) "deb=x"
	cd rend ; $(MAKE) "deb=x"
	cd newadj; $(MAKE) "deb=x"
	cd lift2D; $(MAKE) "deb=x"

