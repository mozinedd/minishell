minishell$ export =
 
final command : export
 
final command: =
=================================================================
==74419==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000b24f at pc 0x00010400b62e bp 0x7ffeebc0d050 sp 0x7ffeebc0d048


minishell$ export =a
 
final command : export
 
final command: =a
=================================================================
==74549==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000416f at pc 0x00010412162e bp 0x7ffeebaf7050 sp 0x7ffeebaf7048





minishell$ >a <d >b >c ls ## if file faild not run cmd
 
final command : ls
 
final command: (null)

---------------------------------
mamima: 39
No such file or directory
Makefile        a               c               lib             should_fix
README.md       b               includes        minishell       srcs
minishell$ 




➜  minishell git:(ysouaf) ✗ env -i ./minishell
minishell$ export f=fff
 
final command : export
 
final command: f=fff

---------------------------------
haneasldkjf;ldasfj 
minishell$ unset f
 
final command : unset
 
final command: f

---------------------------------
AddressSanitizer:DEADLYSIGNAL
=================================================================
==69505==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000008 (pc 0x7fff6eb9a94d bp 0x7ffee1c9b360 sp 0x7ffee1c9b360 T0)
==69505==The signal is caused by a READ memory access.
==69505==Hint: address points to the zero page.
    #0 0x7fff6eb9a94d in _platform_memmove$VARIANT$Haswell+0x4d (/usr/lib/system/libsystem_platform.dylib:x86_64+0x94d)
    #1 0x10e039386 in __asan_memcpy+0x296 (/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x47386)
    #2 0x10df81386 in remove_key+0x1c6 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x10001d386)
    #3 0x10df81492 in ft_unset+0xb2 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x10001d492)
    #4 0x10df7fff2 in exec_is_builtin+0x492 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x10001bff2)
    #5 0x10df81b19 in execute_command+0xc9 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x10001db19)
    #6 0x10df7a312 in mshll_loop+0x192 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x100016312)
    #7 0x10df7a3a2 in main+0x22 (/mnt/homes/ysouaf/Desktop/minishell/./minishell:x86_64+0x1000163a2)
    #8 0x7fff6e9a4cc8 in start+0x0 (/usr/lib/system/libdyld.dylib:x86_64+0x1acc8)

==69505==Register values:
rax = 0x0000603000001c30  rbx = 0x0000000000000018  rcx = 0x00000c0600000301  rdx = 0x0000000000000018  
rdi = 0x0000603000001c30  rsi = 0x0000000000000000  rbp = 0x00007ffee1c9b360  rsp = 0x00007ffee1c9b360  
 r8 = 0x0000000000013002   r9 = 0x0000000000000000  r10 = 0x000000010fccd420  r11 = 0x0000603000001c30  
r12 = 0x0000000000000000  r13 = 0x0000000000000000  r14 = 0x0000000000000000  r15 = 0x0000603000001c30  
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/usr/lib/system/libsystem_platform.dylib:x86_64+0x94d) in _platform_memmove$VARIANT$Haswell+0x4d
==69505==ABORTING
[1]    69505 abort      env -i ./minishell