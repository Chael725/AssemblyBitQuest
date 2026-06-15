global contar_entidades
global validar_movimiento
global calcular_puntaje

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

validar_movimiento:
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    movsxd rax, eax

    movzx r10, byte [rcx + rax]

    cmp r10b, '#'
    je .bloqueado

.valido:
    mov eax, 1
    ret

.bloqueado:
    mov eax, 0
    ret

calcular_puntaje:
    mov eax, ecx
    imul eax, 100

    mov r10d, r8d
    imul r10d, 500

    add eax, r10d

    sub eax, edx

    cmp eax, 0
    jge .fin_puntaje
    mov eax, 0

.fin_puntaje:
    ret
