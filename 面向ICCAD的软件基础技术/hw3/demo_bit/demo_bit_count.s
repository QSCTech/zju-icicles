.text  # start of code segment

.globl bit_count
bit_count:
	push   %rbp
	mov    %rsp,%rbp
	push   %r12
	push   %rbx
	mov    %rdi,-0x28(%rbp)
	movq   $0x1,-0x18(%rbp)
	mov    $0x0,%ebx
	mov    $0x0,%r12d
	jmp    label1
label3:
	mov    -0x28(%rbp),%rax
	and    -0x18(%rbp),%rax
	test   %rax,%rax
	je     label2
	add    $0x1,%ebx
label2:
	shlq   -0x18(%rbp)
	add    $0x1,%r12d
label1:
	cmp    $0x3f,%r12d
	jle    label3
	mov    %ebx,%eax
	pop    %rbx
	pop    %r12
	pop    %rbp
	retq   

# the above assembly code is a translation of the C subroutine below
# variable assigments are,
# n <- -0x28(%rbp) <- %rdi
# i <- %r12d
# c <- %ebx
# one <- -0x18(%rbp)
# return vaule <- %eax
#int bit_count(long n)
#{
#        register int i, c;
#        long one = 1;
#        c = 0;
#        for(i=0; i<64; i++) {
#                if(n&one) 
#                {
#                   ++c;
#                }
#                one = one << 1;
#        }
#        return(c);
#}
