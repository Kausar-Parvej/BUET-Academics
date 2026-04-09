.MODEL SMALL
.STACK 1000H
.DATA
	number DB "00000$"
.CODE
func PROC           ; line: 1
	PUSH BP
	MOV BP, SP
	PUSH BP           ; line: 2
	MOV BX, 4
	ADD BP, BX
	MOV CX, [BP]
	POP BP
	PUSH CX
	MOV CX, 1
	POP AX
	ADD CX, AX
	MOV DX, CX
	JMP func_exit
L1:
func_exit:
	POP BP
	RET
func ENDP
main PROC           ; line: 6
	MOV AX, @DATA
	MOV DS, AX
	PUSH BP
	MOV BP, SP
	SUB SP, 2           ; line: 7
L5:
	MOV CX, 7           ; line: 8
	PUSH CX
	CALL func
	MOV CX, DX
	ADD SP, 2
	PUSH CX
	PUSH BP
	MOV BX, -2
	ADD BP, BX
	POP AX
	POP CX
	MOV [BP], CX
	MOV BP, AX
L4:
	PUSH BP           ; line: 9
	MOV BX, -2
	ADD BP, BX
	MOV AX, [BP]
	CALL PRINT_OUTPUT
	CALL PRINT_NEWLINE
	POP BP
L3:
	PUSH BP           ; line: 10
	MOV BX, -2
	ADD BP, BX
	MOV CX, [BP]
	POP BP
	MOV DX, CX
	JMP main_exit
L2:
main_exit:
	MOV AX, 4CH
	INT 21H
	ADD SP, 2
	POP BP
main ENDP

;-------------------------------
;         print library   
;-------------------------------
PRINT_OUTPUT PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	; dividend in DX:AX
	; divisor in source, CX
	MOV CX, 10
	XOR BL, BL 
	CMP AX, 0
	JGE STACK_OP 
	MOV BH, 1
	NEG AX
STACK_OP:
	XOR DX, DX
	DIV CX
	; quotient in AX, remainder in DX
	PUSH DX
	INC BL ; len++
	CMP AX, 0
	JG STACK_OP
	MOV AH, 02
	CMP BH, 1 
	JNE PRINT_LOOP
	MOV DL, '-'
	INT 21H
PRINT_LOOP:
	POP DX
	XOR DH, DH
	ADD DL, '0'
	INT 21H
	DEC BL
	CMP BL, 0
	JG PRINT_LOOP
	POP DX
	POP CX
	POP BX
	POP AX
	RET
PRINT_OUTPUT ENDP

PRINT_NEWLINE PROC
	PUSH AX
	PUSH DX
	MOV AH, 02
	MOV DL, 0DH
	INT 21H
	MOV DL, 0AH
	INT 21H
	POP DX
	POP AX
	RET
PRINT_NEWLINE ENDP
;-------------------------------

END main
