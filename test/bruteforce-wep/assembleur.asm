	.file	"main.c"
	.text
	.p2align 4,,15
	.globl	read_packet
	.type	read_packet, @function
read_packet:
.LFB21:
	.cfi_startproc
	movq	%rbx, -48(%rsp)
	movq	%rbp, -40(%rsp)
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	movq	%rdi, %rbx
	movq	%r12, -32(%rsp)
	movq	%r14, -16(%rsp)
	.cfi_offset 12, -40
	.cfi_offset 14, -24
	movl	%edx, %r14d
	movq	%r15, -8(%rsp)
	movq	%r13, -24(%rsp)
	subq	$104, %rsp
	.cfi_def_cfa_offset 112
	.cfi_offset 15, -16
	.cfi_offset 13, -32
	movzwl	24(%rsi), %eax
	leal	-28(%rdx), %r15d
	movzbl	27(%rsi), %r13d
	movq	%rsi, %rbp
	subl	$32, %r14d
	movl	%r15d, %edx
	movq	%rdx, %rdi
	movw	%ax, 16(%rsp)
	movzbl	26(%rsi), %eax
	shrb	$6, %r13b
	movq	%rdx, 8(%rsp)
	movb	%al, 18(%rsp)
	call	malloc
	movq	8(%rsp), %rdx
	leaq	28(%rbp), %rsi
	movq	%rax, %rdi
	movq	%rax, %r12
	addq	%r12, %r14
	call	memcpy
	movb	%r13b, 19(%rsp)
	movq	16(%rsp), %rax
	movl	%r15d, 32(%rsp)
	movq	%r12, 8(%rbx)
	movq	%r14, 24(%rbx)
	movq	64(%rsp), %rbp
	movq	%rax, (%rbx)
	movq	32(%rsp), %rax
	movq	72(%rsp), %r12
	movq	80(%rsp), %r13
	movq	88(%rsp), %r14
	movq	96(%rsp), %r15
	movq	%rax, 16(%rbx)
	movq	%rbx, %rax
	movq	56(%rsp), %rbx
	addq	$104, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE21:
	.size	read_packet, .-read_packet
	.p2align 4,,15
	.globl	copy_packet
	.type	copy_packet, @function
copy_packet:
.LFB22:
	.cfi_startproc
	movq	%rbx, -48(%rsp)
	movq	%rbp, -40(%rsp)
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	movq	%rdi, %rbx
	movq	%r12, -32(%rsp)
	movq	%r13, -24(%rsp)
	movq	%rsi, %rbp
	movq	%r14, -16(%rsp)
	movq	%r15, -8(%rsp)
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movl	16(%rsi), %r13d
	movzbl	3(%rsi), %r15d
	movl	%r13d, %r14d
	movq	%r14, %rdi
	call	malloc
	movq	8(%rbp), %rsi
	movq	%r14, %rdx
	movq	%rax, %rdi
	movq	%rax, %r12
	call	memcpy
	movzwl	0(%rbp), %eax
	movb	%r15b, 3(%rsp)
	movl	%r13d, 16(%rsp)
	subl	$4, %r13d
	movq	%r12, 8(%rbx)
	addq	%r12, %r13
	movq	72(%rsp), %r14
	movq	56(%rsp), %r12
	movq	%r13, 24(%rbx)
	movq	80(%rsp), %r15
	movw	%ax, (%rsp)
	movzbl	2(%rbp), %eax
	movq	64(%rsp), %r13
	movq	48(%rsp), %rbp
	movb	%al, 2(%rsp)
	movq	(%rsp), %rax
	movq	%rax, (%rbx)
	movq	16(%rsp), %rax
	movq	%rax, 16(%rbx)
	movq	%rbx, %rax
	movq	40(%rsp), %rbx
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	copy_packet, .-copy_packet
	.p2align 4,,15
	.globl	recopy_packet
	.type	recopy_packet, @function
recopy_packet:
.LFB23:
	.cfi_startproc
	movq	8(%rsi), %rax
	movl	16(%rsi), %edx
	movq	8(%rdi), %rsi
	movq	%rax, %rdi
	jmp	memcpy
	.cfi_endproc
.LFE23:
	.size	recopy_packet, .-recopy_packet
	.p2align 4,,15
	.globl	free_wep_packet
	.type	free_wep_packet, @function
free_wep_packet:
.LFB24:
	.cfi_startproc
	movq	8(%rdi), %rdi
	jmp	free
	.cfi_endproc
.LFE24:
	.size	free_wep_packet, .-free_wep_packet
	.p2align 4,,15
	.globl	init_buffer
	.type	init_buffer, @function
init_buffer:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$256, %edi
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	call	malloc
	movq	%rax, %r10
	movq	%rax, %r8
	negq	%r10
	movl	%r10d, %edi
	andl	$15, %edi
	je	.L15
	xorl	%ecx, %ecx
	movl	$255, %r9d
	.p2align 4,,10
	.p2align 3
.L9:
	leal	1(%rcx), %edx
	movl	%r9d, %esi
	movb	%cl, (%rax)
	subl	%ecx, %esi
	addq	$1, %rax
	cmpl	%edx, %edi
	movl	%edx, %ecx
	ja	.L9
.L8:
	movq	%r10, %rcx
	movl	$256, %r10d
	subl	%edi, %r10d
	andl	$15, %ecx
	movl	%r10d, %edi
	shrl	$4, %edi
	movl	%edi, %r9d
	sall	$4, %r9d
	testl	%r9d, %r9d
	je	.L10
	leal	1(%rdx), %eax
	movl	%edx, (%rsp)
	addq	%r8, %rcx
	movd	(%rsp), %xmm2
	movl	%eax, 4(%rsp)
	leal	2(%rdx), %eax
	movd	4(%rsp), %xmm5
	movl	%eax, 8(%rsp)
	leal	3(%rdx), %eax
	movd	8(%rsp), %xmm0
	punpckldq	%xmm5, %xmm2
	movl	%eax, 12(%rsp)
	xorl	%eax, %eax
	movd	12(%rsp), %xmm1
	movdqa	.LC0(%rip), %xmm6
	punpckldq	%xmm1, %xmm0
	movdqa	.LC1(%rip), %xmm3
	punpcklqdq	%xmm0, %xmm2
	.p2align 4,,10
	.p2align 3
.L11:
	movdqa	%xmm2, %xmm0
	addl	$1, %eax
	movdqa	%xmm2, %xmm5
	paddd	%xmm3, %xmm0
	movdqa	%xmm2, %xmm4
	movdqa	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm5
	paddd	%xmm6, %xmm2
	punpckhwd	%xmm0, %xmm4
	paddd	%xmm3, %xmm1
	movdqa	%xmm5, %xmm0
	punpckhwd	%xmm4, %xmm5
	punpcklwd	%xmm4, %xmm0
	movdqa	%xmm1, %xmm4
	punpcklwd	%xmm5, %xmm0
	movdqa	%xmm1, %xmm5
	paddd	%xmm3, %xmm5
	punpcklwd	%xmm5, %xmm1
	punpckhwd	%xmm5, %xmm4
	movdqa	%xmm1, %xmm5
	punpcklwd	%xmm4, %xmm1
	punpckhwd	%xmm4, %xmm5
	movdqa	%xmm0, %xmm4
	punpcklwd	%xmm5, %xmm1
	punpckhbw	%xmm1, %xmm4
	punpcklbw	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	punpcklbw	%xmm4, %xmm0
	punpckhbw	%xmm4, %xmm1
	movdqa	%xmm0, %xmm4
	punpcklbw	%xmm1, %xmm0
	punpckhbw	%xmm1, %xmm4
	punpcklbw	%xmm4, %xmm0
	movdqa	%xmm0, (%rcx)
	addq	$16, %rcx
	cmpl	%edi, %eax
	jb	.L11
	addl	%r9d, %edx
	subl	%r9d, %esi
	cmpl	%r9d, %r10d
	je	.L12
