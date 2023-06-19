# This program prints out a danish flag, by
# looping through the rows and columns of the flag.
# Each element inside the flag is a single character.
# (i.e., 1 byte).
#
# (Dette program udskriver et dansk flag, ved at
# sløjfe gennem rækker og kolonner i flaget.)
#

# Constants
FLAG_ROWS = 6
FLAG_COLS = 12

# Registers:
# - row in $t0
# - col in $t1
main:
main__row_loop_init:                    # for (int row = 0; row < FLAG_ROWS; row++) {
	li	$t0, 0                  # row = 0

	main__row_loop_body:            # while (row < FLAG_ROWS)
	bge	$t0, FLAG_ROWS, main__row_loop_end

	main__col_loop_init:            # for (int col = 0; col < FLAG_COLS; col++) {
	li	$t1, 0                  # col = 0;

	main__col_loop_body:            # while (col < FLAG_COLS)
	bge	$t1, FLAG_COLS, main__col_loop_end





	la	$t2, flag		# Find address of row (step 1)
	mul	$t3, $t0, FLAG_COLS
	add	$t4, $t2, $t3

	add	$t5, $t4, $t1		# Find address of cell in row (step 2)

	lb	$a0, ($t5)		# Access value of cell





	li	$v0, 11                 # printf("%c", flag[row][col])
	syscall

	main__col_loop_iter:
	addi	$t1, $t1, 1             # col++
	j	main__col_loop_body

	main__col_loop_end:
	main__row_loop_iter:
	li	$a0, '\n'               # printf("%c", '\n')
	li	$v0, 11
	syscall
	addi	$t0, $t0, 1             # row++
	j	main__row_loop_body

	main__row_loop_end:
					# End of the program.
	li	$v0, 0                  # return 0
	jr	$ra

.data
# This label inside the data region refers to the bytes of the flag.
# Note that even thought the bytes are listed on separate lines,
# they are actually stored as a single contiguous chunk or 'string' in memory.
flag:
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
