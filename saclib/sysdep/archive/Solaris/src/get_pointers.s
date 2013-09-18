!Sparcstation SLC assembler routines to get the current framepointer
!and the current stackpointer.
!These routines are coded as leaf routines,
!i.e. they do not get their own windows.
!Author: N.J.Nevin, 20 Nov 90

	.seg 	"text"

!     int
!       *get_frame_ptr(void)

	.globl	get_frame_ptr
get_frame_ptr:
	jmpl	%o7+8, %g0		!return to caller
	mov 	%fp, %o0   		!return value is fp (delay slot)
	

!     int
!       *get_stack_ptr(void)

	.globl	get_stack_ptr
get_stack_ptr:
	jmpl	%o7+8, %g0		!return to caller
	mov 	%sp, %o0   		!return value is sp (delay slot)
