 #################################################################
 # void GETREGSTR(Word register_buff[], Word *num_registers, char **stack_top)
 #################################################################
 # Get the registers.
 # 
 # Outputs
 #   register_buff:  filled with the values of the registers
 #                   which might contain saclib list locations.
 #   num_registers:  the number of registers values stored in 
 #                   the buffer.
 #   stack_top:      the current top-of-stack.
 #
 # Environment
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
 #
 # Remarks
 #   Most probably it would suffice to store only s0-s8.
 #   But to free me from anxiety, I decided to store every 
 #   registers except the followings six registers:
 #       zero, AT, k0, k1, gp, sp
 #
 # Written by Hoon Hong  April 6th 1991
 ################################################################

#include <regdef.h>

	.globl	GETREGSTR	## Prologue.
	.ent	GETREGSTR
GETREGSTR:
	.frame	sp, 0, ra

	sw	v0,   0(a0)	## Store user registers into register_buff. */
	sw	v1,   4(a0)

	sw	a0,   8(a0)
	sw	a1,  12(a0)
	sw	a2,  16(a0)
	sw	a3,  20(a0)

	sw	t0,  24(a0)
	sw	t1,  28(a0)
	sw	t2,  32(a0)
	sw	t3,  36(a0)
	sw	t4,  40(a0)
	sw	t5,  44(a0)
	sw	t6,  48(a0)
	sw	t7,  52(a0)

	sw	s0,  56(a0)
	sw	s1,  60(a0)
	sw	s2,  64(a0)
	sw	s3,  68(a0)
	sw	s4,  72(a0)
	sw	s5,  76(a0)
	sw	s6,  80(a0)
	sw	s7,  84(a0)

	sw	t8,  88(a0)
	sw	t9,  92(a0)

	sw	s8,  96(a0)

	sw	ra, 100(a0)

	li	t0, 26		## Store 26 into num_register. */
	sw	t0, 0(a1)
        
   	or	t0, sp, 0	## Store the top-of-stack adddress. */
	sw	t0, 0(a2)

	j	ra		## Epillogue.
	.end GETREGSTR
