! DPRNN(a,b;c,d)
! [Digit product, non-negative.  a and b are non-negative beta-digits.  
! c and d are the unique beta-digits such that a*b=c*beta+d and c*d>=0.]
! This version of DPRNN is written for the SPARC V9 architecture.
! Author:  Jeremy Johnson
! Written:  Oct. 12, 1997
!
	.seg	"text"
	.global	DPRNN
DPRNN:
	! Get the operands from memory (indirect).
	mov	%o0,%o0
	mov	%o1,%o1
	mulx    %o0,%o1,%o0
        srlx    %o0,29,%o1     ! Extract c and d.
        sllx    %o0,35,%o0
        srlx    %o0,35,%o0
  	st	%o0, [%o3]     ! Send least significant bits back.
	st	%o1, [%o2]     ! Send most significant bits back.
	retl    ! This is a leaf routine, hence "retl".
	nop     ! Nothing in the delay slot.
	.seg	"data"
