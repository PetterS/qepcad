! DPRNN(a,b;c,d)
! [Digit product, non-negative.  a and b are non-negative beta-digits.  
! c and d are the unique beta-digits such that a*b=c*beta+d and c*d>=0.]
! This version of DPR is written for the SPARC V8 architecture.
! Author:  Jeremy Johnson
! Written:  Nov. 7, 1997

	.seg	"text"
	.global	DPRNN
DPRNN:
	! Get the operands from memory (indirect).
	mov	%o0,%o0
	mov	%o1,%o1
        mov     %o0, %y         ! Load the y register in the delay slot.
	andcc	%g0, %g0 ,%o4   ! Zero the partial product and clear N and V.
	!                         
	! 29 bit multiply
	!
	mulscc	%o4, %o1, %o4  ! 1st iteration.
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4  ! 10th iteration.
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4  ! 20th iteration.
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4
	mulscc	%o4, %o1, %o4  ! 29th iteration.
	mulscc	%o4, %g0, %o4  ! The last iteration does necessary shift.
	rd	%y, %g1        ! Read the y register. Least significant bits.
	srl	%g1, 3, %g1    ! Right justify the 29 bits.
4:	st	%g1, [%o3]     ! Send least significant bits back.
	st	%o4, [%o2]     ! Send most significant bits back.
LE12:
	retl    ! This is a leaf routine, hence "retl".
	nop     ! Nothing in the delay slot.
	.seg	"data"
