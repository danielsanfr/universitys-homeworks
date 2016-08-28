# factorial funcition
factorial:
	pushl	%ebp
	movl	%esp, %ebp
	
	subl	$16, %esp
	movl	$1, -4(%ebp)
	
	jmp	.L2

.L3:
	movl	-4(%ebp), %eax
	imull	8(%ebp), %eax
	
	movl	%eax, -4(%ebp)
	subl	$1, 8(%ebp)

.L2:
	cmpl	$1, 8(%ebp)
	jg	.L3
	
	movl	-4(%ebp), %eax
	
	leave
	ret
# factorial funcition end

.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function

main:
	push	%ebp
	mov	%esp, %ebp
	
	push	$5
	call	factorial
	
	push	%eax
	
	push	$.LC0
	call	printf
	
	leave
	ret