.L10:
	addl	%edx, %esi
	.p2align 4,,10
	.p2align 3
.L13:
	movl	%edx, %eax
	movb	%dl, (%r8,%rax)
	addl	$1, %edx
	cmpl	%esi, %edx
	jne	.L13
.L12:
	xorl	%ecx, %ecx
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L14:
	movl	%ecx, %eax
	xorl	%edx, %edx
	movzbl	(%r8,%rcx), %r10d
	divl	%ebp
	movzbl	%r10b, %eax
	movl	%edx, %edx
	movzbl	(%rbx,%rdx), %edx
	addl	%edx, %eax
	addl	%eax, %r9d
	andl	$255, %r9d
	movl	%r9d, %eax
	addq	%r8, %rax
	movzbl	(%rax), %edx
	movb	%dl, (%r8,%rcx)
	addq	$1, %rcx
	movb	%r10b, (%rax)
	cmpq	$256, %rcx
	jne	.L14
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r8, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	movl	$256, %esi
	xorl	%edx, %edx
	jmp	.L8
	.cfi_endproc
.LFE25:
	.size	init_buffer, .-init_buffer
	.p2align 4,,15
	.globl	rc4_byte
	.type	rc4_byte, @function
rc4_byte:
.LFB26:
	.cfi_startproc
	movzbl	(%rdi), %edx
	movq	8(%rdi), %rcx
	addl	$1, %edx
	movb	%dl, (%rdi)
	movzbl	%dl, %edx
	addq	%rcx, %rdx
	movzbl	(%rdx), %eax
	addb	1(%rdi), %al
	movb	%al, 1(%rdi)
	movzbl	%al, %eax
	movzbl	(%rdx), %esi
	movzbl	(%rcx,%rax), %eax
	movb	%al, (%rdx)
	movzbl	1(%rdi), %eax
	movq	8(%rdi), %rdx
	movb	%sil, (%rdx,%rax)
	movzbl	1(%rdi), %edx
	movq	8(%rdi), %rax
	movzbl	(%rdi), %ecx
	movzbl	(%rax,%rdx), %edx
	addb	(%rax,%rcx), %dl
	movzbl	%dl, %edx
	movzbl	(%rax,%rdx), %eax
	ret
	.cfi_endproc
.LFE26:
	.size	rc4_byte, .-rc4_byte
	.p2align 4,,15
	.globl	hexchar
	.type	hexchar, @function
hexchar:
.LFB27:
	.cfi_startproc
	cmpb	$10, %dil
	sbbl	%eax, %eax
	notl	%eax
	andl	$39, %eax
	leal	48(%rax,%rdi), %eax
	ret
	.cfi_endproc
.LFE27:
	.size	hexchar, .-hexchar
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"unable to allocate string :/"
	.text
	.p2align 4,,15
	.globl	hexa
	.type	hexa, @function
hexa:
.LFB28:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	leal	(%rsi,%rsi,2), %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	leal	1(%r12), %edi
	call	malloc
	testq	%rax, %rax
	je	.L36
	movl	%r12d, %edx
	testl	%ebp, %ebp
	leal	-1(%rbp), %r8d
	movb	$0, (%rax,%rdx)
	je	.L30
	leal	-1(%r12), %ecx
	.p2align 4,,10
	.p2align 3
.L35:
	movl	%r8d, %r9d
	movl	%ecx, %edx
	leal	-1(%rcx), %r10d
	addq	%rbx, %r9
	movb	$32, (%rax,%rdx)
	movzbl	(%r9), %esi
	andl	$15, %esi
	cmpb	$10, %sil
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rsi,%rdx), %edx
	movb	%dl, (%rax,%r10)
	movzbl	(%r9), %esi
	leal	-2(%rcx), %r9d
	shrb	$4, %sil
	cmpb	$10, %sil
	sbbl	%edx, %edx
	subl	$1, %r8d
	subl	$3, %ecx
	notl	%edx
	andl	$39, %edx
	cmpl	$-1, %r8d
	leal	48(%rsi,%rdx), %edx
	movb	%dl, (%rax,%r9)
	jne	.L35
.L30:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L36:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	movl	$.LC2, %eax
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE28:
	.size	hexa, .-hexa
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC3:
	.string	"Packet \033[33mIV:%02x%02x%02x\033[36m%2x\033[30m %3d \033[32mCRC:%02x%02x%02x%02x\033[0m\n"
	.text
	.p2align 4,,15
	.globl	print_packet
	.type	print_packet, @function
print_packet:
.LFB29:
	.cfi_startproc
	movq	32(%rsp), %rax
	movl	24(%rsp), %r9d
	movzbl	11(%rsp), %r8d
	movzbl	10(%rsp), %ecx
	movzbl	9(%rsp), %edx
	movzbl	8(%rsp), %esi
	movzbl	3(%rax), %edi
	movl	%edi, 32(%rsp)
	movzbl	2(%rax), %edi
	movl	%edi, 24(%rsp)
	movzbl	1(%rax), %edi
	movl	%edi, 16(%rsp)
	movzbl	(%rax), %eax
	movl	$.LC3, %edi
	movl	%eax, 8(%rsp)
	xorl	%eax, %eax
	jmp	printf
	.cfi_endproc
.LFE29:
	.size	print_packet, .-print_packet
	.p2align 4,,15
	.globl	ch1
	.type	ch1, @function
ch1:
.LFB30:
	.cfi_startproc
	leal	-32(%rdi), %edx
	movl	$32, %eax
	cmpb	$94, %dl
	ja	.L48
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L48:
	shrb	$4, %dil
	cmpb	$10, %dil
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rdi,%rdx), %eax
	ret
	.cfi_endproc
.LFE30:
	.size	ch1, .-ch1
	.p2align 4,,15
	.globl	ch2
	.type	ch2, @function
ch2:
.LFB31:
	.cfi_startproc
	movl	%edi, %eax
	leal	-32(%rax), %edx
	cmpb	$94, %dl
	jbe	.L50
	andl	$15, %eax
	cmpb	$10, %al
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rdx,%rax), %eax
.L50:
	rep
	ret
	.cfi_endproc
.LFE31:
	.size	ch2, .-ch2
	.p2align 4,,15
	.globl	color
	.type	color, @function
color:
.LFB32:
	.cfi_startproc
	movl	%edi, %edx
	shrb	$5, %dl
	cmpb	$2, %dl
	je	.L56
	cmpb	$3, %dl
	je	.L57
	xorl	%eax, %eax
	cmpb	$1, %dl
	je	.L64
.L54:
	.p2align 4,,3
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L64:
	movl	$-85, %edx
	movl	%edi, %eax
	mulb	%dl
	shrw	$8, %ax
	shrb	$5, %al
	leal	(%rax,%rax,2), %eax
	sall	$4, %eax
	subl	%eax, %edi
	cmpb	$10, %dil
	sbbl	%eax, %eax
	andl	$-4, %eax
	addl	$5, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L57:
	movzbl	%dil, %eax
	subl	$1, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	shrl	$27, %edx
	addl	%edx, %eax
	andl	$31, %eax
	subl	%edx, %eax
	cmpl	$26, %eax
	jle	.L58
	movl	$5, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L56:
	movzbl	%dil, %edx
	subl	$1, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$27, %eax
	addl	%eax, %edx
	andl	$31, %edx
	subl	%eax, %edx
	movl	$5, %eax
	cmpl	$26, %edx
	jg	.L54
.L58:
	cmpb	$97, %dil
	sbbl	%eax, %eax
	andl	$-2, %eax
	addl	$6, %eax
	ret
	.cfi_endproc
.LFE32:
	.size	color, .-color
	.section	.rodata.str1.1
.LC4:
	.string	""
.LC5:
	.string	"\033[3%dm%c%c\033[0m"
	.text
	.p2align 4,,15
	.globl	printbuffer
	.type	printbuffer, @function
