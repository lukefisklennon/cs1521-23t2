# Sum 4 numbers using function calls.
# Note the use of the stack to save $ra in main,
# and $ra $a0, $a1, $s0 in sum2.
# For simplicity we are not using a frame pointer
# Only push/pop are needed for this.

main:
        push    $ra             # move stack pointer down to make room
                                # save $ra on $stack


        li      $a0, 11         # int result = sum4(11, 13, 17, 19);
        li      $a1, 13
        li      $a2, 17
        li      $a3, 19
        jal     sum4

        move    $a0, $v0        # printf("%d", result);
        li      $v0, 1
        syscall

        li      $a0, '\n'       # printf("%c", '\n');
        li      $v0, 11
        syscall

        pop     $ra             # recover $ra from $stack
                                # move stack pointer back up to what it was when main called
                                # equivalent to `pop $ra`

        li      $v0, 0          # return 0 from function main
        jr      $ra             # return from function main

# Adds 4 numbers together and returns the result.
#
# Used:         [$s2, $s3, $s4, $s5]
# Clobbered:    [$a0, $a1]
# Stack:        [$ra, $s2, $s3, $s4, $s5]
#
# Arguments:
# - $a0 = a
# - $a1 = b
# - $a2 = c
# - $a3 = d
#
# Registers:
# - $s2 = c
# - $s3 = d
# - $s4 = res1
# - $s5 = res2
sum4:
sum4__prologue:
	push	$ra	# Backup registers that we may clobber
	push	$s2
	push	$s3
	push	$s4
	push	$s5

sum4__body:
	move	$s2, $a2   # Save arguments before they potentially get
	move	$s3, $a3   # clobbered by function calls below

	jal	sum2	   # int res1 = sum2(a, b);
	move	$s4, $v0   # Save result

	move	$a0, $s2   # int res2 = sum2(c, d);
	move	$a1, $s3
	jal	sum2
	move	$s5, $v0   # Save result

	move	$a0, $s4   # int temp = sum2(res1, res2);
	move	$a1, $s5
	jal	sum2

sum4__epilogue:
	pop	$s5	# Restore registers so that everything is back to how it
	pop	$s4     # was before we return
	pop	$s3
	pop	$s2
	pop	$ra

	jr	$ra	# Jump back to the caller function

# Add 2 numbers together and return the result.
#
# Arguments:
# - $a0 = x
# - $a1 = y
sum2:
	add	$v0, $a0, $a1	# int temp = x + y;
	jr	$ra		# return temp;
