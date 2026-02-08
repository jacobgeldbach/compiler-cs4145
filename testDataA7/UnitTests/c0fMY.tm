* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/c0f.c-
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
* TOFF set: -10
 40:    LDC  3,7(6)	load size of array x
 41:     ST  3,-2(1)	save size of array x
* Compound Body
* EXPRESSION
 42:    LDC  3,3(6)	Load integer constant 
 43:     ST  3,-10(1)	Push index 
* TOFF dec: -11
 44:    LDC  3,1023(6)	Load integer constant 
* TOFF inc: -10
 45:     LD  4,-10(1)	Pop index 
 46:    LDA  5,-3(1)	Load address of base of array x
 47:    SUB  5,5,4	Compute offset of value 
 48:     ST  3,0(5)	Store variable x
* EXPRESSION
* CALL output
 49:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
 50:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -11
 51:     LD  4,-11(1)	Pop left into ac1 
 52:    SUB  3,4,3	compute location from index 
 53:     LD  3,0(3)	Load array element 
 54:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* TOFF inc: -11
 55:     LD  4,-11(1)	Pop index 
 56:    LDA  5,-3(1)	Load address of base of array x
 57:    SUB  5,5,4	Compute offset of value 
 58:     LD  4,0(5)	load lhs variable x
 59:     LD  3,-3(1)	load lhs variable x
 60:    LDA  3,1(3)	increment value of x
 61:     ST  3,0(5)	Store variable x
 62:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end output
 63:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 64:    LDA  3,1(7)	Return address in ac 
 65:    JMP  7,-60(7)	CALL output
 66:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
 67:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
 68:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 69:    LDA  3,1(7)	Return address in ac 
 70:    JMP  7,-37(7)	CALL outnl
 71:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
 72:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
 73:    LDA  3,-3(1)	Load address of base of array x
 74:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
 75:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
 76:     LD  4,-12(1)	Pop left into ac1 
 77:    SUB  3,4,3	compute location from index 
 78:     LD  3,0(3)	Load array element 
 79:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
 80:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 81:    LDA  3,1(7)	Return address in ac 
 82:    JMP  7,-77(7)	CALL output
 83:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
 84:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
 85:    LDA  1,-10(1)	Ghost frame becomes new active frame 
 86:    LDA  3,1(7)	Return address in ac 
 87:    JMP  7,-54(7)	CALL outnl
 88:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
 89:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
 90:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -11
 91:     LD  4,-11(1)	Pop left into ac1 
 92:    SUB  3,4,3	compute location from index 
 93:     LD  3,0(3)	Load array element 
 94:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* TOFF inc: -11
 95:     LD  4,-11(1)	Pop index 
 96:    LDA  5,-3(1)	Load address of base of array x
 97:    SUB  5,5,4	Compute offset of value 
 98:     LD  4,0(5)	load lhs variable x
 99:     ST  3,0(5)	Store variable x
100:     ST  3,-11(1)	Push parameter 
* TOFF dec: -12
* Param end output
101:    LDA  1,-10(1)	Ghost frame becomes new active frame 
102:    LDA  3,1(7)	Return address in ac 
103:    JMP  7,-98(7)	CALL output
104:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
105:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
106:    LDA  1,-10(1)	Ghost frame becomes new active frame 
107:    LDA  3,1(7)	Return address in ac 
108:    JMP  7,-75(7)	CALL outnl
109:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* EXPRESSION
* CALL output
110:     ST  1,-10(1)	Store fp in ghost frame for output
* TOFF dec: -11
* TOFF dec: -12
* Param 1
111:    LDA  3,-3(1)	Load address of base of array x
112:     ST  3,-12(1)	Push left side 
* TOFF dec: -13
113:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -12
114:     LD  4,-12(1)	Pop left into ac1 
115:    SUB  3,4,3	compute location from index 
116:     LD  3,0(3)	Load array element 
117:     ST  3,-12(1)	Push parameter 
* TOFF dec: -13
* Param end output
118:    LDA  1,-10(1)	Ghost frame becomes new active frame 
119:    LDA  3,1(7)	Return address in ac 
120:    JMP  7,-115(7)	CALL output
121:    LDA  3,0(2)	Save the result in ac 
* Call end output
* TOFF set: -10
* EXPRESSION
* CALL outnl
122:     ST  1,-10(1)	Store fp in ghost frame for outnl
* TOFF dec: -11
* TOFF dec: -12
* Param end outnl
123:    LDA  1,-10(1)	Ghost frame becomes new active frame 
124:    LDA  3,1(7)	Return address in ac 
125:    JMP  7,-92(7)	CALL outnl
126:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -10
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
127:    LDC  2,0(6)	Set return value to 0 
128:     LD  3,-1(1)	Load return address 
129:     LD  1,0(1)	Adjust fp 
130:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,130(7)	Jump to init [backpatch] 
* INIT
131:    LDA  1,0(0)	set first frame at end of globals 
132:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
133:    LDA  3,1(7)	Return address in ac 
134:    JMP  7,-96(7)	Jump to main 
135:   HALT  0,0,0	DONE! 
* END INIT
