; primes.asm  –  Sieve of Eratosthenes, x86-64 Linux, no libc
; nasm -f elf64 primes.asm -o primes.o && ld -o primes primes.o
; ./primes <n>

bits 64
global _start

section .rodata
usage_msg: db "Usage: primes <n>", 10
usage_len  equ $ - usage_msg

section .text

; ── parse_ulong ─────────────────────────────────────────────────────────────
; in:  rdi = ASCII string ptr
; out: rax = parsed value
parse_ulong:
    xor  rax, rax
.L: movzx ecx, byte [rdi]
    sub   ecx, '0'
    cmp   ecx, 9
    ja    .R
    imul  rax, rax, 10
    add   rax, rcx
    inc   rdi
    jmp   .L
.R: ret

; ── print_uint64 ─────────────────────────────────────────────────────────────
; in: rdi = value  →  writes decimal + newline to stdout
print_uint64:
    push  rbx
    sub   rsp, 24
    lea   rbx, [rsp + 23]
    mov   byte [rbx], 10        ; newline at end
.C: dec   rbx
    xor   edx, edx
    mov   rax, rdi
    mov   ecx, 10
    div   rcx                   ; rax=quotient, rdx=remainder
    mov   rdi, rax
    add   dl, '0'
    mov   [rbx], dl
    test  rdi, rdi
    jnz   .C
    lea   rdx, [rsp + 24]
    sub   rdx, rbx              ; length (digits + newline)
    mov   rsi, rbx              ; buffer ptr
    mov   rdi, 1                ; fd=stdout
    mov   rax, 1                ; SYS_write
    syscall
    add   rsp, 24
    pop   rbx
    ret

; ── _start ───────────────────────────────────────────────────────────────────
_start:
    cmp   qword [rsp], 2        ; argc == 2?
    jne   .usage

    mov   rdi, [rsp + 16]       ; argv[1]
    call  parse_ulong
    mov   r15, rax              ; r15 = n

    cmp   r15, 3
    jbe   .small                ; n ≤ 3: special-case

    ; r14 = limit = n / 2
    ; index k  ↔  odd number 2k+1  (k=1→3, k=2→5, ...)
    mov   r14, r15
    shr   r14, 1

    ; mmap a zeroed bit-sieve: (limit+7)/8 bytes
    lea   rsi, [r14 + 7]
    shr   rsi, 3                ; byte count
    xor   rdi, rdi              ; NULL
    mov   rdx, 3                ; PROT_READ|PROT_WRITE
    mov   r10, 0x22             ; MAP_PRIVATE|MAP_ANONYMOUS
    mov   r8,  -1               ; fd=-1
    xor   r9,  r9               ; offset=0
    mov   rax, 9                ; SYS_mmap
    syscall
    js    .exit1                ; mmap failed
    mov   r12, rax              ; r12 = sieve base

    ; ── outer sieve loop: k = 1, 2, 3, … while (2k+1)² ≤ n ─────────────
    mov   r13, 1

.outer:
    lea   rax, [r13*2 + 1]      ; p = 2k+1
    imul  rax, rax              ; p²
    cmp   rax, r15
    ja    .sieve_done

    ; IS_COMPOSITE(k) ?  →  sieve[k>>3] >> (k&7) & 1
    mov   rcx, r13
    and   ecx, 7                ; bit index
    mov   rax, r13
    shr   rax, 3                ; byte index
    movzx eax, byte [r12 + rax]
    shr   eax, cl
    test  eax, 1
    jnz   .onext                ; composite: skip

    ; r11 = p (inner step),  rbx = j = (p²−1)/2  (start index)
    lea   r11, [r13*2 + 1]      ; p
    mov   rbx, r11
    imul  rbx, rbx              ; p²
    dec   rbx
    shr   rbx, 1                ; j = (p²-1)/2

    ; ── inner loop: SET_COMPOSITE for j, j+p, j+2p, … ──────────────────
.inner:
    cmp   rbx, r14
    jae   .onext
    mov   rax, rbx
    shr   rax, 3                ; byte index
    mov   ecx, ebx
    and   ecx, 7                ; bit index
    mov   dl, 1
    shl   dl, cl
    or    byte [r12 + rax], dl  ; set composite bit
    add   rbx, r11              ; j += p
    jmp   .inner

.onext:
    inc   r13
    jmp   .outer

    ; ── scan backwards from n-1 for the largest prime ────────────────────
.sieve_done:
    mov   r13, r15
    dec   r13                   ; start at n-1
    test  r13b, 1               ; odd?
    jnz   .scan
    dec   r13                   ; nudge down to odd

.scan:
    cmp   r13, 3
    jb    .ret2                 ; fell past 3 → answer is 2
    mov   rax, r13
    dec   rax
    shr   rax, 1                ; k = (p-1)/2
    mov   rcx, rax
    and   ecx, 7
    shr   rax, 3
    movzx edx, byte [r12 + rax]
    shr   edx, cl
    test  edx, 1
    jz    .found                ; bit clear → prime!
    sub   r13, 2
    jmp   .scan

.found:
    mov   rdi, r13
    call  print_uint64
    jmp   .exit0

.ret2:
    mov   rdi, 2
    call  print_uint64
    jmp   .exit0

.small:
    cmp   r15, 3                ; n==3 → largest prime < 3 is 2
    je    .ret2
    xor   rdi, rdi              ; n<3 → print 0
    call  print_uint64

.exit0:
    xor   edi, edi
    mov   eax, 60               ; SYS_exit(0)
    syscall

.exit1:
    mov   edi, 1
    mov   eax, 60
    syscall

.usage:
    mov   rdi, 2                ; stderr
    lea   rsi, [rel usage_msg]
    mov   rdx, usage_len
    mov   rax, 1
    syscall
    mov   edi, 1
    mov   eax, 60
    syscall
