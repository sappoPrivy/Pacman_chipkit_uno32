  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Modified 2023 by Tenzin Sangpo Choedon
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.
  
  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
 .data
 .align 2
 .text
 # Allows these labels to be accessed and used in other files
 .global hexasc
 .global delay
 .global time2string
 .global enable_interrupt

enable_interrupt:
	# Enable interrupt globally
	ei
	# Jump to return adress
	jr $ra

# Convert input numbers to ascii characters
hexasc:

	andi $t0,$a0,0xf	# save the 4 least bits in t0
	ble $t0, 9, jump	# branch if input less than or equal to 9
	addi  $v0, $t0, 0x37	# add 7 to t0 if t0 is more than 9
	jr $ra			# return adress

	# Convert the numbers from 0 - 9 to the hexadecimal value for ASCII characters
	jump:
		addi $v0, $t0, 0x30	# Add 0x30 to get hexadecimal representation of numbers
		jr $ra			# return adress
	
delay:
	addi	$t1, $0, 10000

	ble	$a0, 0, done     # om ms är mindre eller lika med 0 så branch
	nop
	while:
		addi	$a0,$a0, -1       # ms = ms - 1

		addi	$t0, $0, 0        # i = 0
	for:
		addi	$t0,$t0,1
		ble	$t0,$t1, for       # i < 4711
		nop

		bgt	$a0,0,while        # while ms > 0
		nop

	done:      
		jr $ra 
		nop


time2string:
	
	PUSH $ra		# Add ra to the stack
	PUSH $s0		# Add s0 to the stack
	PUSH $s1		# Add s1 to the stack
	
	move	$s0, $a0	# Copy of the output $a0
	move	$s1, $a1	# Copy of the input $a1
	
	# First digit			
	andi	$a0, $s1, 0xf000	
	srl	$a0, $a0, 12
	jal	hexasc
	nop
	sb	$v0, 0($s0)	
	
	# Second digit
	andi	$a0, $s1, 0x0f00	
	srl	$a0, $a0, 8
	jal	hexasc
	nop
	sb	$v0, 1($s0)
	
	# Colon
	li	$a0, 0x3a
	sb	$a0, 2($s0)

	# Third digit
	andi	$a0, $s1, 0x00f0	
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0, 3($s0)
	
	# Fourth digit
	andi	$a0, $s1, 0x000f
	move	$a0, $a0
	jal	hexasc
	nop
	sb	$v0, 4($s0)
	
	andi	$a0, $s1, 0xff00
	beq	$a0, $0, hourtest
	nop
	
	# Null byte
	li	$a0, 0x00
	sb	$a0, 5($s0)
	
	POP	$s1
	POP	$s0
	POP	$ra
	
	jr	$ra
	nop

	hourtest:
	andi	$a0, $s1, 0x00ff
	beq	$a0, $0, hour
	nop
	
	# Remove the registers from the stack
	POP $s1
	POP $s0
	POP $ra
	
	jr	$ra
	nop
	
	hour:
		li	$a0, 0x48
		sb	$a0, 0($s0)
		li	$a0, 0x4f
		sb	$a0, 1($s0)
		li	$a0, 0x55
		sb	$a0, 2($s0)
		li	$a0, 0x52
		sb	$a0, 3($s0)
		li	$a0, 0x00
		sb	$a0, 4($s0)
	
		
		POP	$s1
		POP	$s0
		POP	$ra
	
		jr	$ra
		nop
	

