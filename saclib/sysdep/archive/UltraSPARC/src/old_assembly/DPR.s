!
! DPR(a,b;c,d)
! [Digit product.  a and b are beta-digits.  c and d are the unique
! beta-digits such that a*b=c*beta+d and c*d>=0.]
! This version of DPR is written for the UNIX assembler running on the
! Sun SPARC version 9 architecture.
! Author:  Jeremy Johnson
! Written:  Oct. 12, 1997
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
        sllx    %o0,32,%o0      ! Extend sign
        srax    %o0,32,%o0
	sub	%g0,%o0,%o0	
1:	tst	%o1
	bge	2f
	nop                     ! Do nothing in the delay slot
        sllx    %o1,32,%o1      ! Extend sign
        srax    %o1,32,%o1
	sub	%g0,%o1,%o1	! 
2:	
	mulx    %o0,%o1,%o0
        srlx    %o0,29,%o1
        sllx    %o0,35,%o0
        srlx    %o0,35,%o0
       
!       Fix the signs of the output.
	tst	%o5
	bge	4f
	nop	! Nothing in the delay slot.
	sub	%g0, %o0,%o0
	sub	%g0, %o1,%o1
4:	st	%o0, [%o3]     ! Send least significant bits back.
	st	%o1, [%o2]     ! Send most significant bits back.
LE12:
	retl    ! This is a leaf routine, hence "retl".
	nop     ! Nothing in the delay slot.
	.seg	"data"
