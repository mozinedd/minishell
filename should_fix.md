###############################################################
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


###############################################################


minishell$ >a <d >b >c ls ## if file faild not run cmd
 
final command : ls
 
final command: (null)

---------------------------------
mamima: 39
No such file or directory
Makefile        a               c               lib             should_fix
README.md       b               includes        minishell       srcs
minishell$ 


###############################################################

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
###############################################################


bash-3.2$ exit | exit | exit
bash-3.2$ 

###############################################################


bash-3.2$ ls | ls | ls | ls
Makefile        README.md       includes        lib             should_fix.md   srcs

###############################################################

minishell$ cat 
 
final command : cat
 
final command: (null)

---------------------------------
^\^\^\^\^\
 #when i click on ctrl+\ should print quit : 3 like bash and exit status must be 131
^Cminishell$    

##########################################################
minishell$ top
 
final command : top
 
final command: (null)

---------------------------------
Error opening terminal: unknown. #should run normaly like bash

############################################################

minishell$ dfsdf
 
final command : dfsdf
 
final command: (null)

---------------------------------
minishell 2: dfsdf: Command not found
minishell$ echo $?
 
final command : echo
 
final command: 127

---------------------------------
127 #normale
minishell$ echo $?
 
final command : echo
 
final command: 127

---------------------------------
127 #but here should be 0


###########################################################
minishell$ < r > t
 
final command : (null)
=================================================================
==97596==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000044a18 at pc 0x0001043b5287 bp 0x7ffeeb858350 sp 0x7ffeeb858348
READ of size 8 at 0x602000044a18 thread T0
    #0 0x1043b5286 in final_commandes+0x196 (minishell:x86_64+0x10000e286)
    #1 0x1043bcee9 in parsing+0x1b9 (minishell:x86_64+0x100015ee9)
    #2 0x1043bd230 in mshll_loop+0xb0 (minishell:x86_64+0x100016230)
    #3 0x1043bd3a2 in main+0x22 (minishell:x86_64+0x1000163a2)
    #4 0x7fff6d1cacc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

0x602000044a18 is located 0 bytes to the right of 8-byte region [0x602000044a10,0x602000044a18)
allocated by thread T0 here:
    #0 0x10447e17d in wrap_malloc+0x9d (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4917d)
    #1 0x1043bd5d3 in gc_malloc+0x33 (minishell:x86_64+0x1000165d3)
    #2 0x1043b4386 in process_command_node+0x176 (minishell:x86_64+0x10000d386)
    #3 0x1043b3faf in create_commands+0xbf (minishell:x86_64+0x10000cfaf)
    #4 0x1043bcea1 in parsing+0x171 (minishell:x86_64+0x100015ea1)
    #5 0x1043bd230 in mshll_loop+0xb0 (minishell:x86_64+0x100016230)
    #6 0x1043bd3a2 in main+0x22 (minishell:x86_64+0x1000163a2)
    #7 0x7fff6d1cacc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

SUMMARY: AddressSanitizer: heap-buffer-overflow (minishell:x86_64+0x10000e286) in final_commandes+0x196
Shadow bytes around the buggy address:
  0x1c04000088f0: fa fa fd fa fa fa 00 00 fa fa fd fa fa fa 00 00
  0x1c0400008900: fa fa fd fa fa fa 00 00 fa fa fd fa fa fa 00 00
  0x1c0400008910: fa fa 00 00 fa fa 02 fa fa fa 00 00 fa fa 00 00
  0x1c0400008920: fa fa 00 00 fa fa 02 fa fa fa 00 00 fa fa 00 00
  0x1c0400008930: fa fa 00 00 fa fa 00 00 fa fa fd fa fa fa fd fa
=>0x1c0400008940: fa fa 00[fa]fa fa 00 00 fa fa 01 fa fa fa 02 fa
  0x1c0400008950: fa fa 00 00 fa fa 01 fa fa fa 02 fa fa fa 00 00
  0x1c0400008960: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x1c0400008970: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x1c0400008980: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x1c0400008990: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==97596==ABORTING
[1]    97596 abort      ./minishell

##########################################

minishell$ clear
 
final command : clear
 
final command: (null)

---------------------------------
TERM environment variable not set


########################################


minishell$ expand 
 
final command : expand
 
final command: (null)

---------------------------------






^Cminishell$ 
###############################################################
bash-3.2$ >a cat <b >>c 
bash: b: No such file or directory
bash-3.2$ 

minishell$ >a cat <b >>c
 
final command : cat

---------------------------------
mamima: 47
No such file or directory




^\^\^\^\^\^Cminishell$ 
minishell$ 

##################################################################
