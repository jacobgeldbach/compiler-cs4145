* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/v00.c-
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
* TOFF set: -14
 40:    LDC  3,5(6)	load size of array a
 41:     ST  3,-2(1)	save size of array a
 42:    LDC  3,5(6)	load size of array b
 43:     ST  3,-8(1)	save size of array b
* Compound Body
* EXPRESSION
* CALL outputc
 44:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 45:    LDA  3,-3(1)	Load address of base of array a
 46:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 47:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -16
 48:     LD  4,-16(1)	Pop left into ac1 
 49:    SUB  3,4,3	compute location from index 
 50:     LD  3,0(3)	Load array element 
 51:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
 52:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 53:    LDA  3,1(7)	Return address in ac 
 54:    JMP  7,-27(7)	CALL outputc
 55:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
 56:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 57:    LDA  3,-3(1)	Load address of base of array a
 58:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 59:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -16
 60:     LD  4,-16(1)	Pop left into ac1 
 61:    SUB  3,4,3	compute location from index 
 62:     LD  3,0(3)	Load array element 
 63:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
 64:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 65:    LDA  3,1(7)	Return address in ac 
 66:    JMP  7,-39(7)	CALL outputc
 67:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
 68:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 69:    LDA  3,-3(1)	Load address of base of array a
 70:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 71:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -16
 72:     LD  4,-16(1)	Pop left into ac1 
 73:    SUB  3,4,3	compute location from index 
 74:     LD  3,0(3)	Load array element 
 75:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
 76:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 77:    LDA  3,1(7)	Return address in ac 
 78:    JMP  7,-51(7)	CALL outputc
 79:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
 80:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 81:    LDA  3,-3(1)	Load address of base of array a
 82:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 83:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -16
 84:     LD  4,-16(1)	Pop left into ac1 
 85:    SUB  3,4,3	compute location from index 
 86:     LD  3,0(3)	Load array element 
 87:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
 88:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 89:    LDA  3,1(7)	Return address in ac 
 90:    JMP  7,-63(7)	CALL outputc
 91:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outnl
 92:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
 93:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 94:    LDA  3,1(7)	Return address in ac 
 95:    JMP  7,-62(7)	CALL outnl
 96:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
 97:    LDA  3,-3(1)	Load address of base of array a
 98:     ST  3,-14(1)	Push left side 
* TOFF dec: -15
* TOFF inc: -14
 99:     LD  4,-14(1)	Pop index 
100:    LDA  5,-9(1)	Load address of base of array b
101:    SUB  5,5,4	Compute offset of value 
102:     ST  3,0(5)	Store variable b
* EXPRESSION
* CALL outputc
103:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
104:    LDA  3,-9(1)	Load address of base of array b
105:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
106:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -16
107:     LD  4,-16(1)	Pop left into ac1 
108:    SUB  3,4,3	compute location from index 
109:     LD  3,0(3)	Load array element 
110:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
111:    LDA  1,-14(1)	Ghost frame becomes new active frame 
112:    LDA  3,1(7)	Return address in ac 
113:    JMP  7,-86(7)	CALL outputc
114:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
115:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
116:    LDA  3,-9(1)	Load address of base of array b
117:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
118:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -16
119:     LD  4,-16(1)	Pop left into ac1 
120:    SUB  3,4,3	compute location from index 
121:     LD  3,0(3)	Load array element 
122:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
123:    LDA  1,-14(1)	Ghost frame becomes new active frame 
124:    LDA  3,1(7)	Return address in ac 
125:    JMP  7,-98(7)	CALL outputc
126:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
127:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
128:    LDA  3,-9(1)	Load address of base of array b
129:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
130:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -16
131:     LD  4,-16(1)	Pop left into ac1 
132:    SUB  3,4,3	compute location from index 
133:     LD  3,0(3)	Load array element 
134:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
135:    LDA  1,-14(1)	Ghost frame becomes new active frame 
136:    LDA  3,1(7)	Return address in ac 
137:    JMP  7,-110(7)	CALL outputc
138:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outputc
139:     ST  1,-14(1)	Store fp in ghost frame for outputc
* TOFF dec: -15
* TOFF dec: -16
* Param 1
140:    LDA  3,-9(1)	Load address of base of array b
141:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
142:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -16
143:     LD  4,-16(1)	Pop left into ac1 
144:    SUB  3,4,3	compute location from index 
145:     LD  3,0(3)	Load array element 
146:     ST  3,-16(1)	Push parameter 
* TOFF dec: -17
* Param end outputc
147:    LDA  1,-14(1)	Ghost frame becomes new active frame 
148:    LDA  3,1(7)	Return address in ac 
149:    JMP  7,-122(7)	CALL outputc
150:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -14
* EXPRESSION
* CALL outnl
151:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
152:    LDA  1,-14(1)	Ghost frame becomes new active frame 
153:    LDA  3,1(7)	Return address in ac 
154:    JMP  7,-121(7)	CALL outnl
155:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
156:    LDC  2,0(6)	Set return value to 0 
157:     LD  3,-1(1)	Load return address 
158:     LD  1,0(1)	Adjust fp 
159:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,159(7)	Jump to init [backpatch] 
* INIT
160:    LDA  1,-5(0)	set first frame at end of globals 
161:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
  1:    LIT  "acid"
162:    LDA  3,-1(0)	Load address of char array 
163:     ST  3,-3(1)	Store variable a
* END INIT GLOBALS AND STATICS
164:    LDA  3,1(7)	Return address in ac 
165:    JMP  7,-127(7)	Jump to main 
166:   HALT  0,0,0	DONE! 
* END INIT
