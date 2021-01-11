	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	__Z15contextSwitcherP7Process ## -- Begin function _Z15contextSwitcherP7Process
	.p2align	4, 0x90
__Z15contextSwitcherP7Process:          ## @_Z15contextSwitcherP7Process
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	.cfi_offset %rbx, -24
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	32(%rdi), %rdi
	movq	%rdi, _runtimeStackPointer(%rip)
	## InlineAsm Start
	pushfq
	pushq	%rax
	pushq	%rbx
	pushq	%rcx
	pushq	%rdx
	pushq	%rbp
	pushq	%rdi
	pushq	%rsi
	pushq	%r8
	pushq	%r9
	pushq	%r10
	pushq	%r11
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15
	movq	_runtimeStackPointer(%rip), %rax
	movq	(%rax), %rbx
	movq	%rsp, (%rax)
	movq	%rbx, %rsp
	popq	%r15
	popq	%r14
	popq	%r13
	popq	%r12
	popq	%r11
	popq	%r10
	popq	%r9
	popq	%r8
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%rdx
	popq	%rcx
	popq	%rbx
	popq	%rax
	popfq
	retq
	.globl	runtimeEntryPoint
runtimeEntryPoint:
	pushfq
	pushq	%rax
	pushq	%rbx
	pushq	%rcx
	pushq	%rdx
	pushq	%rbp
	pushq	%rdi
	pushq	%rsi
	pushq	%r8
	pushq	%r9
	pushq	%r10
	pushq	%r11
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15
	movq	%rsp, %rbx
	movq	_runtimeStackPointer(%rip), %rax
	movq	(%rax), %rsp
	movq	%rbx, (%rax)
	popq	%r15
	popq	%r14
	popq	%r13
	popq	%r12
	popq	%r11
	popq	%r10
	popq	%r9
	popq	%r8
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%rdx
	popq	%rcx
	popq	%rbx
	popq	%rax
	popfq

	## InlineAsm End
	movq	_runtimeStackPointer(%rip), %rax
	movq	-16(%rbp), %rdi
	movq	%rax, 32(%rdi)
	movq	_runtimeRequestStatic(%rip), %rax
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_runtimeStackPointer    ## @runtimeStackPointer
.zerofill __DATA,__common,_runtimeStackPointer,8,3
	.globl	_runtimeRequestStatic   ## @runtimeRequestStatic
.zerofill __DATA,__common,_runtimeRequestStatic,8,3

.subsections_via_symbols
