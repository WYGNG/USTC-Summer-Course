ASSUME CS:CODE,DS:DATA
DATA SEGMENT
    BUFF DW 123,13,9,11,33,8,53,76,100,3
DATA ENDS
CODE SEGMENT
START: 
	MOV AX,DATA
        MOV DS,AX
        MOV CX,9	  ;外层循环9趟
SORT:  
	PUSH CX           ;保存外层循环次数,外层第1次循环，内循环执行9次，外层第2次循环，内循环执行8次，...控制外层循环的cx值正好是内层循环次数
        MOV SI,OFFSET BUFF
NEICENG:
	MOV AX,[SI]       ;(ax)即a[j]
        CMP AX,[SI+2]     ;a[j]与a[j+1]比较
        JBE SWAP          ;小于等于时跳转，即a[j]<=a[j+1]时不交换
        XCHG AX,[SI+2]    ;交换
        MOV [SI],AX       ;交换完成
SWAP: 
	ADD SI,2          ;a[j]<=a[j+1]时，跳到下一个待排序的数
        LOOP NEICENG      ;内层循环
        POP CX            ;恢复外层循环的cx
        LOOP SORT         ;外层循环

        MOV AX,4C00H
        INT 21H
CODE ENDS
	END START