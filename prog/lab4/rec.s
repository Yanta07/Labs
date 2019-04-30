	.file	"rec.c"
	.text
	.p2align 4,,15
	.globl	sum_arr_rec
	.type	sum_arr_rec, @function
sum_arr_rec:
.LFB23:
	.cfi_startproc
	testl	%esi, %esi
	je	.L4
	movslq	%esi, %rax
	salq	$2, %rax
	leaq	-8(%rdi,%rax), %rcx
	leaq	-4(%rdi,%rax), %rdx
	leal	-1(%rsi), %eax
	salq	$2, %rax
	subq	%rax, %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	addl	(%rdx), %eax
	subq	$4, %rdx
	cmpq	%rcx, %rdx
	jne	.L3
	rep ret
	.p2align 4,,10
	.p2align 3
.L4:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	sum_arr_rec, .-sum_arr_rec
	.p2align 4,,15
	.globl	fib_rec
	.type	fib_rec, @function
fib_rec:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	testl	%edi, %edi
	je	.L11
	cmpl	$1, %edi
	movl	%edi, %ebx
	je	.L12
	xorl	%ebp, %ebp
.L9:
	leal	-1(%rbx), %edi
	call	fib_rec
	addl	%eax, %ebp
	subl	$2, %ebx
	je	.L7
	cmpl	$1, %ebx
	jne	.L9
	addl	$1, %ebp
.L7:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	%ebp, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	.cfi_restore_state
	xorl	%ebp, %ebp
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	%ebp, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	.cfi_restore_state
	movl	$1, %ebp
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movl	%ebp, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	fib_rec, .-fib_rec
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