printbuffer:
.LFB33:
	.cfi_startproc
	testl	%esi, %esi
	je	.L90
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$-85, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leal	-1(%rsi), %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	addq	$1, %r12
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebx, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L93:
	movl	%r8d, %ecx
	movl	%r8d, %edx
	andl	$15, %ecx
	cmpb	$10, %cl
	sbbl	%eax, %eax
	shrb	$4, %dl
	notl	%eax
	andl	$39, %eax
	cmpb	$10, %dl
	leal	48(%rcx,%rax), %ecx
	sbbl	%eax, %eax
	notl	%eax
	andl	$39, %eax
	movzbl	%cl, %ecx
	leal	48(%rdx,%rax), %edx
	movl	%r8d, %eax
	shrb	$5, %al
	cmpb	$2, %al
	movzbl	%dl, %edx
	je	.L72
.L94:
	cmpb	$3, %al
	je	.L73
	xorl	%esi, %esi
	cmpb	$1, %al
	jne	.L70
	movl	%r8d, %eax
	mulb	%r13b
	shrw	$8, %ax
	shrb	$5, %al
	leal	(%rax,%rax,2), %eax
	sall	$4, %eax
	subl	%eax, %r8d
	cmpb	$10, %r8b
	sbbl	%esi, %esi
	andl	$-4, %esi
	addl	$5, %esi
.L70:
	xorl	%eax, %eax
	movl	$.LC5, %edi
	call	printf
	movq	%rbx, %rax
	andl	$63, %eax
	cmpl	$63, %eax
	je	.L91
	addq	$1, %rbx
	cmpq	%r12, %rbx
	je	.L92
.L76:
	movzbl	0(%rbp,%rbx), %r8d
	leal	-32(%r8), %eax
	cmpb	$94, %al
	ja	.L93
	movl	%r8d, %eax
	movzbl	%r8b, %ecx
	movl	$32, %edx
	shrb	$5, %al
	cmpb	$2, %al
	jne	.L94
.L72:
	movzbl	%r8b, %eax
	subl	$1, %eax
	movl	%eax, %esi
	sarl	$31, %esi
	shrl	$27, %esi
	addl	%esi, %eax
	andl	$31, %eax
	subl	%esi, %eax
	movl	$5, %esi
	cmpl	$26, %eax
	jg	.L70
	cmpb	$96, %r8b
	movb	$4, %sil
	jbe	.L70
.L74:
	movl	$6, %esi
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L73:
	movzbl	%r8b, %eax
	subl	$1, %eax
	movl	%eax, %esi
	sarl	$31, %esi
	shrl	$27, %esi
	addl	%esi, %eax
	andl	$31, %eax
	subl	%esi, %eax
	movl	$5, %esi
	cmpl	$26, %eax
	jg	.L70
	cmpb	$96, %r8b
	movb	$4, %sil
	jbe	.L70
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L91:
	movl	$.LC4, %edi
	addq	$1, %rbx
	call	puts
	cmpq	%r12, %rbx
	jne	.L76
	.p2align 4,,10
	.p2align 3
.L92:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	$.LC4, %edi
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_restore 13
	.cfi_def_cfa_offset 8
	jmp	puts
.L90:
	movl	$.LC4, %edi
	jmp	puts
	.cfi_endproc
.LFE33:
	.size	printbuffer, .-printbuffer
	.p2align 4,,15
	.globl	check_key
	.type	check_key, @function
check_key:
.LFB34:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movzwl	96(%rsp), %eax
	movl	112(%rsp), %ebx
	movq	104(%rsp), %r12
	movq	120(%rsp), %rbp
	movl	%ebx, %r13d
	movw	%ax, 16(%rsp)
	movzbl	98(%rsp), %eax
	movb	%al, 18(%rsp)
	movl	(%rdi), %eax
	movl	%eax, 19(%rsp)
	movzbl	4(%rdi), %eax
	movb	%al, 23(%rsp)
.L97:
	movq	%r13, %rdi
	call	malloc
	testq	%rax, %rax
	je	.L128
	movl	$256, %edi
	movq	%rax, %r14
	call	malloc
	movq	%rax, %r10
	movq	%rax, %rdi
	movq	%rax, %rcx
	negq	%r10
	movl	%r10d, %r8d
	andl	$15, %r8d
	je	.L112
	xorl	%edx, %edx
	movl	$255, %r9d
	.p2align 4,,10
	.p2align 3
.L99:
	leal	1(%rdx), %eax
	movl	%r9d, %esi
	movb	%dl, (%rcx)
	subl	%edx, %esi
	addq	$1, %rcx
	cmpl	%eax, %r8d
	movl	%eax, %edx
	ja	.L99
.L98:
	movq	%r10, %rcx
	movl	$256, %r10d
	subl	%r8d, %r10d
	andl	$15, %ecx
	movl	%r10d, %r8d
	shrl	$4, %r8d
	movl	%r8d, %r9d
	sall	$4, %r9d
	testl	%r9d, %r9d
	je	.L100
	leal	1(%rax), %edx
	movl	%eax, (%rsp)
	addq	%rdi, %rcx
	movd	(%rsp), %xmm2
	movl	%edx, 4(%rsp)
	leal	2(%rax), %edx
	movd	4(%rsp), %xmm5
	movl	%edx, 8(%rsp)
	leal	3(%rax), %edx
	movd	8(%rsp), %xmm0
	punpckldq	%xmm5, %xmm2
	movl	%edx, 12(%rsp)
	xorl	%edx, %edx
	movd	12(%rsp), %xmm1
	movdqa	.LC0(%rip), %xmm6
	punpckldq	%xmm1, %xmm0
	movdqa	.LC1(%rip), %xmm3
	punpcklqdq	%xmm0, %xmm2
	.p2align 4,,10
	.p2align 3
.L101:
	movdqa	%xmm2, %xmm0
	addl	$1, %edx
	movdqa	%xmm2, %xmm5
	paddd	%xmm3, %xmm0
	movdqa	%xmm2, %xmm4
	movdqa	%xmm0, %xmm1
	punpcklwd	%xmm0, %xmm5
	paddd	%xmm6, %xmm2
	punpckhwd	%xmm0, %xmm4
	paddd	%xmm3, %xmm1
	movdqa	%xmm5, %xmm0
	punpckhwd	%xmm4, %xmm5
	punpcklwd	%xmm4, %xmm0
	movdqa	%xmm1, %xmm4
	punpcklwd	%xmm5, %xmm0
	movdqa	%xmm1, %xmm5
	paddd	%xmm3, %xmm5
	punpcklwd	%xmm5, %xmm1
	punpckhwd	%xmm5, %xmm4
	movdqa	%xmm1, %xmm5
	punpcklwd	%xmm4, %xmm1
	punpckhwd	%xmm4, %xmm5
	movdqa	%xmm0, %xmm4
	punpcklwd	%xmm5, %xmm1
	punpckhbw	%xmm1, %xmm4
	punpcklbw	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	punpcklbw	%xmm4, %xmm0
	punpckhbw	%xmm4, %xmm1
	movdqa	%xmm0, %xmm4
	punpcklbw	%xmm1, %xmm0
	punpckhbw	%xmm1, %xmm4
	punpcklbw	%xmm4, %xmm0
	movdqa	%xmm0, (%rcx)
	addq	$16, %rcx
	cmpl	%r8d, %edx
	jb	.L101
	addl	%r9d, %eax
	subl	%r9d, %esi
	cmpl	%r9d, %r10d
	je	.L102
.L100:
	addl	%eax, %esi
	.p2align 4,,10
	.p2align 3
.L103:
	movl	%eax, %edx
	movb	%al, (%rdi,%rdx)
	addl	$1, %eax
	cmpl	%esi, %eax
	jne	.L103
