* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/v02.c-
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
* CALL outputb
 44:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 45:    LDA  3,-3(1)	Load address of base of array a
 46:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 47:    LDA  3,-9(1)	Load address of base of array b
 48:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
 49:     LD  4,-17(1)	Pop left into ac1 
 50:    TEQ  3,4,3	Op = 
 51:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
 52:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 53:    LDA  3,1(7)	Return address in ac 
 54:    JMP  7,-38(7)	CALL outputb
 55:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
 56:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 57:    LDA  3,-9(1)	Load address of base of array b
 58:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 59:    LDA  3,-3(1)	Load address of base of array a
 60:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
 61:     LD  4,-17(1)	Pop left into ac1 
 62:    TEQ  3,4,3	Op = 
 63:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
 64:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 65:    LDA  3,1(7)	Return address in ac 
 66:    JMP  7,-50(7)	CALL outputb
 67:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
 68:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
 69:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 70:    LDA  3,1(7)	Return address in ac 
 71:    JMP  7,-38(7)	CALL outnl
 72:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
* CALL outputb
 73:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 74:    LDA  3,-3(1)	Load address of base of array a
 75:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 76:    LDA  3,-9(1)	Load address of base of array b
 77:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
 78:     LD  4,-17(1)	Pop left into ac1 
 79:    TNE  3,4,3	Op >< 
 80:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
 81:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 82:    LDA  3,1(7)	Return address in ac 
 83:    JMP  7,-67(7)	CALL outputb
 84:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
 85:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
 86:    LDA  3,-9(1)	Load address of base of array b
 87:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
 88:    LDA  3,-3(1)	Load address of base of array a
 89:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
 90:     LD  4,-17(1)	Pop left into ac1 
 91:    TNE  3,4,3	Op >< 
 92:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
 93:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 94:    LDA  3,1(7)	Return address in ac 
 95:    JMP  7,-79(7)	CALL outputb
 96:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
 97:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
 98:    LDA  1,-14(1)	Ghost frame becomes new active frame 
 99:    LDA  3,1(7)	Return address in ac 
