.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function

main:
	pushl %ebp
	movl %esp, %ebp

	subl $48, %esp
	movl $1, 28(%esp)
	movl $2, 32(%esp)
	movl $3, 36(%esp)
	movl $4, 40(%esp)
	movl $5, 44(%esp)
	movl $0, 24(%esp)
	movl $0, 20(%esp)
	jmp .L2
	
.L3:
	movl 20(%esp), %eax
	movl 28(%esp,%eax,4), %eax
	addl %eax, 24(%esp) 
	addl $1, 20(%esp)

.L2:
	cmpl $4, 20(%esp)
	jle .L3

	movl 24(%esp), %eax
	push %eax
	push $.LC0
	call printf

	leave
	ret