.L102:
	xorl	%eax, %eax
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L104:
	movq	%rax, %rcx
	movzbl	(%rdi,%rax), %esi
	andl	$7, %ecx
	movzbl	16(%rsp,%rcx), %r8d
	movzbl	%sil, %ecx
	addl	%r8d, %ecx
	addl	%ecx, %edx
	andl	$255, %edx
	movl	%edx, %ecx
	addq	%rdi, %rcx
	movzbl	(%rcx), %r8d
	movb	%r8b, (%rdi,%rax)
	addq	$1, %rax
	movb	%sil, (%rcx)
	cmpq	$256, %rax
	jne	.L104
	movl	%ebx, %ecx
	subl	$4, %ecx
	je	.L113
	xorw	%ax, %ax
	xorl	%edx, %edx
	movl	$-1, %r15d
	.p2align 4,,10
	.p2align 3
.L106:
	leal	1(%rax), %r8d
	movzbl	(%r12,%rax), %esi
	movzbl	%r8b, %r8d
	addq	%rdi, %r8
	movzbl	(%r8), %r9d
	addl	%r9d, %edx
	movzbl	%dl, %r10d
	addq	%rdi, %r10
	movzbl	(%r10), %r11d
	movb	%r11b, (%r8)
	movb	%r9b, (%r10)
	addb	(%r8), %r9b
	movzbl	%r9b, %r9d
	xorb	(%rdi,%r9), %sil
	movb	%sil, (%r12,%rax)
	xorl	%r15d, %esi
	addq	$1, %rax
	movzbl	%sil, %esi
	shrl	$8, %r15d
	xorl	crc32_tab(,%rsi,4), %r15d
	cmpl	%eax, %ecx
	ja	.L106
	notl	%r15d
	leal	-4(%rbx), %r10d
	movl	%r15d, %eax
.L105:
	cmpl	%ecx, %ebx
	jbe	.L111
	movb	%al, 4(%rsp)
	.p2align 4,,10
	.p2align 3
.L118:
	addl	$1, %r10d
	movl	%ecx, %r11d
	addl	$1, %ecx
	movzbl	%r10b, %r8d
	addq	%r12, %r11
	addq	%rdi, %r8
	movzbl	(%r11), %esi
	movzbl	(%r8), %r9d
	addl	%r9d, %edx
	movzbl	%dl, %r13d
	addq	%rdi, %r13
	movzbl	0(%r13), %eax
	movb	%al, (%r8)
	movb	%r9b, 0(%r13)
	addb	(%r8), %r9b
	movzbl	%r9b, %r9d
	xorb	(%rdi,%r9), %sil
	cmpl	%ebx, %ecx
	movb	%sil, (%r11)
	jne	.L118
	movzbl	4(%rsp), %eax
.L111:
	xorl	%ebx, %ebx
	cmpb	%al, 0(%rbp)
	je	.L129
.L109:
	call	free
	movq	%r14, %rdi
	call	free
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L128:
	.cfi_restore_state
	xorl	%edi, %edi
	call	sleep
	jmp	.L97
.L129:
	movl	%r15d, %eax
	xorl	%ebx, %ebx
	shrl	$8, %eax
	cmpb	%al, 1(%rbp)
	jne	.L109
	movl	%r15d, %eax
	shrl	$16, %eax
	cmpb	%al, 2(%rbp)
	jne	.L109
	xorl	%ebx, %ebx
	shrl	$24, %r15d
	cmpb	%r15b, 3(%rbp)
	sete	%bl
	jmp	.L109
.L113:
	xorl	%eax, %eax
	xorl	%r15d, %r15d
	xorl	%edx, %edx
	xorl	%r10d, %r10d
	jmp	.L105
.L112:
	movl	$256, %esi
	xorl	%eax, %eax
	jmp	.L98
	.cfi_endproc
.LFE34:
	.size	check_key, .-check_key
	.p2align 4,,15
	.globl	update_key
	.type	update_key, @function
update_key:
.LFB35:
	.cfi_startproc
	movq	%rdi, %rcx
	xorl	%eax, %eax
	jmp	.L134
	.p2align 4,,10
	.p2align 3
.L139:
	movl	%r8d, %eax
.L134:
	movzbl	(%rcx), %edx
	leal	1(%rax), %r8d
	cmpb	$-1, %dl
	jne	.L135
	addq	$1, %rcx
	cmpl	%esi, %r8d
	jb	.L139
.L135:
	cmpl	%esi, %r8d
	je	.L147
	cmpl	$-1, %eax
	movl	%eax, %ecx
	jne	.L137
	.p2align 4,,3
	jmp	.L136
	.p2align 4,,10
	.p2align 3
.L148:
	movl	%eax, %ecx
	movzbl	(%rdi,%rcx), %edx
.L137:
	subl	$1, %eax
	addl	$1, %edx
	cmpl	$-1, %eax
	movb	%dl, (%rdi,%rcx)
	jne	.L148
.L136:
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L147:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE35:
	.size	update_key, .-update_key
	.section	.rodata
	.align 8
.LC6:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204\3604\253qY"
	.string	"h\207 \030X\267(\307\320j\303}\251K\006\253\327j\t\243J\r\226wI\024\241\\\375,\264\\\361"
	.string	"\370\245o\353I\235\b\325\0226\351o\211\f\355\360\2477i\227\312\253\033\212\037\3573\377H\232\"\033\3726\f,o)>\n\256U,o\307;\302\024Q\205Xe&\3213}R`l?\376!\222Ck\277{*\211KZ\374\\\275\366\352\036\2618\322\235\0174f\0052\2403\230\374\276\204P\n.\312\332\271h\261O;\352x\267\263&O\005\021\350Gy\375lH\221\221:\b\240\224>IFPNro5\f\274\315\020E\346\032-\342\026Q\336\340\311D\004\262A\344\026\320;w\t\205\355Y\177\267v@\226RF\251\270\270!6\225\233\322\035uz\304\302b4a\237\352\247\212\233\023\333\177\251\351;l|\213\"\036\263\221\331W\007\371oJ\016\350\213\225\016\204;\226\244.s\302\3479\260\260\262MQ'\023\351=3\372\031\253x\371\345\243\205\030J\261\237MDO\275\016y"
	.string	"\250\306l\330$\307Z\367%+\377h+\301\356\342\276\030:\321$\017\353F\036\306x\260\261\202\374h%c\276\352\277\246\362\f\303O\254s\333\200L&8\037\262\252\231l\366\322!\021y\335\335\274\2533@\241\3148\231\251\025\026\322\313\026\225\226\270\311"
	.string	"\032>7\222\235\306\355m\272>*\275\377\027\363a\204MV\016\362@e\021\257\243R]\023\3237(\234F\257Wl\34085\023'\326\374\037L\303\216\376\006L\022\245)r\225"
	.string	"\224\266I\373<\346\315>\224u\212uj\021\367\2669\004}\277c\356\211\377\334\030\273\374NA\215\263"
	.align 8
.LC7:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204\360<\260\241\333"
	.ascii	"\305\253\352\f\365\354\242%\252\257*\224\251k\3716\346f\202\257"
	.ascii	"mCe\271\244cT\274v\326\330\2555I3\344\036\246\2120\241y\nW\213"
	.ascii	"\353\023\251\037\3276W\311y\323\332\306\023\327\036M\220\005"
	.ascii	"\\\331\267U\301LII#\331\306\367\225\026\361~\354r\364\2436\377"
	.ascii	"\354\232\354\235$d\360\037\214\311\376\333\232\350X2\306p\367"
	.ascii	"t\3361\004/\242]\203?\023"
	.string	"5\"\247\365\314A\363S-Y\255@+\345a\025\315b\212\2627\257\215/\024^\334*\364&&\230_i\212_s\363\230_p\254\232\315\2205L9**\353\020\261\f\023c\211A\275mF\223\354Ew\3063B\271\311\334 \\D\235\257\t\237Z\262\320\264\n\316\372c\b\227\227\332x(\273f\201\302\344\230=\261\245\344\303\254x\334\\`Z\230:\230JQ\326\201\306\025\272ew\236\333\320\252\202c\036\036d\211I\006\367( \205\316\031y\344\225\"\344\350j\355\356#\207\213\342<\013A\354\033#EP\273\200 \232\347y)uY\205\217\227\025\300\b\372\337\240\323\024\246\321P\033X\2443f\321TM+\027M\013\333\326\227~\310\244\201\225dk\321=\005k\273T\325I\276\274bx\322\243Z\345\202\340\0303[\313\266m\335\372\273\272\213x\211O\240\201\t\32422wE{\2264\357\r\350\274o\376\315\235"
	.string	"k=\322YN\tf\224"
	.string	"\243\030\254\034\365\233\340\337\316\233\315\0058wu\366\373t\367}\216M\1777\266\031\005\372\r\261\035\322\203\304\265e\311\250\221\016\314?\311\220\311y\363\336\204en\210\301gs{\317\217"
	.align 8
