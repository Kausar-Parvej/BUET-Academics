                ;Offline- 2: Count Chocolates (2005076) 

name "Problem 1"   

.MODEL SMALL

.STACK 100H

.DATA
    CR  EQU 0DH
    LF  EQU 0AH
    TAB EQU 09H
    
    PROMPT DB "Enter two integer numbers separated by space : $" 
    MSG1 DB CR,LF,TAB,"Invalid Input!$"
    MSG2 DB CR,LF,TAB,"Total Chocolate: $"
    MSG3 DB CR,LF,TAB,"K must be greater than 1! $"  
                                           
                                           
    N  DW ?
    K  DW ?  
    ANS DW ?
    


.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    LEA DX, PROMPT
    MOV AH, 9H
    INT 21H 
    
    CALL INPUT_NUMBER 
    MOV N, DX
    
    CALL INPUT_NUMBER 
    MOV K, DX  
    
    CMP K, 01H
    JBE INVALID_K 
    
    CALL FIND_CHOCOLATE
    
    LEA DX, MSG2
    MOV AH, 9H
    INT 21H  
    
    MOV DX, ANS
    CALL OUTPUT_NUMBER
       
    
    MOV AH, 4CH
    INT 21H  
    
    INVALID_K:
        LEA DX, MSG3
        MOV AH, 09H
        INT 21H
        
        MOV AH, 4CH
        INT 21H
       
MAIN ENDP

FIND_CHOCOLATE PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX 
    
    XOR AX,AX
    XOR BX, BX 
    
    MOV  AX, N  
    MOV  BX, K
    MOV  ANS, AX
    
    XCHG_WRAPPER:
        CMP AX, BX
        JB  END_CALC 
        
        XOR DX, DX       ; DX HOLD THE HIGH BYTES OF THE NUMERATOR, SO IT MUST BE CLEARED
        DIV BX
        
        ADD ANS, AX 
        ADD AX,  DX
        JMP XCHG_WRAPPER
        
        END_CALC:
            POP DX
            POP CX
            POP BX
            POP AX
            
            RET

FIND_CHOCOLATE ENDP



INPUT_NUMBER PROC
    PUSH AX
    PUSH BX
    PUSH CX
    
    XOR DX, DX
    XOR CX, CX
    
    SINGLE_DIGIT:
        MOV AH, 01H
        INT 21H
        
        CMP AL, 20H
        JE  END_INPUT
        
        CMP AL, 0AH
        JE  END_INPUT
        
        CMP AL, '0'
        JL  INVALID
        CMP AL, '9' 
        JG  INVALID
        
        SUB AL, 30H
        MOV BL, AL
        MOV BH, 0H
        
        MOV AL, 10D
        MOV AH, 0H
        MUL DX
        ADD AX, BX
        MOV DX, AX
        JMP SINGLE_DIGIT
        
        INVALID:
        
        END_INPUT:
            POP CX
            POP BX
            POP AX
            
            RET
            
INPUT_NUMBER ENDP  



OUTPUT_NUMBER PROC
    
      PUSH AX
      PUSH BX
      PUSH CX
      PUSH DX
      
      MOV CX, 0H
      
      SINGLE_DIGIT_OUTPUT:
        CMP DX, 0H
        JE  SHOW
        
        MOV AX, DX
        MOV BL, 10D
        MOV BH, 0H
        
        XOR DX,DX
        DIV BX
        ADD DX, 30H
        
        PUSH DX
        ADD CX, 01H
        MOV DX, AX
        JMP SINGLE_DIGIT_OUTPUT
       
       SHOW:
        CMP CX, 0H
        JE  END
        
        POP DX
        SUB CX, 01H
        
        MOV AH, 02H
        INT 21H
        JMP SHOW
        
       END:
        POP DX
        POP CX
        POP BX
        POP AX
        
        RET
        
OUTPUT_NUMBER ENDP
         
    
    END MAIN