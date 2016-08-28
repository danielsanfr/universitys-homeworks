prime:
	push	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	cmpl	$1, 8(%ebp)
	jg	.L2
	movl	$0, %eax
	jmp	.L3

.L2:
	movl	$2, -4(%ebp)
	jmp	.L4

.L6:
	movl	8(%ebp), %eax
	cltd
	idivl	-4(%ebp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L5
	movl	$0, %eax
	jmp	.L3

.L5:
	addl	$1, -4(%ebp)

.L4:
	movl	-4(%ebp), %eax
	imull	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	.L6
	movl	$1, %eax

.L3:
	leave
	ret

.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
	
main:
	push	%ebp
	movl	%esp, %ebp

	push	$7
	call	prime

	push	%eax
	push	$.LC0
	call	printf

	leave
	ret
