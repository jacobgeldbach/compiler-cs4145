* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/v05.c-
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
* FUNCTION outputs
* TOFF set: -3
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -4
* Compound Body
* EXPRESSION
 40:    LDC  3,0(6)	Load integer constant 
 41:     ST  3,-3(1)	Store variable i
* WHILE
 42:     LD  3,-3(1)	Load variable i
 43:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 44:     LD  3,-2(1)	Load address of base of array s
 45:     LD  3,1(3)	Load array size 
* TOFF inc: -4
 46:     LD  4,-4(1)	Pop left into ac1 
 47:    TLT  3,4,3	Op < 
 48:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* TOFF set: -4
* IF
 50:     LD  3,-2(1)	Load address of base of array s
 51:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 52:     LD  3,-3(1)	Load variable i
* TOFF inc: -4
 53:     LD  4,-4(1)	Pop left into ac1 
 54:    SUB  3,4,3	compute location from index 
 55:     LD  3,0(3)	Load array element 
 56:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
 57:    LDC  3,0(6)	Load char constant 
* TOFF inc: -4
 58:     LD  4,-4(1)	Pop left into ac1 
 59:    TEQ  3,4,3	Op = 
* THEN
* BREAK
 61:    JMP  7,-13(7)	break 
 60:    JZR  3,1(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
* CALL outputc
 62:     ST  1,-4(1)	Store fp in ghost frame for outputc
* TOFF dec: -5
* TOFF dec: -6
* Param 1
 63:     LD  3,-2(1)	Load address of base of array s
 64:     ST  3,-6(1)	Push left side 
* TOFF dec: -7
 65:     LD  3,-3(1)	Load variable i
* TOFF inc: -6
 66:     LD  4,-6(1)	Pop left into ac1 
 67:    SUB  3,4,3	compute location from index 
 68:     LD  3,0(3)	Load array element 
 69:     ST  3,-6(1)	Push parameter 
* TOFF dec: -7
* Param end outputc
 70:    LDA  1,-4(1)	Ghost frame becomes new active frame 
 71:    LDA  3,1(7)	Return address in ac 
 72:    JMP  7,-45(7)	CALL outputc
 73:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -4
* EXPRESSION
 74:     LD  3,-3(1)	load lhs variable i
 75:    LDA  3,1(3)	increment value of i
 76:     ST  3,-3(1)	Store variable i
* TOFF set: -4
* END COMPOUND
 77:    JMP  7,-36(7)	go to beginning of loop 
 49:    JMP  7,28(7)	Jump past loop [backpatch] 
* END WHILE
* TOFF set: -3
* END COMPOUND
* Add standard closing in case there is no return statement
 78:    LDC  2,0(6)	Set return value to 0 
 79:     LD  3,-1(1)	Load return address 
 80:     LD  1,0(1)	Adjust fp 
 81:    JMP  7,0(3)	Return 
* END FUNCTION outputs
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 82:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -39
  1:    LIT  "armadillo
 83:    LDA  3,-1(0)	Load address of char array 
 84:     ST  3,-3(1)	Store variable a
 85:    LDC  3,10(6)	load size of array a
 86:     ST  3,-2(1)	save size of array a
 10:    LIT  "bat
 87:    LDA  3,-10(0)	Load address of char array 
 88:     ST  3,-14(1)	Store variable b
 89:    LDC  3,4(6)	load size of array b
 90:     ST  3,-13(1)	save size of array b
 13:    LIT  "horse
 91:    LDA  3,-13(0)	Load address of char array 
 92:     ST  3,-19(1)	Store variable h
 93:    LDC  3,6(6)	load size of array h
 94:     ST  3,-18(1)	save size of array h
 95:    LDC  3,10(6)	load size of array big
 96:     ST  3,-25(1)	save size of array big
 97:    LDC  3,2(6)	load size of array small
 98:     ST  3,-36(1)	save size of array small
* Compound Body
* EXPRESSION
 99:    LDA  3,-3(1)	Load address of base of array a
100:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
101:     LD  4,-39(1)	Pop index 
102:    LDA  5,-37(1)	Load address of base of array small
103:    SUB  5,5,4	Compute offset of value 
104:     ST  3,0(5)	Store variable small
* EXPRESSION
* CALL outputs
105:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
106:    LDA  3,-37(1)	Load address of base of array small
107:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
108:    LDA  1,-39(1)	Ghost frame becomes new active frame 
109:    LDA  3,1(7)	Return address in ac 
110:    JMP  7,-72(7)	CALL outputs
111:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
112:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
113:    LDA  1,-39(1)	Ghost frame becomes new active frame 
114:    LDA  3,1(7)	Return address in ac 
115:    JMP  7,-82(7)	CALL outnl
116:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
117:    LDA  3,-3(1)	Load address of base of array a
118:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
119:     LD  4,-39(1)	Pop index 
120:    LDA  5,-26(1)	Load address of base of array big
121:    SUB  5,5,4	Compute offset of value 
122:     ST  3,0(5)	Store variable big
* EXPRESSION
* CALL outputs
123:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
124:    LDA  3,-26(1)	Load address of base of array big
125:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
126:    LDA  1,-39(1)	Ghost frame becomes new active frame 
127:    LDA  3,1(7)	Return address in ac 
128:    JMP  7,-90(7)	CALL outputs
129:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
130:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
131:    LDA  1,-39(1)	Ghost frame becomes new active frame 
132:    LDA  3,1(7)	Return address in ac 
133:    JMP  7,-100(7)	CALL outnl
134:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
* CALL outnl
135:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
136:    LDA  1,-39(1)	Ghost frame becomes new active frame 
137:    LDA  3,1(7)	Return address in ac 
138:    JMP  7,-105(7)	CALL outnl
139:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
140:    LDA  3,-14(1)	Load address of base of array b
141:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
142:     LD  4,-39(1)	Pop index 
143:    LDA  5,-37(1)	Load address of base of array small
144:    SUB  5,5,4	Compute offset of value 
145:     ST  3,0(5)	Store variable small
* EXPRESSION
* CALL outputs
146:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
147:    LDA  3,-37(1)	Load address of base of array small
148:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
149:    LDA  1,-39(1)	Ghost frame becomes new active frame 
150:    LDA  3,1(7)	Return address in ac 
151:    JMP  7,-113(7)	CALL outputs
152:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
153:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
154:    LDA  1,-39(1)	Ghost frame becomes new active frame 
155:    LDA  3,1(7)	Return address in ac 
156:    JMP  7,-123(7)	CALL outnl
157:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
158:    LDA  3,-14(1)	Load address of base of array b
159:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
160:     LD  4,-39(1)	Pop index 
161:    LDA  5,-26(1)	Load address of base of array big
162:    SUB  5,5,4	Compute offset of value 
163:     ST  3,0(5)	Store variable big
* EXPRESSION
* CALL outputs
164:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
165:    LDA  3,-26(1)	Load address of base of array big
166:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
167:    LDA  1,-39(1)	Ghost frame becomes new active frame 
168:    LDA  3,1(7)	Return address in ac 
169:    JMP  7,-131(7)	CALL outputs
170:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
171:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
172:    LDA  1,-39(1)	Ghost frame becomes new active frame 
173:    LDA  3,1(7)	Return address in ac 
174:    JMP  7,-141(7)	CALL outnl
175:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
* CALL outnl
176:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
177:    LDA  1,-39(1)	Ghost frame becomes new active frame 
178:    LDA  3,1(7)	Return address in ac 
179:    JMP  7,-146(7)	CALL outnl
180:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
181:    LDA  3,-19(1)	Load address of base of array h
182:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
183:     LD  4,-39(1)	Pop index 
184:    LDA  5,-37(1)	Load address of base of array small
185:    SUB  5,5,4	Compute offset of value 
186:     ST  3,0(5)	Store variable small
* EXPRESSION
* CALL outputs
187:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
188:    LDA  3,-37(1)	Load address of base of array small
189:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
190:    LDA  1,-39(1)	Ghost frame becomes new active frame 
191:    LDA  3,1(7)	Return address in ac 
192:    JMP  7,-154(7)	CALL outputs
193:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
194:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
195:    LDA  1,-39(1)	Ghost frame becomes new active frame 
196:    LDA  3,1(7)	Return address in ac 
197:    JMP  7,-164(7)	CALL outnl
198:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
199:    LDA  3,-19(1)	Load address of base of array h
200:     ST  3,-39(1)	Push left side 
* TOFF dec: -40
* TOFF inc: -39
201:     LD  4,-39(1)	Pop index 
202:    LDA  5,-26(1)	Load address of base of array big
203:    SUB  5,5,4	Compute offset of value 
204:     ST  3,0(5)	Store variable big
* EXPRESSION
* CALL outputs
205:     ST  1,-39(1)	Store fp in ghost frame for outputs
* TOFF dec: -40
* TOFF dec: -41
* Param 1
206:    LDA  3,-26(1)	Load address of base of array big
207:     ST  3,-41(1)	Push left side 
* TOFF dec: -42
* Param end outputs
208:    LDA  1,-39(1)	Ghost frame becomes new active frame 
209:    LDA  3,1(7)	Return address in ac 
210:    JMP  7,-172(7)	CALL outputs
211:    LDA  3,0(2)	Save the result in ac 
* Call end outputs
* TOFF set: -39
* EXPRESSION
* CALL outnl
212:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
213:    LDA  1,-39(1)	Ghost frame becomes new active frame 
214:    LDA  3,1(7)	Return address in ac 
215:    JMP  7,-182(7)	CALL outnl
216:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* EXPRESSION
* CALL outnl
217:     ST  1,-39(1)	Store fp in ghost frame for outnl
* TOFF dec: -40
* TOFF dec: -41
* Param end outnl
218:    LDA  1,-39(1)	Ghost frame becomes new active frame 
219:    LDA  3,1(7)	Return address in ac 
220:    JMP  7,-187(7)	CALL outnl
221:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -39
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
222:    LDC  2,0(6)	Set return value to 0 
223:     LD  3,-1(1)	Load return address 
224:     LD  1,0(1)	Adjust fp 
225:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,225(7)	Jump to init [backpatch] 
* INIT
226:    LDA  1,-17(0)	set first frame at end of globals 
227:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
228:    LDA  3,1(7)	Return address in ac 
229:    JMP  7,-148(7)	Jump to main 
230:   HALT  0,0,0	DONE! 
* END INIT