.LC8:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204\020\020\275(\320"
	.ascii	"\356\367\326\235\277\033\350\244\337\313\370\244\353}\273\374"
	.ascii	"l\357\353:\203\232\235\0303\205\372\352\240\236\3409\363\371"
	.ascii	"V\201zed&\022W\265\203e'\212\366\326\211$\\{\037z\t\313\303-"
	.string	"\375\327\234\264\b\247\227c1\207\364\241T\257;g\207U\215\272\356m\352\247\330\013\271\335\032\r2#\235\312E\030\324\006m\276u\n\367`\347\307T\rqI\315;+\005?\b\026\317\227\001\t\316{H\022o9^\347p\032\263\355J`!\253\277\210ZNGR`\274\277A\374\002F\354\226\321\274p\257\360\362\315\342:j\023\272V\352\233L\2168%z-\360b#\244|\265\025\220]\230\273\f\025\361=\311!\027td7S\024\266\342\216f!\340\016\0363H\316\b/\213\245SU=\231\002\207\274\230\327q\264\246|{\276\336\350\2100*\360\221\245\"A\347\334\035\305\217\021\337\341a\022VV\210m\261\004\007\3300\317\213m[\336B\327\316[\310\325T(d~$\210x\265\204D\363\254r\314\230j\2665\234\277z\333\244\315 \3463\303\362\272\246C\345\001\200P\255\276\371b\274\027\310!x\356V~\377\360"
	.string	"\002\231AQ}c\204\340fKXa\264\263\004h$\241\336<\256\200\372n\321"
	.string	"\371'\203\276\315\230\346\270\tw\274\245>)\002H\034#\352\224\240nK\\\321k^E\\-G\266J6\273\t\f\350\255\317V\260\0063\274\037(^)\366c\271d\372bM\235\223\210\bY<\0324\026\212&\375\202\270\"\242\f~k?g\327\343\034\274\2525W\t\306@\327TT\030\246\200?z\030\366( \032\253\264\256\206\222\rux"
	.align 8
.LC9:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204@]\300\234\274"
	.string	"\307T\002/nE\\\225\237'\3739\022O\265\034\033\330\030\n\246O\332\235\035\367t\003y\364\337$'mQ\351N\311\253\375^\263gJB\340\376\232<-6\330\306\235\351\023\227o\237\236\373:\017\203U%\302\253'\244\377\233'\017\347\r\034\253\235\022\242l\265W8\361/tJ\357\027\024\351Df\037\306\275q\322Z\225\312\311\233'`\256<5\216Iv\035W\347txp\373?\356Mv\032\020\361\307&\t\222\205\371\340=\n\n\224Rn\235E\255\201\260\245gQN\2056\347\214>\rv7|\2221\347E#\231t6\212j\263\310\004\\1\376\022\354\273\323\022\231\210t\312/Y\246\005\202\301+\004\321\247\326\332\346\222\340(\306\362\213~~W\031\3062\210,\337\333\2107KZR7\030\021$\361\312EL\300\267\222\363\220\314"
	.string	"\003c\250\266\231"
	.string	"B\256i\021\260\210\344r\230j#\2366I\275\336\245\007\333\327\032\266\177\226\322\274v$\235\246hB\221\341B\022\n\032\264([\264\250\217\230jA%N\372@\"\315\2313t\364S\027qL2\006\254#\201\202\024\327\355 ^\323\036\363\020\303\211\225)\330\315X\200<\b`\335\365\206\325\324\351"
	.string	"\347:\203\3045\372V\321\225\021tA\225\247X\324\375\253\261\371Sc\214\264\212bS\332]\321\365\316\224\304\035D\037\266\232\374\t\265Fp\002\303\013\207\204mn\377\006\247\320\255\017\262!\322\257\245\233oA\231\357\r\327\206\021\310\375\033\322\224\332j\254RmXLh\332_\225\024\\\\n-\313\204\240j~caD3l\025n)\210"
	.align 8
.LC10:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204P]\300\235\226"
	.string	"P;9\337j\027\365\241U\344\002\301^\375\220?QI\346@\317\341\317\033\334x\225\026+\376+>W.\201/\252\"Vo\344v\301\r\nBu\202"
	.string	"A\255R\352<\306b\035\"\356\324\267SW\354\240K\312\221\372s\311\343\b\305\216\033\311\3407+\357\260\327U\233\255]\237\337>\f\036\374d\246\356\363\363h\247\037\327\231\355\237\273\024[\212\244M-\033..\320\275\374]\"\347\370-5\256\366s\233\332\335h\260:\200\251\024aF\372&2\t\212\350\030\200\361\323\233l}oi\372\b\034\320`\262w\312\320K\035\231@*Q\035{\236/\364@\375\177\024\350[\232\3148\273\035\335c\002\321\300\362+!\213\034 .\214\200\343\n\344\303\207Nq\210\240\2668p\257X\004\334z#`\013\250\"\204\365\270\217\276\023\264u\354)\254\206\332mz\300\361zq\fb\003\223\004\257S\007\315\353\211\364T="
	.string	"\266v\207\0367\376\305\310\333\200\356\204\2578\005r\242\337\30580L\200\177\372S\255\r\025\362\216\343\024M\204|\025\025\303\223td\337f\230\\hV\221\215\374\230\334=Pc\336as\371\016\222\027\326\251c<bn\022\356\375\222\360\307h+\026\207.\322\342\035\026\301\001\255ISM\325V\360Y\364\366V\241T\254L\220\204?\325n\277\202\331\355\020\224\306\366Y\026\234I\305\342x\374\252S\323\223L\211\236\316\240\027\320\322\331\221\205C\343=!\020\373\372\325p(C\3246\331d\344\366\214\3230T\253\":\357\367\315\245\0024A\035\3555\336\276\262\025\256\331V\037\n\013\376\326\374\020\221\267\226\262\367+\253\245\326\266\022"
	.align 8
.LC11:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204"
	.string	"\320\355H\260"
	.string	"\330\301D\360\f\320\326HZ\221E\245\371xb\034g\t\304a\2733\310\354 \016\305\27694$\024V\r\230\207e\367\037\023(\037\243}\035o>\004\352\276\273M\f\277\033a\177\236\027<\216\301\f,\2203\361\316\237\377Z\331\235>R\305\256_\313\021\200\3627\246\r\344<\336>\311\300D\307\037\by\212\2113"
	.string	"tN\374\254N\326k\213\204\311\212\273\024\337"
	.string	"\302\315\252\354\270dF\275\347\213d\245\250\231\365\334cBT\b\341Q\344o^KG,\300HI\222\037\272\235\246\316\324\321}\006-\201\274\222\273a@\355\260\370\21610\020w:\214B5\243\021J%{w\304BL?#\334\\R7\211\274q\020\224\007V\320\364\237oo\357\020\321p\326\353\262\230\376\037\035\324?R|H\303\016\024\227\265@\024\256^\345\207~\307\371I\253$\304\035-\254b;\252\242j\346$RV\245=,\243}\203}1\217R\274\020\347V\330\203\023"
	.string	"\321NdV\302P\036\"\371\226&9\351)I\256W\202{\346\265\t\267a_\223\226:\236p?\017\tTG' \347\2033f\027\t\307cf\234BF=\3255\266\337\347;F\340\254@J\211R-6\322\205"
	.string	"a\254\323x\271\\\033\306\326L\251\305\266(Z\224\030l\036\037\266X\224\357\026]\360\177\b\037|\0136\035\337\332}\206\007&\347\3025T8=,\241y\371z\266*\345\025\255!\341\264\335\375\311\315\001n"
	.string	"\223\355[\277\275\367K\354\030\021\325bC\031\275TV\353\216Cj\335-K\266\344(c\232\345\320\234e\253spV\366"
	.align 8