100:    JMP  7,-67(7)	CALL outnl
101:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
* CALL outputb
102:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
103:    LDA  3,-3(1)	Load address of base of array a
104:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
105:    LDA  3,-9(1)	Load address of base of array b
106:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
107:     LD  4,-17(1)	Pop left into ac1 
108:    TGT  3,4,3	Op > 
109:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
110:    LDA  1,-14(1)	Ghost frame becomes new active frame 
111:    LDA  3,1(7)	Return address in ac 
112:    JMP  7,-96(7)	CALL outputb
113:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
114:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
115:    LDA  3,-9(1)	Load address of base of array b
116:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
117:    LDA  3,-3(1)	Load address of base of array a
118:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
119:     LD  4,-17(1)	Pop left into ac1 
120:    TGT  3,4,3	Op > 
121:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
122:    LDA  1,-14(1)	Ghost frame becomes new active frame 
123:    LDA  3,1(7)	Return address in ac 
124:    JMP  7,-108(7)	CALL outputb
125:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
126:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
127:    LDA  1,-14(1)	Ghost frame becomes new active frame 
128:    LDA  3,1(7)	Return address in ac 
129:    JMP  7,-96(7)	CALL outnl
130:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
* CALL outputb
131:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
132:    LDA  3,-3(1)	Load address of base of array a
133:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
134:    LDA  3,-9(1)	Load address of base of array b
135:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
136:     LD  4,-17(1)	Pop left into ac1 
137:    TGE  3,4,3	Op >= 
138:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
139:    LDA  1,-14(1)	Ghost frame becomes new active frame 
140:    LDA  3,1(7)	Return address in ac 
141:    JMP  7,-125(7)	CALL outputb
142:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
143:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
144:    LDA  3,-9(1)	Load address of base of array b
145:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
146:    LDA  3,-3(1)	Load address of base of array a
147:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
148:     LD  4,-17(1)	Pop left into ac1 
149:    TGE  3,4,3	Op >= 
150:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
151:    LDA  1,-14(1)	Ghost frame becomes new active frame 
152:    LDA  3,1(7)	Return address in ac 
153:    JMP  7,-137(7)	CALL outputb
154:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
155:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
156:    LDA  1,-14(1)	Ghost frame becomes new active frame 
157:    LDA  3,1(7)	Return address in ac 
158:    JMP  7,-125(7)	CALL outnl
159:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
* CALL outputb
160:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
161:    LDA  3,-3(1)	Load address of base of array a
162:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
163:    LDA  3,-9(1)	Load address of base of array b
164:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
165:     LD  4,-17(1)	Pop left into ac1 
166:    TLT  3,4,3	Op < 
167:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
168:    LDA  1,-14(1)	Ghost frame becomes new active frame 
169:    LDA  3,1(7)	Return address in ac 
170:    JMP  7,-154(7)	CALL outputb
171:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
172:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
173:    LDA  3,-9(1)	Load address of base of array b
174:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
175:    LDA  3,-3(1)	Load address of base of array a
176:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
177:     LD  4,-17(1)	Pop left into ac1 
178:    TLT  3,4,3	Op < 
179:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
180:    LDA  1,-14(1)	Ghost frame becomes new active frame 
181:    LDA  3,1(7)	Return address in ac 
182:    JMP  7,-166(7)	CALL outputb
183:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
184:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
185:    LDA  1,-14(1)	Ghost frame becomes new active frame 
186:    LDA  3,1(7)	Return address in ac 
187:    JMP  7,-154(7)	CALL outnl
188:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* EXPRESSION
* CALL outputb
189:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
190:    LDA  3,-3(1)	Load address of base of array a
191:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
192:    LDA  3,-9(1)	Load address of base of array b
193:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
194:     LD  4,-17(1)	Pop left into ac1 
195:    TLE  3,4,3	Op <= 
196:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
197:    LDA  1,-14(1)	Ghost frame becomes new active frame 
198:    LDA  3,1(7)	Return address in ac 
199:    JMP  7,-183(7)	CALL outputb
200:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outputb
201:     ST  1,-14(1)	Store fp in ghost frame for outputb
* TOFF dec: -15
* TOFF dec: -16
* Param 1
202:    LDA  3,-9(1)	Load address of base of array b
203:     ST  3,-16(1)	Push left side 
* TOFF dec: -17
204:    LDA  3,-3(1)	Load address of base of array a
205:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
206:     LD  4,-17(1)	Pop left into ac1 
207:    TLE  3,4,3	Op <= 
208:     ST  3,-17(1)	Push parameter 
* TOFF dec: -18
* Param end outputb
209:    LDA  1,-14(1)	Ghost frame becomes new active frame 
210:    LDA  3,1(7)	Return address in ac 
211:    JMP  7,-195(7)	CALL outputb
212:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -14
* EXPRESSION
* CALL outnl
213:     ST  1,-14(1)	Store fp in ghost frame for outnl
* TOFF dec: -15
* TOFF dec: -16
* Param end outnl
214:    LDA  1,-14(1)	Ghost frame becomes new active frame 
215:    LDA  3,1(7)	Return address in ac 
216:    JMP  7,-183(7)	CALL outnl
217:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -14
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
218:    LDC  2,0(6)	Set return value to 0 
219:     LD  3,-1(1)	Load return address 
220:     LD  1,0(1)	Adjust fp 
221:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,221(7)	Jump to init [backpatch] 
* INIT
222:    LDA  1,-10(0)	set first frame at end of globals 
223:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
  1:    LIT  "acid"
224:    LDA  3,-1(0)	Load address of char array 
225:     ST  3,-3(1)	Store variable a
  6:    LIT  "army"
226:    LDA  3,-6(0)	Load address of char array 
227:     ST  3,-9(1)	Store variable b
* END INIT GLOBALS AND STATICS
228:    LDA  3,1(7)	Return address in ac 
229:    JMP  7,-191(7)	Jump to main 
230:   HALT  0,0,0	DONE! 
* END INIT
