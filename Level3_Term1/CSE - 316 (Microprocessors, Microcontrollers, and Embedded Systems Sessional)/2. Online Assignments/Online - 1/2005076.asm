                                                       ;ONline- 1: Count Characters (2005076) 

name "Problem 1"   

.MODEL SMALL

.STACK 100H

.DATA
    CR  EQU 0DH
    LF  EQU 0AH
    TAB EQU 09H
    
    PROMPT DB "Enter two integer numbers separated by space : $" 
    MSG1 DB CR,LF,TAB,"Vowel Count: $"
    MSG2 DB CR,LF,TAB,"Consonant Count: $"
     
                                           
                                           
    V  DW 0
    C DW 0  
    ANS DW ? 
    
    
    INPUT DW "eruiaaageruiaaag$"
    


.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
     
    
    LEA SI, INPUT 
    
    START: 
    
    CMP [SI], '$'
    JE  FINISH
    
    CMP [SI], 'i'
    JE  VOWEL 
    
    CMP [SI], 'o'
    JE  VOWEL 
 
    
    CMP [SI], 'a'
    JE  VOWEL 
   
    
    CMP [SI], 'e'
    JE  VOWEL 
    
    
    CMP [SI], 'u'
    JE  VOWEL 
    
    ADD C, 1
    ADD SI,1 
    JMP START
    
    VOWEL:
        ADD V,1 
        ADD SI, 1
        JMP START
        
        
    FINISH:
        LEA DX, MSG1
        MOV AH, 9H
        INT 21H
        
        MOV DX, V
        CALL OUTPUT_NUMBER
        
        LEA DX, MSG2
        MOV AH, 9H
        INT 21H
        
        MOV DX, C
        CALL OUTPUT_NUMBER 
    
    
    MOV AH, 4CH
    INT 21H
       
MAIN ENDP 


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