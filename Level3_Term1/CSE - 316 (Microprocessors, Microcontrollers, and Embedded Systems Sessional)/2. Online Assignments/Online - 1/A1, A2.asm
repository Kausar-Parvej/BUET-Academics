                            .MODEL SMALL
.STACK 100H
.DATA  
NEWLINE  DB 0AH,0DH,'$' 
PROMPT   DW 'ASCENDING $'
PROMPT2  DW 'DESCENDING $'
PROMPT3  DW 'NOT SORTED $'
ARR     DW 90,90,70,60,50,40,30,20,20,5
N       DW 10  
K       DW ? 
C       DW 0 
T       DW 0  
R       DW 0

.CODE   



MAIN PROC
      MOV AX,@DATA
      MOV DS,AX   
      
      LEA SI,ARR
      
      MOV CX,N  
      MOV BX,[SI]
      
      
  FRST_LOOP:
      MOV AX,[SI] 
      ADD SI,2   
      DEC CX
      
      CMP AX,BX
      JG ASC_LOOP
      
      CMP AX,BX  
      JL DESC_LOOP
       
      INC CX
      MOV BX,AX
      
      LOOP FRST_LOOP 
      
  JMP ASC    
      
  ASC_LOOP:
      MOV BX,AX 
      
      MOV AX,[SI]
      CMP AX,BX
      JL NOTS
      
      ADD SI,2
      
      LOOP ASC_LOOP 
      
  JMP ASC
  
  
  DESC_LOOP:
       MOV BX,AX
       
       MOV AX,[SI]
       CMP AX,BX
       JG NOTS   
       
       ADD SI,2
       
       LOOP DESC_LOOP
       
   JMP DESC 
   
   
   ASC:
      LEA DX,PROMPT 
      JMP PRINT 
   DESC:
      LEA DX,PROMPT2
      JMP PRINT
      
   NOTS:
      LEA DX,PROMPT3
      JMP PRINT
      
   PRINT:
       MOV AH,9
       INT 21H
       MOV AH,4CH
       INT 21H
       
       
   ENDP MAIN