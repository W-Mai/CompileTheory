ASSUME CS:codesg,DS:datasg
datasg segment
    x DB '?'
    y DB '?'
    z DB '?'
    tmpB DB 'Please input x and y :\n$'
    tmpC DB '?'
    tmpD DB '?'
    tmpE DB '?'
    tmpF DB '?'
    tmpG DB '?'
datasg ends
codesg segment
  start:
    mov AX,datasg
    mov DS,AX
    LEA DX,tmpB
    mov AH,09
    int 21H
    mov AL,y
    mov BH,5
    mul BH
    mov BL,1
    div BL
    mov tmpC,AL
    mov BL,x
    add BL,tmpC
    mov tmpD,BL
    mov AL,4
    CBW
    mov BL,3
    div BL
    mov tmpE,AL
    mov AL,tmpD
    mov BH,tmpE
    mul BH
    mov BL,1
    div BL
    mov tmpF,AL
    mov BL,tmpF
    mov z,BL
    mov AL,z
    CMP AL,10
    JG stepB
    JMP stepC
  stepB:
