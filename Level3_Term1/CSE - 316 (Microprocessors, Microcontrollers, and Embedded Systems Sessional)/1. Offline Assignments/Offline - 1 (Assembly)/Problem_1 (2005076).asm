;Categorize the input character into classifications:(2005076) 

name "Problem 1"   

.MODEL SMALL

.STACK 100H

.DATA
    CR  EQU 0DH
    LF  EQU 0AH
    TAB EQU 09H
    
    PROMPT DB "Enter a single printable ASCII character: $" 
    MSG1 DB CR,LF,TAB,"Uppercase letter $"
    MSG2 DB CR,LF,TAB,"Lowercase letter $"
    MSG3 DB CR,LF,TAB,"Number $"
    MSG4 DB CR,LF,TAB,"Not an alphanumeric value $"


.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    LEA DX, PROMPT
    MOV AH, 9H
    INT 21H
    
    MOV AH, 1H
    INT 21H 
    
    NUMBER:
    CMP AL, '0'
    JB  OTHER
    CMP AL, '9'
    JA  UPPER
    LEA DX, MSG3
    JMP DISPLAY
    
    UPPER:
    CMP AL, 'A'
    JB  OTHER
    CMP AL, 'Z'
    JA  LOWER
    LEA DX, MSG1
    JMP DISPLAY
    
    LOWER:
    CMP AL, 'a'
    JB  OTHER
    CMP AL, 'z'
    JA  OTHER 
    LEA DX, MSG2
    JMP DISPLAY
    
    OTHER:
    LEA DX, MSG4
    
    DISPLAY:
    MOV AH, 9H
    INT 21H  
    
    MOV AH, 4CH
    INT 21H
    
MAIN ENDP
    
    END MAIN