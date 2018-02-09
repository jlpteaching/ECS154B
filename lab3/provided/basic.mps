# To have it so that no forwarding occurs:
# there must be a gap of 5 instructions between
# when an instruction that writes to a register and when it is used.

	addi	$1, $0, 1	# $1 = 1
	addi	$2, $0, 2	# $2 = 2
	ori	$3, $0, 3	# $3 = 3
	ori	$4, $0, 4	# $4 = 4
	addi	$5, $0, 5	# $5 = 5
	addi	$6, $0, 6	# $6 = 6
	addi	$7, $0, 7	# $7 = 7
	sw	$1, 12($0)	# memory[12] = 1
	add	$8, $1, $2	# $8 = 3
	lw	$15, 9($3)	# $15 = 1
	and	$9, $1, $2	# $9 = 0
	sub	$10, $4, $2	# $10 = 2
	or	$11, $5, $3	# $11 = 7
	xor	$12, $7, $6	# $12 = 1
	slt	$13, $5, $6	# $13 = 1
	slt	$14, $6, $5	# $14 = 0
	andi	$16, $1, 1	# $16 = 1
	sll	$17, $1, 10	# $17 = 1024
	srl	$18, $7, 2	# $18 = 1