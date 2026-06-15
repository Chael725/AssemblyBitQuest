global contar_entidades, detectar_objeto, contar_celdas_libres

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

;Funcion 4: detectar_objeto
detectar_objeto:
    xor rax, rax
    xor r10, r10
    
    mov eax, r8d       
    imul eax, edx       
    add eax, r9d       
    
    mov r10b, byte [rcx + rax] 
    

    mov r11b, byte [rsp + 40]  
    
    cmp r10b, r11b
    jne .falso
    
.verdadero:
    mov rax, 1         
    ret
    
.falso:
    mov rax, 0          
    ret


;Funcion 5: contar_celdas_libres
contar_celdas_libres:
    xor rax, rax        
    xor r8, r8         
    
.ciclo_libres:
    cmp eax, edx        
    jge .fin_libres
    
    mov r9b, byte [rcx + rax]  
    cmp r9b, '.'               
    jne .no_es_libre
    
    inc r8d             
    
.no_es_libre:
    inc rax           
    jmp .ciclo_libres
    
.fin_libres:
    mov rax, r8       
    ret