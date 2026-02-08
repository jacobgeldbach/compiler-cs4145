* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/c0g.c-
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load parameter 
 19:   OUTB  3,3,3	Output bool 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab char input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* Compound Body
* EXPRESSION
 40:    LDC  3,3(6)	Load integer constant 
 41:     ST  3,-2(1)	Push index 
* TOFF dec: -3
 42:    LDC  3,1023(6)	Load integer constant 
* TOFF inc: -2
 43:     LD  4,-2(1)	Pop index 
 44:    LDA  5,-1(0)	Load address of base of array x
 45:    SUB  5,5,4	Compute offset of value 
 46:     ST  3,0(5)	Store variable x
* EXPRESSION
* CALL output
 47:     ST  1,-2(1)	Store fp in ghost frame for output
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 48:    LDC  3,3(6)	Load integer constant 
 49:     ST  3,-4(1)	Push index 
* TOFF dec: -5
* TOFF inc: -4
 50:     LD  4,-4(1)	Pop index 
 51:    LDA  5,-1(0)	Load address of base of array x
 52:    SUB  5,5,4	Compute offset of value 
 53:     LD  4,0(5)	load lhs variable x
 54:     LD  3,-1(0)	load lhs variable x
 55:    LDA  3,1(3)	increment value of x
 56:     ST  3,0(5)	Store variable x
 57:     ST  3,-4(1)	Push parameter 
* TOFF dec: -5
* Param end output
 58:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 59:    LDA  3,1(7)	Return address in ac 
 60:    JMP  7,-55(7)	CALL output
 61:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -2
* EXPRESSION
* CALL outnl
 62:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
 63:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 64:    LDA  3,1(7)	Return address in ac 
 65:    JMP  7,-32(7)	CALL outnl
 66:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* EXPRESSION
* CALL output
 67:     ST  1,-2(1)	Store fp in ghost frame for output
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 68:    LDA  3,-1(0)	Load address of base of array x
 69:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 70:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -4
 71:     LD  4,-4(1)	Pop left into ac1 
 72:    SUB  3,4,3	compute location from index 
 73:     LD  3,0(3)	Load array element 
 74:     ST  3,-4(1)	Push parameter 
* TOFF dec: -5
* Param end output
 75:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 76:    LDA  3,1(7)	Return address in ac 
 77:    JMP  7,-72(7)	CALL output
 78:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -2
* EXPRESSION
* CALL outnl
 79:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
 80:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 81:    LDA  3,1(7)	Return address in ac 
 82:    JMP  7,-49(7)	CALL outnl
 83:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* EXPRESSION
* CALL output
 84:     ST  1,-2(1)	Store fp in ghost frame for output
* TOFF dec: -3
* TOFF dec: -4
* Param 1
 85:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -3
 86:     LD  4,-3(1)	Pop left into ac1 
 87:    SUB  3,4,3	compute location from index 
 88:     LD  3,0(3)	Load array element 
 89:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* TOFF inc: -3
 90:     LD  4,-3(1)	Pop index 
 91:    LDA  5,-1(0)	Load address of base of array x
 92:    SUB  5,5,4	Compute offset of value 
 93:     LD  4,0(5)	load lhs variable x
 94:     ST  3,0(5)	Store variable x
 95:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* Param end output
 96:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 97:    LDA  3,1(7)	Return address in ac 
 98:    JMP  7,-93(7)	CALL output
 99:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -2
* EXPRESSION
* CALL outnl
100:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
101:    LDA  1,-2(1)	Ghost frame becomes new active frame 
102:    LDA  3,1(7)	Return address in ac 
103:    JMP  7,-70(7)	CALL outnl
104:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* EXPRESSION
* CALL output
105:     ST  1,-2(1)	Store fp in ghost frame for output
* TOFF dec: -3
* TOFF dec: -4
* Param 1
106:    LDA  3,-1(0)	Load address of base of array x
107:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
108:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -4
109:     LD  4,-4(1)	Pop left into ac1 
110:    SUB  3,4,3	compute location from index 
111:     LD  3,0(3)	Load array element 
112:     ST  3,-4(1)	Push parameter 
* TOFF dec: -5
* Param end output
113:    LDA  1,-2(1)	Ghost frame becomes new active frame 
114:    LDA  3,1(7)	Return address in ac 
115:    JMP  7,-110(7)	CALL output
116:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -2
* EXPRESSION
* CALL outnl
117:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
118:    LDA  1,-2(1)	Ghost frame becomes new active frame 
119:    LDA  3,1(7)	Return address in ac 
120:    JMP  7,-87(7)	CALL outnl
121:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
122:    LDC  2,0(6)	Set return value to 0 
123:     LD  3,-1(1)	Load return address 
124:     LD  1,0(1)	Adjust fp 
125:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,125(7)	Jump to init [backpatch] 
* INIT
126:    LDA  1,-8(0)	set first frame at end of globals 
127:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
128:    LDC  3,7(6)	load size of array x
129:     ST  3,0(0)	save size of array x
* END INIT GLOBALS AND STATICS
130:    LDA  3,1(7)	Return address in ac 
131:    JMP  7,-93(7)	Jump to main 
132:   HALT  0,0,0	DONE! 
* END INIT
