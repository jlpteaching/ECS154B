	ori	$1, $0, 1	# $1 = 1
	add	$2, $1, $1	# $2 = 2. forwarding both ALU inputs from same source
	xor	$3, $1, $2	# $3 = 3. forwarding both ALU inputs from different sources
	addi	$4, $3, 14	# $4 = 17. forwarding only A value
	and	$5, $1, $3	# $5 = 1. forwarding only B value
	sw	$4, 11($5)	# memory[12] = 17. need to forward both $4 and $5
	lw	$6, 11($5)	# $6 = 17. forward $5
	and	$7, $6, $4	# $7 = 17. stall or forward
	beq	$7, $1, begin	# not taken. forward $7 or stall
	slt	$8, $6, $7	# $8 = 0. forward $7 and $6
	beq	$8, $8, begin	# taken. forward $8 or stall
	addi	$28, $0, -1	# should not execute
begin:	addi	$9, $0, 1	# $9 = 1
	lw	$10, 12($0)	# $10 = 17
	sw	$10, 19($10)	# memory[36] = 17. forward $10 or stall
	lw	$10, 12($0)	# $10 = 17
	beq	$10, $1, begin	# must stall for $10. not taken
	jal	middle	# $31 = 72
	addi	$27, $0, -1	# should not execute
middle:	addi	$31, $31, 24	# $31 = 96
	sw	$31, 0($0)	# memory[0] = 96
	lw	$11, 0($0)	# $11 = 96
	jr	$11	# must stall here
	addi	$26, $0, -1	# should not execute
end:	j	end	# infinite loop to mark we are done
	addi	$25, $0, -1	# should not execute
	addi	$24, $0, -1	# should not execute