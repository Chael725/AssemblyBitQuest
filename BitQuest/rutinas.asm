; Exportamos las funciones para poder llamarlas desde el archivo main.c
global contar_entidades, detectar_objeto, contar_celdas_libres, validar_movimiento, calcular_puntaje

section .text

; Función 1: Cuenta enemigos, llaves y monedas en el mapa
contar_entidades:
    ; Inicializamos los contadores en 0
    mov dword [rdx], 0
    mov dword [r8], 0
    mov dword [r9], 0

    mov rax, 0         ; Índice actual (i = 0)
    mov r10, 3660      ; Total de caracteres a recorrer (60x61)

.ciclo:
    cmp rax, r10       ; ¿Terminamos de recorrer el mapa?
    jge .fin           ; Si es así, salimos al final

    movzx r11, byte [rcx + rax]  ; Leemos un caracter del mapa

    ; Comparamos qué caracter es y saltamos a sumarlo
    cmp r11b, '&'
    je .es_enemigo
    cmp r11b, 'K'
    je .es_llave
    cmp r11b, 'M'
    je .es_moneda
    jmp .siguiente     ; Si no es ninguno, avanzamos

.es_enemigo:
    add dword [rdx], 1
    jmp .siguiente
.es_llave:
    add dword [r8], 1
    jmp .siguiente
.es_moneda:
    add dword [r9], 1

.siguiente:
    inc rax            ; i++
    jmp .ciclo         ; Volvemos a repetir

.fin:
    ret                ; Regresamos a C

; Función 2: Verifica si un objeto específico está en una coordenada
detectar_objeto:
    xor rax, rax
    xor r10, r10

    ; Calculamos el índice lineal: (fila * columnas) + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    ; Leemos el caracter en esa posición exacta
    mov r10b, byte [rcx + rax]
    mov r11b, byte [rsp + 40]  ; Leemos el quinto parámetro (el objeto a buscar)

    cmp r10b, r11b     ; ¿Coinciden?
    jne .falso

.verdadero:
    mov rax, 1         ; Retornamos 1 (Verdadero)
    ret

.falso:
    mov rax, 0         ; Retornamos 0 (Falso)
    ret

; Función 3: Cuenta todas las celdas vacías ('.') del mapa
contar_celdas_libres:
    xor rax, rax        ; Índice
    xor r8, r8          ; Contador de espacios libres

.ciclo_libres:
    cmp eax, edx        ; ¿Llegamos al final del mapa?
    jge .fin_libres

    mov r9b, byte [rcx + rax]
    cmp r9b, '.'        ; ¿Es un espacio vacío?
    jne .no_es_libre

    inc r8d             ; Si es vacío, incrementamos el contador

.no_es_libre:
    inc rax
    jmp .ciclo_libres

.fin_libres:
    mov rax, r8         ; Retornamos el total de celdas libres
    ret

; Función 4: Valida si el próximo movimiento choca con una pared
validar_movimiento:
    ; Calculamos la posición en memoria: (fila * columnas) + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    movsxd rax, eax

    movzx r10, byte [rcx + rax]  ; Obtenemos el caracter

    cmp r10b, '#'       ; ¿Es una pared?
    je .bloqueado

.valido:
    mov eax, 1          ; Retornamos 1 (Movimiento válido)
    ret

.bloqueado:
    mov eax, 0          ; Retornamos 0 (Bloqueado)
    ret

; Función 5: Calcula el puntaje evitando resultados negativos
calcular_puntaje:
    mov eax, ecx
    imul eax, 100       ; Monedas * 100

    mov r10d, r8d
    imul r10d, 500      ; Niveles * 500

    add eax, r10d       ; Sumamos premios (Monedas + Niveles)
    sub eax, edx        ; Restamos castigo (Pasos)

    cmp eax, 0          ; ¿El puntaje quedó debajo de 0?
    jge .fin_puntaje
    mov eax, 0          ; Forzamos el puntaje a 0 si es negativo

.fin_puntaje:
    ret                 ; Retornamos el total
