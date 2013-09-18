!
! DPR(a,b;c,d)
! [Digit product.  a and b are beta-digits.  c and d are the unique
! beta-digits such that a*b=c*beta+d and c*d>=0.]
! This version of DPR is written for the UNIX assembler running on the
! Sun SPARC version 8 architecture.
! Author:  Todd Torgersen
! Last Modified:  Oct. 12, 1997, Jeremy Johnson
!
	.seg	"text"
	.global	DPR
DPR:
	! Get the operands from memory (indirect).
	mov	%o0,%o0
	mov	%o1,%o1
	!  Take the absolute value of the operands, store sign in %o5.
	tst	%o0
	bge	1f
	xor	%o0,%o1,%o5	! Store sign of result in delay slot.
	sub	%g0,%o0,%o0	! it's a SPARC :-)
1:	tst	%o1
	bge	2f
	mov	%o0, %y         ! Load the y register in the delay slot.
	sub	%g0,%o1,%o1	! 
2:	andcc	%g0, %g0 ,%o4   ! Zero the partial product and clear N and V.
	nop			! I don't know why, but this thing does
	!                         not work without this "nop".
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
!       Fix the signs of the output.
	tst	%o5
	bge	4f
	nop	! Nothing in the delay slot.
	sub	%g0, %g1,%g1
	sub	%g0, %o4,%o4
4:	st	%g1, [%o3]     ! Send least significant bits back.
	st	%o4, [%o2]     ! Send most significant bits back.
LE12:
	retl    ! This is a leaf routine, hence "retl".
	nop     ! Nothing in the delay slot.
	.seg	"data"
