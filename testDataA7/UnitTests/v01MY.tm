* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/v01.c-
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
* TOFF set: -17
 40:    LDC  3,4(6)	load size of array a
 41:     ST  3,-2(1)	save size of array a
 42:    LDC  3,4(6)	load size of array b
 43:     ST  3,-7(1)	save size of array b
 44:    LDC  3,4(6)	load size of array c
 45:     ST  3,-12(1)	save size of array c
* Compound Body
* EXPRESSION
* CALL outputc
 46:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 47:    LDA  3,-3(1)	Load address of base of array a
 48:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
 49:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -19
 50:     LD  4,-19(1)	Pop left into ac1 
 51:    SUB  3,4,3	compute location from index 
 52:     LD  3,0(3)	Load array element 
 53:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
 54:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 55:    LDA  3,1(7)	Return address in ac 
 56:    JMP  7,-29(7)	CALL outputc
 57:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
 58:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 59:    LDA  3,-3(1)	Load address of base of array a
 60:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
 61:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -19
 62:     LD  4,-19(1)	Pop left into ac1 
 63:    SUB  3,4,3	compute location from index 
 64:     LD  3,0(3)	Load array element 
 65:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
 66:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 67:    LDA  3,1(7)	Return address in ac 
 68:    JMP  7,-41(7)	CALL outputc
 69:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
 70:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 71:    LDA  3,-3(1)	Load address of base of array a
 72:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
 73:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -19
 74:     LD  4,-19(1)	Pop left into ac1 
 75:    SUB  3,4,3	compute location from index 
 76:     LD  3,0(3)	Load array element 
 77:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
 78:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 79:    LDA  3,1(7)	Return address in ac 
 80:    JMP  7,-53(7)	CALL outputc
 81:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
 82:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 83:    LDA  3,-3(1)	Load address of base of array a
 84:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
 85:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -19
 86:     LD  4,-19(1)	Pop left into ac1 
 87:    SUB  3,4,3	compute location from index 
 88:     LD  3,0(3)	Load array element 
 89:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
 90:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 91:    LDA  3,1(7)	Return address in ac 
 92:    JMP  7,-65(7)	CALL outputc
 93:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
 94:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
 95:    LDC  3,32(6)	Load char constant 
 96:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
 97:    LDA  1,-17(1)	Ghost frame becomes new active frame 
 98:    LDA  3,1(7)	Return address in ac 
 99:    JMP  7,-72(7)	CALL outputc
100:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
101:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
102:    LDA  3,-8(1)	Load address of base of array b
103:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
104:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -19
105:     LD  4,-19(1)	Pop left into ac1 
106:    SUB  3,4,3	compute location from index 
107:     LD  3,0(3)	Load array element 
108:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
109:    LDA  1,-17(1)	Ghost frame becomes new active frame 
110:    LDA  3,1(7)	Return address in ac 
111:    JMP  7,-84(7)	CALL outputc
112:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
113:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
114:    LDA  3,-8(1)	Load address of base of array b
115:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
116:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -19
117:     LD  4,-19(1)	Pop left into ac1 
118:    SUB  3,4,3	compute location from index 
119:     LD  3,0(3)	Load array element 
120:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
121:    LDA  1,-17(1)	Ghost frame becomes new active frame 
122:    LDA  3,1(7)	Return address in ac 
123:    JMP  7,-96(7)	CALL outputc
124:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
125:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
126:    LDA  3,-8(1)	Load address of base of array b
127:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
128:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -19
129:     LD  4,-19(1)	Pop left into ac1 
130:    SUB  3,4,3	compute location from index 
131:     LD  3,0(3)	Load array element 
132:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
133:    LDA  1,-17(1)	Ghost frame becomes new active frame 
134:    LDA  3,1(7)	Return address in ac 
135:    JMP  7,-108(7)	CALL outputc
136:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
137:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
138:    LDA  3,-8(1)	Load address of base of array b
139:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
140:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -19
141:     LD  4,-19(1)	Pop left into ac1 
142:    SUB  3,4,3	compute location from index 
143:     LD  3,0(3)	Load array element 
144:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
145:    LDA  1,-17(1)	Ghost frame becomes new active frame 
146:    LDA  3,1(7)	Return address in ac 
147:    JMP  7,-120(7)	CALL outputc
148:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outnl
149:     ST  1,-17(1)	Store fp in ghost frame for outnl
* TOFF dec: -18
* TOFF dec: -19
* Param end outnl
150:    LDA  1,-17(1)	Ghost frame becomes new active frame 
151:    LDA  3,1(7)	Return address in ac 
152:    JMP  7,-119(7)	CALL outnl
153:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -17
* EXPRESSION
154:    LDA  3,-3(1)	Load address of base of array a
155:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
156:     LD  4,-17(1)	Pop index 
157:    LDA  5,-13(1)	Load address of base of array c
158:    SUB  5,5,4	Compute offset of value 
159:     ST  3,0(5)	Store variable c
* EXPRESSION
160:    LDA  3,-8(1)	Load address of base of array b
161:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
162:     LD  4,-17(1)	Pop index 
163:    LDA  5,-3(1)	Load address of base of array a
164:    SUB  5,5,4	Compute offset of value 
165:     ST  3,0(5)	Store variable a
* EXPRESSION
166:    LDA  3,-13(1)	Load address of base of array c
167:     ST  3,-17(1)	Push left side 
* TOFF dec: -18
* TOFF inc: -17
168:     LD  4,-17(1)	Pop index 
169:    LDA  5,-8(1)	Load address of base of array b
170:    SUB  5,5,4	Compute offset of value 
171:     ST  3,0(5)	Store variable b
* EXPRESSION
* CALL outputc
172:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
173:    LDA  3,-3(1)	Load address of base of array a
174:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
175:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -19
176:     LD  4,-19(1)	Pop left into ac1 
177:    SUB  3,4,3	compute location from index 
178:     LD  3,0(3)	Load array element 
179:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
180:    LDA  1,-17(1)	Ghost frame becomes new active frame 
181:    LDA  3,1(7)	Return address in ac 
182:    JMP  7,-155(7)	CALL outputc
183:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
184:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
185:    LDA  3,-3(1)	Load address of base of array a
186:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
187:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -19
188:     LD  4,-19(1)	Pop left into ac1 
189:    SUB  3,4,3	compute location from index 
190:     LD  3,0(3)	Load array element 
191:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
192:    LDA  1,-17(1)	Ghost frame becomes new active frame 
193:    LDA  3,1(7)	Return address in ac 
194:    JMP  7,-167(7)	CALL outputc
195:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
196:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
197:    LDA  3,-3(1)	Load address of base of array a
198:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
199:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -19
200:     LD  4,-19(1)	Pop left into ac1 
201:    SUB  3,4,3	compute location from index 
202:     LD  3,0(3)	Load array element 
203:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
204:    LDA  1,-17(1)	Ghost frame becomes new active frame 
205:    LDA  3,1(7)	Return address in ac 
206:    JMP  7,-179(7)	CALL outputc
207:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
208:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
209:    LDA  3,-3(1)	Load address of base of array a
210:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
211:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -19
212:     LD  4,-19(1)	Pop left into ac1 
213:    SUB  3,4,3	compute location from index 
214:     LD  3,0(3)	Load array element 
215:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
216:    LDA  1,-17(1)	Ghost frame becomes new active frame 
217:    LDA  3,1(7)	Return address in ac 
218:    JMP  7,-191(7)	CALL outputc
219:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
220:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
221:    LDC  3,32(6)	Load char constant 
222:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
223:    LDA  1,-17(1)	Ghost frame becomes new active frame 
224:    LDA  3,1(7)	Return address in ac 
225:    JMP  7,-198(7)	CALL outputc
226:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
227:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
228:    LDA  3,-8(1)	Load address of base of array b
229:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
230:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -19
231:     LD  4,-19(1)	Pop left into ac1 
232:    SUB  3,4,3	compute location from index 
233:     LD  3,0(3)	Load array element 
234:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
235:    LDA  1,-17(1)	Ghost frame becomes new active frame 
236:    LDA  3,1(7)	Return address in ac 
237:    JMP  7,-210(7)	CALL outputc
238:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
239:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
240:    LDA  3,-8(1)	Load address of base of array b
241:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
242:    LDC  3,1(6)	Load integer constant 
* TOFF inc: -19
243:     LD  4,-19(1)	Pop left into ac1 
244:    SUB  3,4,3	compute location from index 
245:     LD  3,0(3)	Load array element 
246:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
247:    LDA  1,-17(1)	Ghost frame becomes new active frame 
248:    LDA  3,1(7)	Return address in ac 
249:    JMP  7,-222(7)	CALL outputc
250:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
251:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
252:    LDA  3,-8(1)	Load address of base of array b
253:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
254:    LDC  3,2(6)	Load integer constant 
* TOFF inc: -19
255:     LD  4,-19(1)	Pop left into ac1 
256:    SUB  3,4,3	compute location from index 
257:     LD  3,0(3)	Load array element 
258:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
259:    LDA  1,-17(1)	Ghost frame becomes new active frame 
260:    LDA  3,1(7)	Return address in ac 
261:    JMP  7,-234(7)	CALL outputc
262:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outputc
263:     ST  1,-17(1)	Store fp in ghost frame for outputc
* TOFF dec: -18
* TOFF dec: -19
* Param 1
264:    LDA  3,-8(1)	Load address of base of array b
265:     ST  3,-19(1)	Push left side 
* TOFF dec: -20
266:    LDC  3,3(6)	Load integer constant 
* TOFF inc: -19
267:     LD  4,-19(1)	Pop left into ac1 
268:    SUB  3,4,3	compute location from index 
269:     LD  3,0(3)	Load array element 
270:     ST  3,-19(1)	Push parameter 
* TOFF dec: -20
* Param end outputc
271:    LDA  1,-17(1)	Ghost frame becomes new active frame 
272:    LDA  3,1(7)	Return address in ac 
273:    JMP  7,-246(7)	CALL outputc
274:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* TOFF set: -17
* EXPRESSION
* CALL outnl
275:     ST  1,-17(1)	Store fp in ghost frame for outnl
* TOFF dec: -18
* TOFF dec: -19
* Param end outnl
276:    LDA  1,-17(1)	Ghost frame becomes new active frame 
277:    LDA  3,1(7)	Return address in ac 
278:    JMP  7,-245(7)	CALL outnl
279:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -17
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
280:    LDC  2,0(6)	Set return value to 0 
281:     LD  3,-1(1)	Load return address 
282:     LD  1,0(1)	Adjust fp 
283:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,283(7)	Jump to init [backpatch] 
* INIT
284:    LDA  1,-10(0)	set first frame at end of globals 
285:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
  1:    LIT  "acid"
286:    LDA  3,-1(0)	Load address of char array 
287:     ST  3,-3(1)	Store variable a
  6:    LIT  "zulu"
288:    LDA  3,-6(0)	Load address of char array 
289:     ST  3,-8(1)	Store variable b
* END INIT GLOBALS AND STATICS
290:    LDA  3,1(7)	Return address in ac 
291:    JMP  7,-253(7)	Jump to main 
292:   HALT  0,0,0	DONE! 
* END INIT