.LC12:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204\020\320\355Iz"
	.string	"\262\315\233\243a\007\27758\263M\264\270\210\226=\314\033La\271\307>\235\323\253\321\201\322\273/\230:!R\323\233*\030w\t}\233UXf&\362\"\351\235\221\370K\231\207\301h~\213z\230\315I\231\246\227M=\236Mo\335\016\022\270\330\363A3\371\233\236\013\026\025:\341J\375`\221\273h\366<\374:\360V\361@\216\275\273\200-kD\263\310r\271\267\335\223<}5\240\177\300\276+\315\364T\314\250\350\234\200\255pWs>kU\002zr<h\203\004\323\266b\316W\252.G#\343Z,H\232\243@Z_/\213\357+\001{\330\0137\303U\034"
	.ascii	"\265K\263\314\333$\203\264~\005Y\273n\273\017=\277"
	.string	"\231\316\367\371\200K\335n\215j\334#s4\344[\n+\002\240\021|F\016`G0/>i\212r/\274:\035\375\025\367\324\375\205\231\025w3\326\260uj\322\337\3016\006\005\225\025\321A\b\224\f\330E\330V\f\203#nt?\226l\t<\326\370\0050x\f\017\t@\035\300\\\246:gU\354\253\017\025f\230\270\354\222\005\307\364\033\\v\222\270\023o\210/\261\322\301\265]\250i\002\201\276\260\377\003\271\203\372 9\004\027\013D+\371S\032\001|.\221\265]z\342\275C-?rR\332\323\366\307<\227\2415\241{\346\ri\311'\310\247\274 \207\312s\370\221s\322\032b_\220\013\016\267\320\225\271\032\270v\371\263Mt\221\365\272E=\267\004\273\370\024\377u\036\364\266&\313\210\272\374\201\232\370\234\251})\337\330=[\2369>)\022y\346\260\303_\371\br+[\310=\247\250qm\036\350|\351x\335\027"
	.align 8
.LC13:
	.string	"\bb"
	.string	""
	.string	"\001"
	.string	"^\177\377\372"
	.string	"$\324N\213\204"
	.string	"$\324N\213\204\360\351\365\260 "
	.string	"\216"
	.ascii	"\227\204\025M\216\003\324{(\024\256N\025\244da\037\351\357\205"
	.ascii	"_\350,\351\221^\254\261\216\240\323\037%3i\020\025L6]\004\246"
	.ascii	"=\016\355\202\327\265\n\274\254\277\247\210\036\363\305q\214"
	.ascii	"\200:f\001f/\312\357St#\247\334t`\357\346#\3066\222E\017\201"
	.ascii	"\037\373ie\\\367\256\303-\300\255<\3526Z\351(\353Sjl\005\234"
	.ascii	"\272@\267\225\240\273\205\013\310A9q\336x\3067q\245\022\001h"
	.ascii	"\345an\304\373z\232DP\264\316GR[:\357(!\377Qw\022>Xx\250\224"
	.ascii	"P\003)\266K\bL\237\004=n\313\345\fj,j\302x\217\300\234(\f\231"
	.ascii	"\307"
	.string	"\343Zf6\356\371\264\007\371,\030\207\264}uc,\322\242)\323o\315\"\\\217\232\303\203v\305\003T\027\255\3108\376\n\337\256\027\220\262^\342y\016\331\327\206l\230\317V\001\204xi<Kn!\376[\340\tM/\023R+\257\241^\033\352J8`Ma\023\017o?\033\252\310\217\364:<\334\244\310<B~\327\222<~\276\312\373\373\355\004\013H\273\031/\261ezW\367\377\213\266\026zv\277HN\2579M*4\032\247\270\274'\365\017\375l\273\350\\N3\266\351\321\321\201C\004D\334A\366D\332\344 \340!\r\206\301O\352<W\004L\315\003\211\345\374\375\354\275\235\206\241\322\272Ij\262\241XO\022KU\f\356|\024\322\t/\314P\027\271\216\213\364\312\036\202\204J\207\005\276\220\027\205\373\274\006V\267>T\376#M\340W\003M\343u*\333z\247\205\215\211\r)o\247\331+\205\017m\273\266B\372"
	.text
	.p2align 4,,15
	.globl	load_packets
	.type	load_packets, @function
load_packets:
.LFB36:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$128, %edi
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	call	malloc
	movl	$478, %edi
	movq	%rax, %rbx
	movl	$478, (%rax)
	call	malloc
	movl	$.LC6, %esi
	movq	%rax, 8(%rbx)
	movq	%rax, %rdi
	movl	$59, %ecx
	rep movsq
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movzwl	.LC6+476(%rip), %eax
	movw	%ax, 4(%rdi)
	movl	$466, %edi
	movl	$466, 16(%rbx)
	call	malloc
	movl	$.LC7, %esi
	movq	%rax, 24(%rbx)
	movq	%rax, %rdi
	movl	$58, %ecx
	rep movsq
	movzwl	(%rsi), %eax
	movw	%ax, (%rdi)
	movl	$478, %edi
	movl	$478, 32(%rbx)
	call	malloc
	movl	$.LC8, %esi
	movq	%rax, 40(%rbx)
	movq	%rax, %rdi
	movl	$59, %ecx
	rep movsq
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movzwl	.LC8+476(%rip), %eax
	movw	%ax, 4(%rdi)
	movl	$466, %edi
	movl	$466, 48(%rbx)
	call	malloc
	movl	$.LC9, %esi
	movq	%rax, 56(%rbx)
	movq	%rax, %rdi
	movl	$58, %ecx
	rep movsq
	movzwl	(%rsi), %eax
	movw	%ax, (%rdi)
	movl	$478, %edi
	movl	$478, 64(%rbx)
	call	malloc
	movl	$.LC10, %esi
	movq	%rax, 72(%rbx)
	movq	%rax, %rdi
	movl	$59, %ecx
	rep movsq
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movzwl	.LC10+476(%rip), %eax
	movw	%ax, 4(%rdi)
	movl	$466, %edi
	movl	$466, 80(%rbx)
	call	malloc
	movl	$.LC11, %esi
	movq	%rax, 88(%rbx)
	movq	%rax, %rdi
	movl	$58, %ecx
	rep movsq
	movzwl	(%rsi), %eax
	movw	%ax, (%rdi)
	movl	$478, %edi
	movl	$478, 96(%rbx)
	call	malloc
	movl	$.LC12, %esi
	movq	%rax, 104(%rbx)
	movq	%rax, %rdi
	movl	$59, %ecx
	rep movsq
	movl	(%rsi), %eax
	movl	%eax, (%rdi)
	movzwl	.LC12+476(%rip), %eax
	movw	%ax, 4(%rdi)
	movl	$466, %edi
	movl	$466, 112(%rbx)
	call	malloc
	movl	$.LC13, %esi
	movq	%rax, 120(%rbx)
	movq	%rax, %rdi
	movl	$58, %ecx
	movq	%rbx, %rdx
	rep movsq
	movzwl	(%rsi), %eax
	movw	%ax, (%rdi)
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	movl	$8, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	load_packets, .-load_packets
	.section	.rodata.str1.1
