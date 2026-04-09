;Categorize the input character into classifications:(2005076) 

name "Problem 2"   

.MODEL SMALL

.STACK 100H

.DATA
    CR  EQU 0DH
    LF  EQU 0AH
    TAB EQU 09H
    
    PROMPT DB "Enter three lowercase letters: $" 
    MSG1 DB CR,LF,TAB,"All letters are equal $"
    MSG2 DB CR,LF,TAB,"Not valid inputs $"
    MSG3 DB CR,LF,TAB,"The second-highest letter is: $"
    
    CHAR1 DB ?
    CHAR2 DB ?
    CHAR3 DB ?
    CHAR_ANS DB ?


.CODE

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    LEA DX, PROMPT
    MOV AH, 9H
    INT 21H
    
    MOV AH, 1H
    INT 21H 
    MOV CHAR1, AL  
    
    INT 21H
    MOV CHAR2, AL
    
    INT 21H
    MOV CHAR3, AL
    
    CMP CHAR1, 'a'
    JB  INVALID
    CMP CHAR1, 'z'
    JA  INVALID
    
    CMP CHAR2, 'a'
    JB  INVALID
    CMP CHAR2, 'z'
    JA  INVALID
    
    CMP CHAR3, 'a'
    JB  INVALID
    CMP CHAR3, 'z'
    JA  INVALID
    
    MOV BL, CHAR1
    CMP BL, CHAR2
    JE  CASE1
    CMP BL, CHAR2
    JA  CASE3
    CMP BL, CHAR3
    JA  ANS1
     
    MOV BL, CHAR2
    CMP BL, CHAR3
    JA  ANS3
    CMP BL, CHAR3
    JE  ANS1
    JMP ANS2 
    
    CASE1:
    MOV BL, CHAR2
    CMP BL, CHAR3
    JNE CASE2
    LEA DX, MSG1
    MOV AH, 9H
    INT 21H
    JMP END_IF
    
    CASE2: 
    MOV BL, CHAR2
    CMP BL, CHAR3
    JA  ANS3
    JMP ANS2 
    
    CASE3:
    MOV BL, CHAR2
    CMP BL, CHAR3
    JAE  ANS2
    
    MOV BL,CHAR1
    CMP BL, CHAR3
    JA  ANS3
    CMP BL,CHAR3
    JE  ANS2
    JMP ANS1
    
    ANS1:
    MOV DL, CHAR1
    MOV CHAR_ANS, DL
    JMP DISPLAY
    
    ANS2:
    MOV DL, CHAR2
    MOV CHAR_ANS, DL
    JMP DISPLAY
    
    ANS3:
    MOV DL, CHAR3
    MOV CHAR_ANS, DL
    JMP DISPLAY
    
    
    INVALID:
    LEA DX, MSG2
    MOV AH, 9H
    INT 21H
    JMP END_IF
    
    DISPLAY:
    MOV AH, 9H
    LEA DX, MSG3
    INT 21H
    
    MOV AH, 2H 
    MOV DL, CHAR_ANS
    INT 21H
    
    END_IF:  
    MOV AH, 4CH
    INT 21H
    
    
MAIN ENDP
    
    END MAIN