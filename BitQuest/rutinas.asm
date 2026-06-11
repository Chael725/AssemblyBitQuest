global contar_entidades

section .text

contar_entidades:
    mov dword [rdx], 0
    mov dword [r8], 0
    mov dword [r9], 0

    mov rax, 0
    mov r10, 3660

.ciclo:
    cmp rax, r10
    jge .fin

    movzx r11, byte [rcx + rax]  

    cmp r11b, '&'
    je .es_enemigo

    cmp r11b, 'K'
    je .es_llave

    cmp r11b, 'M'
    je .es_moneda

    jmp .siguiente

.es_enemigo:
    add dword [rdx], 1
    jmp .siguiente

.es_llave:
    add dword [r8], 1
    jmp .siguiente

.es_moneda:
    add dword [r9], 1

.siguiente:
    inc rax
    jmp .ciclo

.fin:
    ret