.LC14:
	.string	"Initial key : %s\n"
.LC15:
	.string	"%s (yolo null key)\n"
.LC16:
	.string	"%ds %s\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB37:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$5, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$216, %rsp
	.cfi_def_cfa_offset 272
	call	malloc
	movl	$336617568, (%rax)
	movb	$83, 4(%rax)
	movq	%rax, %rbx
	call	load_packets
	movl	%eax, 112(%rsp)
	movq	112(%rsp), %r13
	movq	%rdx, %rbp
	movq	%rdx, 120(%rsp)
	movq	%rdx, 136(%rsp)
	movl	%r13d, %edi
	movq	%r13, 128(%rsp)
	movl	%r13d, 76(%rsp)
	salq	$5, %rdi
	call	malloc
	movl	76(%rsp), %edx
	movq	%rax, %r12
	testl	%edx, %edx
	je	.L156
	movq	%rbp, %r13
	movq	%rax, %rbp
	movl	76(%rsp), %eax
	subl	$1, %eax
	salq	$4, %rax
	leaq	16(%r13,%rax), %rax
	movq	%rax, 64(%rsp)
	.p2align 4,,10
	.p2align 3
.L155:
	movq	8(%r13), %rsi
	movl	0(%r13), %r10d
	addq	$16, %r13
	movzwl	24(%rsi), %eax
	leal	-28(%r10), %r15d
	movl	%r15d, %edx
	movq	%rdx, %rdi
	movw	%ax, 144(%rsp)
	movzbl	26(%rsi), %eax
	movb	%al, 146(%rsp)
	movzbl	27(%rsi), %r8d
	movl	%r10d, 40(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rsi, 56(%rsp)
	shrb	$6, %r8b
	movb	%r8b, 32(%rsp)
	call	malloc
	movq	56(%rsp), %rsi
	movq	48(%rsp), %rdx
	movq	%rax, %rdi
	movq	%rax, %r14
	addq	$28, %rsi
	call	memcpy
	movzbl	32(%rsp), %r8d
	movl	%r15d, 160(%rsp)
	movl	40(%rsp), %r10d
	movq	%r14, 8(%rbp)
	movq	%r14, 152(%rsp)
	movq	%r14, 184(%rsp)
	movb	%r8b, 147(%rsp)
	movq	144(%rsp), %rdx
	leal	-32(%r10), %eax
	addq	%r14, %rax
	movq	%rdx, 176(%rsp)
	movq	160(%rsp), %rdx
	movb	%r8b, 179(%rsp)
	movq	%rax, 24(%rbp)
	movq	%rax, 168(%rsp)
	movq	%rax, 200(%rsp)
	movq	%rdx, 192(%rsp)
	movq	176(%rsp), %rdx
	movl	%r15d, 192(%rsp)
	movq	%rdx, 0(%rbp)
	movq	192(%rsp), %rdx
	movq	%rdx, 16(%rbp)
	addq	$32, %rbp
	cmpq	64(%rsp), %r13
	jne	.L155
.L156:
	movl	$5, %esi
	movq	%rbx, %rdi
	call	hexa
	movl	$.LC14, %edi
	movq	%rax, %rsi
	xorl	%eax, %eax
	call	printf
	leaq	80(%rsp), %rdi
	movq	%r12, %rsi
	call	copy_packet
	movq	80(%rsp), %rsi
	movq	88(%rsp), %rcx
	movq	%rbx, %rdi
	movq	96(%rsp), %rdx
	movq	104(%rsp), %rax
	movq	%rsi, 144(%rsp)
	movq	%rcx, 152(%rsp)
	movq	%rdx, 160(%rsp)
	movq	%rax, 168(%rsp)
	movq	%rsi, (%rsp)
	movq	%rcx, 8(%rsp)
	movq	%rdx, 16(%rsp)
	movq	%rax, 24(%rsp)
	call	check_key
	testl	%eax, %eax
	jne	.L203
.L154:
	leaq	144(%rsp), %rsi
	movq	%r12, %rdi
	call	recopy_packet
	xorl	%edi, %edi
	call	time
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L157:
	cmpb	$-1, (%rbx)
	jne	.L189
	cmpb	$-1, 1(%rbx)
	jne	.L190
	cmpb	$-1, 2(%rbx)
	jne	.L191
	cmpb	$-1, 3(%rbx)
	jne	.L192
	movl	76(%rsp), %eax
	testl	%eax, %eax
	je	.L176
	movl	76(%rsp), %r13d
	movq	%r12, %rbp
	subl	$1, %r13d
	salq	$5, %r13
	leaq	32(%r12,%r13), %r13
	.p2align 4,,10
	.p2align 3
.L175:
	movq	8(%rbp), %rdi
	addq	$32, %rbp
	call	free
	cmpq	%r13, %rbp
	jne	.L175
.L176:
	movq	%r12, %rdi
	call	free
	movq	%rbx, %rdi
	call	free
	addq	$216, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L189:
	.cfi_restore_state
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L195:
	movl	%edx, %ecx
	subl	$1, %edx
	addb	$1, (%rbx,%rcx)
	cmpl	$-1, %edx
	jne	.L195
	cmpb	$0, 1(%rbx)
	jne	.L158
	cmpb	$0, (%rbx)
	je	.L204
.L158:
	movq	144(%rsp), %rax
	movq	%rbx, %rdi
	movq	%rax, (%rsp)
	movq	152(%rsp), %rax
	movq	%rax, 8(%rsp)
	movq	160(%rsp), %rax
	movq	%rax, 16(%rsp)
	movq	168(%rsp), %rax
	movq	%rax, 24(%rsp)
	call	check_key
	testl	%eax, %eax
	jne	.L205
.L159:
	movl	160(%rsp), %edx
	movq	8(%r12), %rsi
	movq	152(%rsp), %rdi
	call	memcpy
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L205:
	movl	$16, %edi
	call	malloc
	testq	%rax, %rax
	je	.L178
	movzbl	4(%rbx), %edx
	movl	$15, %esi
	movb	$0, 15(%rax)
	movb	$32, 14(%rax)
	movb	$32, 11(%rax)
	movb	$32, 8(%rax)
	movb	$32, 5(%rax)
	movb	$32, 2(%rax)
	andl	%edx, %esi
	cmpb	$10, %sil
	sbbl	%ecx, %ecx
	notl	%ecx
	andl	$39, %ecx
	leal	48(%rsi,%rcx), %ecx
	movl	$15, %esi
	movb	%cl, 13(%rax)
	movl	%edx, %ecx
	shrb	$4, %cl
	cmpb	$10, %cl
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rcx,%rdx), %edx
	movb	%dl, 12(%rax)
	movzbl	3(%rbx), %edx
	andl	%edx, %esi
	cmpb	$10, %sil
	sbbl	%ecx, %ecx
	notl	%ecx
	andl	$39, %ecx
	leal	48(%rsi,%rcx), %ecx
	movl	$15, %esi
	movb	%cl, 10(%rax)
	movl	%edx, %ecx
	shrb	$4, %cl
	cmpb	$10, %cl
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rcx,%rdx), %edx
	movb	%dl, 9(%rax)
	movzbl	2(%rbx), %edx
	andl	%edx, %esi
	cmpb	$10, %sil
	sbbl	%ecx, %ecx
	notl	%ecx
	andl	$39, %ecx
	leal	48(%rsi,%rcx), %ecx
	movl	$15, %esi
	movb	%cl, 7(%rax)
	movl	%edx, %ecx
	shrb	$4, %cl
	cmpb	$10, %cl
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rcx,%rdx), %edx
	movb	%dl, 6(%rax)
	movzbl	1(%rbx), %edx
	andl	%edx, %esi
	cmpb	$10, %sil
	sbbl	%ecx, %ecx
	notl	%ecx
	andl	$39, %ecx
	leal	48(%rsi,%rcx), %ecx
	movl	$15, %esi
	movb	%cl, 4(%rax)
	movl	%edx, %ecx
	shrb	$4, %cl
	cmpb	$10, %cl
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rcx,%rdx), %edx
	movb	%dl, 3(%rax)
	movzbl	(%rbx), %edx
	andl	%edx, %esi
	cmpb	$10, %sil
	sbbl	%ecx, %ecx
	notl	%ecx
	andl	$39, %ecx
	leal	48(%rsi,%rcx), %ecx
	movb	%cl, 1(%rax)
	movl	%edx, %ecx
	shrb	$4, %cl
	cmpb	$10, %cl
	sbbl	%edx, %edx
	notl	%edx
	andl	$39, %edx
	leal	48(%rcx,%rdx), %edx
	movb	%dl, (%rax)
