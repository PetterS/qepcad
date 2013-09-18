 ######################################################
 # void DPR(Word a, Word b, Word *c_, Word *d_)
 ######################################################
 # Digit Product.
 #
 # Inputs
 #   a, b : beta-digits.
 #
 # Outputs
 #   c, d : the unique beta-digits such that a*b = c*beta+d and c*d >= 0.
 #
 # Environement
 #   Processor:         MIPS R2000 or R3000
 #   Assembler:         MIPS Assembler
 #   Operating system:  UNIX
 #   Computer:          DEC station
 #
 # Notes for programmers
 #   Please refer to the following book for further details:
 #              "mips RISC Architecture",
 #                   by Gerry Kane,
 #                   Prentice Hall
 #                 ISBN 0-13-584749-4
 #   Especially Appendix D is helpful.
 #   According to the terminology of the book, this  routine can be 
 #   classified as "leaf without stack storage for local variables".
 #
 # Remarks 
 #   One might investigate the possibility of utilizing the 
 #   branch delay slots.  (though it is not neccessary in this 
 #   case, since the "mult" takes 10 cycles.)
 #
 # Written by Hoon Hong   April 5th 1991
 #######################################################


 #=====================================================#
 #           Register Allocation                       #
 #=====================================================#
#include <regdef.h>
#define 	a	a0
#define 	b	a1
#define 	c_	a2
#define		d_	a3

#define		c	t2
#define		d	t3

#define		high	t0
#define		low	t1

#define		mask	t7

#define		temp0	t4
#define		temp1	t5
#define		temp2	t6


 #=====================================================#
 #          Assembly code                              #
 #=====================================================#


 #-------------------------------------------------------#
	.globl	DPR         		## Define DPR as external.
	.ent	DPR			## Tell debugger this starts DPR.
DPR:					## This is the entry point.
	.frame	sp, 0, ra		## Define frame size, return reg.
 #-------------------------------------------------------#
	mult	a ,b			## Takes 10 cycles, and the following
					## instructios are executed in parallel.
 #-------------------------------------------------------#
	beq	a, zero, ab_zero	## Classifying the cases.
	beq	b, zero, ab_zero	##
	bltz	a, a_negative		##
	bltz	b, ab_negative		## 
 #-------------------------------------------------------#
ab_positive:				## You get here if a * b > 0. 
	addi	temp2, zero, -1		## mask  <-- 0001...1  	
	srl	mask, temp2, 3		## 

	mfhi	high			## Get the result of "mult a, b".
	mflo	low			##

	and	d, low, mask		## d  <--- 000 low28...0
	sll	temp0, high, 3		## c  <--- high28...0 low31..29 
	srl	temp1, low, 29		##
	or	c, temp0, temp1		##
	
	sw	c, 0(c_)		## *c_  <--- c.
	sw	d, 0(d_)		## *d_  <--- d.
	j	ra			## Return to the caller.
 #-------------------------------------------------------#
a_negative:				## Classifying the cases.
	bltz	b, ab_positive	
 #-------------------------------------------------------#
ab_negative:				## You get here if  a * b < 0.
	lui	mask, 0xE000 		## mask  <--- 1110...0 = - beta.
	
	mfhi	high			## Get the result of "mult a, b".
	mflo	low			##
	
	or	d, low, mask		## d  <--- 111 low28...0
	sll	temp0, high, 3		## c  <--- high28...0 low31..29.
	srl	temp1, low, 29		##
	or	c, temp0, temp1		## 

	beq	d, mask, degenerate	## Classifying the subcases.
	#------------------------------------------------#
nondegenerate:				## You get here if d > -beta.
	addi	c, c, 1			## c    <--- c + 1.
	sw	c, 0(c_)		## *c_  <--- c.
	sw	d, 0(d_)		## *d_  <--- d.
	j	ra			## Return to the caller.
	#------------------------------------------------#
degenerate:				## You get here if d = -beta.
	sw	c, 0(c_)		## *c_  <--- c.
	sw	zero, 0(d_)		## *d_  <--- 0.
	j	ra			## Return to the caller.
 #-------------------------------------------------------#
ab_zero:				## You get here if  a * b = 0.
	sw	zero, 0(c_)		## *c_  <--- 0.
	sw	zero, 0(d_)		## *d_  <--- 0.
	j	ra			## Return to the caller. 
 #-------------------------------------------------------#
	.end	DPR			## This the end of the code.
