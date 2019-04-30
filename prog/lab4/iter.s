	.file	"iter.c"
	.text
	.p2align 4,,15
	.globl	sum_arr_iter
	.type	sum_arr_iter, @function
sum_arr_iter:
.LFB23:
	.cfi_startproc
	testl	%esi, %esi
	je	.L4
	movslq	%esi, %rax
	subl	$1, %esi
	salq	$2, %rax
	salq	$2, %rsi
	leaq	-4(%rdi,%rax), %rcx
	leaq	-8(%rdi,%rax), %rax
	subq	%rsi, %rax
	movq	%rax, %rsi
	movl	%edx, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	addl	(%rcx), %eax
	subq	$4, %rcx
	cmpq	%rsi, %rcx
	jne	.L3
	rep ret
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	sum_arr_iter, .-sum_arr_iter
	.p2align 4,,15
	.globl	sum_arr
	.type	sum_arr, @function
sum_arr:
.LFB24:
	.cfi_startproc
	testl	%esi, %esi
	je	.L10
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
.L9:
	addl	(%rdx), %eax
	subq	$4, %rdx
	cmpq	%rcx, %rdx
	jne	.L9
	rep ret
	.p2align 4,,10
	.p2align 3
.L10:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	sum_arr, .-sum_arr
	.p2align 4,,15
	.globl	fib_iter
	.type	fib_iter, @function
fib_iter:
.LFB25:
	.cfi_startproc
	cmpl	%ecx, %edx
	jne	.L14
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L16:
	movl	%eax, %edi
.L14:
	addl	$1, %edx
	leal	(%rdi,%rsi), %eax
	movl	%edi, %esi
	cmpl	%ecx, %edx
	jne	.L16
	rep ret
	.p2align 4,,10
	.p2align 3
.L17:
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE25:
	.size	fib_iter, .-fib_iter
	.p2align 4,,15
	.globl	fib
	.type	fib, @function
fib:
.LFB26:
	.cfi_startproc
	testl	%edi, %edi
	je	.L21
	movl	$1, %esi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L22:
	movl	%eax, %ecx
.L20:
	addl	$1, %edx
	leal	(%rcx,%rsi), %eax
	movl	%ecx, %esi
	cmpl	%edx, %edi
	jne	.L22
	rep ret
	.p2align 4,,10
	.p2align 3
.L21:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE26:
	.size	fib, .-fib
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