.L160:
	movq	%rax, %rdi
	call	puts
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L204:
	xorl	%edi, %edi
	call	time
	movq	%rax, %r14
	movq	%rbx, %rdi
	movl	$5, %esi
	subq	%rbp, %r14
	call	hexa
	movl	%r14d, %esi
	movq	%rax, %rdx
	movl	$.LC16, %edi
	xorl	%eax, %eax
	call	printf
	jmp	.L158
.L190:
	movl	$1, %edx
	jmp	.L195
.L191:
	movl	$2, %edx
	jmp	.L195
.L192:
	movl	$3, %edx
	jmp	.L195
.L178:
	movl	$.LC2, %eax
	jmp	.L160
.L203:
	movq	%rbx, %rdi
	movl	$5, %esi
	call	hexa
	movl	$.LC15, %edi
	movq	%rax, %rsi
	xorl	%eax, %eax
	call	printf
	jmp	.L154
	.cfi_endproc
.LFE37:
	.size	main, .-main
	.section	.rodata
	.align 32
	.type	crc32_tab, @object
	.size	crc32_tab, 1024
crc32_tab:
	.long	0
	.long	1996959894
	.long	-301047508
	.long	-1727442502
	.long	124634137
	.long	1886057615
	.long	-379345611
	.long	-1637575261
	.long	249268274
	.long	2044508324
	.long	-522852066
	.long	-1747789432
	.long	162941995
	.long	2125561021
	.long	-407360249
	.long	-1866523247
	.long	498536548
	.long	1789927666
	.long	-205950648
	.long	-2067906082
	.long	450548861
	.long	1843258603
	.long	-187386543
	.long	-2083289657
	.long	325883990
	.long	1684777152
	.long	-43845254
	.long	-1973040660
	.long	335633487
	.long	1661365465
	.long	-99664541
	.long	-1928851979
	.long	997073096
	.long	1281953886
	.long	-715111964
	.long	-1570279054
	.long	1006888145
	.long	1258607687
	.long	-770865667
	.long	-1526024853
	.long	901097722
	.long	1119000684
	.long	-608450090
	.long	-1396901568
	.long	853044451
	.long	1172266101
	.long	-589951537
	.long	-1412350631
	.long	651767980
	.long	1373503546
	.long	-925412992
	.long	-1076862698
	.long	565507253
	.long	1454621731
	.long	-809855591
	.long	-1195530993
	.long	671266974
	.long	1594198024
	.long	-972236366
	.long	-1324619484
	.long	795835527
	.long	1483230225
	.long	-1050600021
	.long	-1234817731
	.long	1994146192
	.long	31158534
	.long	-1731059524
	.long	-271249366
	.long	1907459465
	.long	112637215
	.long	-1614814043
	.long	-390540237
	.long	2013776290
	.long	251722036
	.long	-1777751922
	.long	-519137256
	.long	2137656763
	.long	141376813
	.long	-1855689577
	.long	-429695999
	.long	1802195444
	.long	476864866
	.long	-2056965928
	.long	-228458418
	.long	1812370925
	.long	453092731
	.long	-2113342271
	.long	-183516073
	.long	1706088902
	.long	314042704
	.long	-1950435094
	.long	-54949764
	.long	1658658271
	.long	366619977
	.long	-1932296973
	.long	-69972891
	.long	1303535960
	.long	984961486
	.long	-1547960204
	.long	-725929758
	.long	1256170817
	.long	1037604311
	.long	-1529756563
	.long	-740887301
	.long	1131014506
	.long	879679996
	.long	-1385723834
	.long	-631195440
	.long	1141124467
	.long	855842277
	.long	-1442165665
	.long	-586318647
	.long	1342533948
	.long	654459306
	.long	-1106571248
	.long	-921952122
	.long	1466479909
	.long	544179635
	.long	-1184443383
	.long	-832445281
	.long	1591671054
	.long	702138776
	.long	-1328506846
	.long	-942167884
	.long	1504918807
	.long	783551873
	.long	-1212326853
	.long	-1061524307
	.long	-306674912
	.long	-1698712650
	.long	62317068
	.long	1957810842
	.long	-355121351
	.long	-1647151185
	.long	81470997
	.long	1943803523
	.long	-480048366
	.long	-1805370492
	.long	225274430
	.long	2053790376
	.long	-468791541
	.long	-1828061283
	.long	167816743
	.long	2097651377
	.long	-267414716
	.long	-2029476910
	.long	503444072
	.long	1762050814
	.long	-144550051
	.long	-2140837941
	.long	426522225
	.long	1852507879
	.long	-19653770
	.long	-1982649376
	.long	282753626
	.long	1742555852
	.long	-105259153
	.long	-1900089351
	.long	397917763
	.long	1622183637
	.long	-690576408
	.long	-1580100738
	.long	953729732
	.long	1340076626
	.long	-776247311
	.long	-1497606297
	.long	1068828381
	.long	1219638859
	.long	-670225446
	.long	-1358292148
	.long	906185462
	.long	1090812512
	.long	-547295293
	.long	-1469587627
	.long	829329135
	.long	1181335161
	.long	-882789492
	.long	-1134132454
	.long	628085408
	.long	1382605366
	.long	-871598187
	.long	-1156888829
	.long	570562233
	.long	1426400815
	.long	-977650754
	.long	-1296233688
	.long	733239954
	.long	1555261956
	.long	-1026031705
	.long	-1244606671
	.long	752459403
	.long	1541320221
	.long	-1687895376
	.long	-328994266
	.long	1969922972
	.long	40735498
	.long	-1677130071
	.long	-351390145
	.long	1913087877
	.long	83908371
	.long	-1782625662
	.long	-491226604
	.long	2075208622
	.long	213261112
	.long	-1831694693
	.long	-438977011
	.long	2094854071
	.long	198958881
	.long	-2032938284
	.long	-237706686
	.long	1759359992
	.long	534414190
	.long	-2118248755
	.long	-155638181
	.long	1873836001
	.long	414664567
	.long	-2012718362
	.long	-15766928
	.long	1711684554
	.long	285281116
	.long	-1889165569
	.long	-127750551
	.long	1634467795
	.long	376229701
	.long	-1609899400
	.long	-686959890
	.long	1308918612
	.long	956543938
	.long	-1486412191
	.long	-799009033
	.long	1231636301
	.long	1047427035
	.long	-1362007478
	.long	-640263460
	.long	1088359270
	.long	936918000
	.long	-1447252397
	.long	-558129467
	.long	1202900863
	.long	817233897
	.long	-1111625188
	.long	-893730166
	.long	1404277552
	.long	615818150
	.long	-1160759803
	.long	-841546093
	.long	1423857449
	.long	601450431
	.long	-1285129682
	.long	-1000256840
	.long	1567103746
	.long	711928724
	.long	-1274298825
	.long	-1022587231
	.long	1510334235
	.long	755167117
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	16
	.long	16
	.long	16
	.long	16
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.ident	"GCC: (Debian 4.7.2-5) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
