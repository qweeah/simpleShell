	.file	"myProcess.c"
	.section	.rodata
.LC0:
	.string	"$$"
	.data
	.align 8
	.type	_ZL6prompt, @object
	.size	_ZL6prompt, 8
_ZL6prompt:
	.quad	.LC0
	.local	_ZL8localBuf
	.comm	_ZL8localBuf,128,32
	.section	.rodata
.LC1:
	.string	"%s"
	.text
	.globl	_Z10ShowPromptv
	.type	_Z10ShowPromptv, @function
_Z10ShowPromptv:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	_ZL6prompt(%rip), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_Z10ShowPromptv, .-_Z10ShowPromptv
	.globl	_Z10GetOneLinePc
	.type	_Z10GetOneLinePc, @function
_Z10GetOneLinePc:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
.L8:
	call	getchar
	movb	%al, -5(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-5(%rbp), %eax
	movb	%al, (%rdx)
	cmpb	$-1, -5(%rbp)
	jne	.L4
	movl	-4(%rbp), %eax
	jmp	.L5
.L4:
	cmpb	$10, -5(%rbp)
	je	.L6
	cmpb	$0, -5(%rbp)
	je	.L6
	addl	$1, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L6
	movl	$1, %eax
	jmp	.L7
.L6:
	movl	$0, %eax
.L7:
	testb	%al, %al
	jne	.L8
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movl	-4(%rbp), %eax
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_Z10GetOneLinePc, .-_Z10GetOneLinePc
	.section	.rodata
	.align 8
.LC2:
	.string	"Currently working directory: %s"
.LC3:
	.string	"Execution error!"
	.text
	.type	_ZL14enterDirectoryPc, @function
_ZL14enterDirectoryPc:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	chdir
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L10
	movl	$128, %esi
	movl	$_ZL8localBuf, %edi
	call	getcwd
	testq	%rax, %rax
	sete	%al
	testb	%al, %al
	je	.L10
	movl	$_ZL8localBuf, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	jmp	.L9
.L10:
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	_ZL14enterDirectoryPc, .-_ZL14enterDirectoryPc
	.section	.rodata
.LC4:
	.string	"cd"
.LC5:
	.string	"No directory argument"
	.text
	.globl	_Z14BuildInCommandiPPc
	.type	_Z14BuildInCommandiPPc, @function
_Z14BuildInCommandiPPc:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1, -4(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L13
	cmpl	$1, -20(%rbp)
	jg	.L14
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	-4(%rbp), %eax
	jmp	.L15
.L14:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	_ZL14enterDirectoryPc
	jmp	.L16
.L13:
	movl	$0, -4(%rbp)
.L16:
	movl	-4(%rbp), %eax
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z14BuildInCommandiPPc, .-_Z14BuildInCommandiPPc
	.type	_ZL12SplitCommandPcPS_, @function
_ZL12SplitCommandPcPS_:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -12(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L18
.L19:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L18
	movl	-12(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -12(%rbp)
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
.L18:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L19
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	_ZL12SplitCommandPcPS_, .-_ZL12SplitCommandPcPS_
	.type	_ZL11ExecCommandPc, @function
_ZL11ExecCommandPc:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1048, %rsp
	movq	%rdi, -1048(%rbp)
	leaq	-1024(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	-1048(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZL12SplitCommandPcPS_
	movl	%eax, -1028(%rbp)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	_ZL11ExecCommandPc, .-_ZL11ExecCommandPc
	.section	.rodata
	.type	_ZL5token, @object
	.size	_ZL5token, 1
_ZL5token:
	.byte	32
	.align 8
	.type	_ZL13LOCALBUF_SIZE, @object
	.size	_ZL13LOCALBUF_SIZE, 8
_ZL13LOCALBUF_SIZE:
	.quad	128
	.align 4
	.type	_ZL14MAX_OPTION_CNT, @object
	.size	_ZL14MAX_OPTION_CNT, 4
_ZL14MAX_OPTION_CNT:
	.long	128
	.align 4
	.type	_ZL15MAX_COMMAND_LEN, @object
	.size	_ZL15MAX_COMMAND_LEN, 4
_ZL15MAX_COMMAND_LEN:
	.long	128
	.align 32
	.type	_ZL10builtInCmd, @object
	.size	_ZL10builtInCmd, 256
_ZL10builtInCmd:
	.string	"cd"
	.zero	125
	.string	"echo"
	.zero	123
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
