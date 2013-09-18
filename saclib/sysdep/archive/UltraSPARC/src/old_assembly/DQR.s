!
!                     DQR(a1,a0,b;q,r)                                
! [Digit quotient and remainder.  a1, a0 and b are BETA-integers with 
! a1*a0 >= 0 and abs(b) > abs(a1).  q is the integral part of       
! (a1*BETA+a0)/b and r is (a1*BETA+a0)-b*q.  q and r are        
! BETA-integers.]                                                         
!
! 	Replacement routine for DQR.ald
!
!  Variables:  a1  b   a'1    a'0    b'   q'   q     r  loopcounter  temp
!  Registers:          o0     o1     o2   g3  [o3]  [o4]    g5        o5
!
!  Also, register g4 is used for the constant 2^29.
!        Register g1 is used for the sign of (a1 * BETA + a0) and the
!        sign of b.  Register g2 is used for 2*b.
!
! This version of DQR is written for the UNIX assembler running on the
! Sun Workstation SPARC architecture.
! The original assembly code was written by Todd Torgersen.
! Jeremy Johnson
!
	.seg	"text"
	.global	DQR
DQR:
	! Get the operands from memory (indirect).
	mov	%o0,%o0
	mov	%o1,%o1
	mov	%o2,%o2
	!  Take the absolute value a1, a0, and b.
	orcc	%o0,%o1,%g1	! if either a1 or a0 is negative.
	bpos	1f
	sethi   %hi(0x60000000), %g4  ! Delay slot: initialize %g4 = 2^29.
	sub	%g0,%o0,%o0	! Negate both since a0 and a1 have the
	sub	%g0,%o1,%o1	! same sign.
1:	tst	%o2
	bge	2f
	srl	%o2,31,%g2	! Delay slot: Keep sign of b in low order bit.
	sub	%g0,%o2,%o2	! End taking absolute values.
2:	andn	%g1,1, %g1	! Force low order bit of %g1 to 0.
	or	%g1,%g2,%g1	! Pack sign bit of b in low order bit of %g1.
	mov	14, %g5		! Initialize loop counter.
	mov	0, %g3		! Initialize q' = 0.
	add	%o2,%o2,%g2	! Store 2*b in %g2.
!
!       Develop quotient bits two at a time.
!
	sll	%o1,2,%o1	! Skew loop to take advantage of delay slot.
3:				! Begin loop.
	! Shift left (a1*BETA+ao).
	sll	%o0,2,%o0	! Shift a'1.
	srl	%o1,29,%o5	! top bits of a'0, right justified.
	or	%o5,%o0,%o0	! Put in low order positions of a'1.
	andn	%o1,%g4,%o1	! Set 29th and 30th bit of a'0 to 0.
	subcc	%o0,%g2,%g0	! if ( a'1 >= 2*b' )
	bl	7f
	sll	%g3,2,%g3	! Delay slot: shift q'.
	sub	%o0,%g2,%o0	!      a'1 := a'1 - 2*b'
	add	%g3,2,%g3	!      q' := q' + 2
7:	subcc	%o0,%o2,%g0	! if ( a'1 >= b' )
	bl	4f
	subcc	%g5,1,%g5	! Delay slot: Decrement loop counter.
	sub	%o0,%o2,%o0	!      a'1 := a'1 - b'
	add	%g3,1,%g3	!      q' := q' + 1
4:	bg	3b		! Branch back.
	sll	%o1,2,%o1	! Delay slot: Prepare for next iter.
	! Develop the last bit.
	sll	%o0,1,%o0	! Shift a'1.
	srl	%o1,30,%o5	! Get last bit of a'0. 30 because of shift
				! by 2 in the delay slot at end of loop.
	or	%o5,%o0,%o0	! Put in low order positions of a'1.
	subcc	%o0,%o2,%g0	! if ( a'1 >= b' )
	bl	8f
	sll	%g3,1,%g3	! Delay slot: shift q'.
	sub	%o0,%o2,%o0	!      a'1 := a'1 - b'
	add	%g3,1,%g3	!      q' := q' + 1
!       Fix the signs of the output.
8:	tst	%g1		! if ( (a'1* BETA + a'0) < 0 )
	bge	5f
	sll	%g1,31,%g2	! Delay slot: Restore sign bit of b in %g2.
	sub	%g0,%g3,%g3	! q' := -q'
	sub	%g0,%o0,%o0	! a'1 := -a'1
5:	tst	%g2		! if ( b < 0 )
	bge	6f
	st	%o0, [%o4]     ! Delay slot: Send r back (indirect).
	sub	%g0,%g3,%g3	! q' := -q'
6:	st	%g3, [%o3]     ! Send q back (indirect).
LE12:
	retl    ! This is a leaf routine, hence "retl".
	nop     ! Nothing in the delay slot.
	.seg	"data"
