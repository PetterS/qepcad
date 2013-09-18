!Sparcstation SLC assembler routine to flush register windows.
!This routine is coded as a leaf routine,
!i.e. it does not get its own window.
!Author: N.J.Nevin: 20 Nov 90

#include </usr/include/sys/trap.h>

	.seg "text"
	
!	void 
!	  flush_windows(void)

	.globl _flush_windows
_flush_windows:
	ta 	ST_FLUSH_WINDOWS		!call software trap to flush
						!register windows to stack
	jmpl 	%o7+8, %g0			!return to caller
	nop					!delay slot
