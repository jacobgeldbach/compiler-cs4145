* C- compiler version C-F23
* File compiled:  ../testDataA7/UnitTests/b0c.c-
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
* CALL outputb
 40:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
 41:    LDC  3,1(6)	Load integer constant 
 42:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
 43:     LD  4,-3(1)	Pop left into ac1 
 44:    TEQ  3,4,3	Op = 
 45:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* Param end outputb
 46:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 47:    LDA  3,1(7)	Return address in ac 
 48:    JMP  7,-32(7)	CALL outputb
 49:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outnl
 50:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
 51:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 52:    LDA  3,1(7)	Return address in ac 
 53:    JMP  7,-20(7)	CALL outnl
 54:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* EXPRESSION
* CALL outputb
 55:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
 56:    LDC  3,100000(6)	Load integer constant 
 57:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
 58:     LD  4,-3(1)	Pop left into ac1 
 59:    TGT  3,4,3	Op > 
 60:     ST  3,-3(1)	Push parameter 
* TOFF dec: -4
* Param end outputb
 61:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 62:    LDA  3,1(7)	Return address in ac 
 63:    JMP  7,-47(7)	CALL outputb
 64:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outputb
 65:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
 66:    LDC  3,3(6)	Load integer constant 
 67:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
 68:     LD  4,-3(1)	Pop left into ac1 
 69:    TGT  3,4,3	Op > 
 70:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
 71:    LDC  3,3(6)	Load integer constant 
 72:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
 73:     LD  4,-3(1)	Pop left into ac1 
 74:    TGT  3,4,3	Op > 
* TOFF inc: -2
 75:     LD  4,-2(1)	Pop left into ac1 
 76:    AND  3,4,3	Op AND 
 77:     ST  3,-2(1)	Push left side 
* TOFF dec: -3
 78:    LDC  3,3(6)	Load integer constant 
 79:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -2
 80:     LD  4,-2(1)	Pop left into ac1 
 81:    TGT  3,4,3	Op > 
* TOFF inc: -1
 82:     LD  4,-1(1)	Pop left into ac1 
 83:    AND  3,4,3	Op AND 
 84:     ST  3,-1(1)	Push left side 
* TOFF dec: -2
 85:    LDC  3,3(6)	Load integer constant 
 86:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -1
 87:     LD  4,-1(1)	Pop left into ac1 
 88:    TGT  3,4,3	Op > 
* TOFF inc: 0
 89:     LD  4,0(1)	Pop left into ac1 
 90:    AND  3,4,3	Op AND 
 91:     ST  3,0(1)	Push left side 
* TOFF dec: -1
 92:    LDC  3,3(6)	Load integer constant 
 93:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 0
 94:     LD  4,0(1)	Pop left into ac1 
 95:    TGT  3,4,3	Op > 
* TOFF inc: 1
 96:     LD  4,1(1)	Pop left into ac1 
 97:    AND  3,4,3	Op AND 
 98:     ST  3,1(1)	Push left side 
* TOFF dec: 0
 99:    LDC  3,3(6)	Load integer constant 
100:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 1
101:     LD  4,1(1)	Pop left into ac1 
102:    TGT  3,4,3	Op > 
* TOFF inc: 2
103:     LD  4,2(1)	Pop left into ac1 
104:    AND  3,4,3	Op AND 
105:     ST  3,2(1)	Push left side 
* TOFF dec: 1
106:    LDC  3,3(6)	Load integer constant 
107:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 2
108:     LD  4,2(1)	Pop left into ac1 
109:    TGT  3,4,3	Op > 
* TOFF inc: 3
110:     LD  4,3(1)	Pop left into ac1 
111:    AND  3,4,3	Op AND 
112:     ST  3,3(1)	Push left side 
* TOFF dec: 2
113:    LDC  3,3(6)	Load integer constant 
114:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 3
115:     LD  4,3(1)	Pop left into ac1 
116:    TGT  3,4,3	Op > 
* TOFF inc: 4
117:     LD  4,4(1)	Pop left into ac1 
118:    AND  3,4,3	Op AND 
119:     ST  3,4(1)	Push left side 
* TOFF dec: 3
120:    LDC  3,3(6)	Load integer constant 
121:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 4
122:     LD  4,4(1)	Pop left into ac1 
123:    TGT  3,4,3	Op > 
* TOFF inc: 5
124:     LD  4,5(1)	Pop left into ac1 
125:    AND  3,4,3	Op AND 
126:     ST  3,5(1)	Push left side 
* TOFF dec: 4
127:    LDC  3,3(6)	Load integer constant 
128:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 5
129:     LD  4,5(1)	Pop left into ac1 
130:    TGT  3,4,3	Op > 
* TOFF inc: 6
131:     LD  4,6(1)	Pop left into ac1 
132:    AND  3,4,3	Op AND 
133:     ST  3,6(1)	Push left side 
* TOFF dec: 5
134:    LDC  3,3(6)	Load integer constant 
135:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 6
136:     LD  4,6(1)	Pop left into ac1 
137:    TGT  3,4,3	Op > 
* TOFF inc: 7
138:     LD  4,7(1)	Pop left into ac1 
139:    AND  3,4,3	Op AND 
140:     ST  3,7(1)	Push left side 
* TOFF dec: 6
141:    LDC  3,3(6)	Load integer constant 
142:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 7
143:     LD  4,7(1)	Pop left into ac1 
144:    TGT  3,4,3	Op > 
* TOFF inc: 8
145:     LD  4,8(1)	Pop left into ac1 
146:    AND  3,4,3	Op AND 
147:     ST  3,8(1)	Push left side 
* TOFF dec: 7
148:    LDC  3,3(6)	Load integer constant 
149:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 8
150:     LD  4,8(1)	Pop left into ac1 
151:    TGT  3,4,3	Op > 
* TOFF inc: 9
152:     LD  4,9(1)	Pop left into ac1 
153:    AND  3,4,3	Op AND 
154:     ST  3,9(1)	Push parameter 
* TOFF dec: 8
* Param end outputb
155:    LDA  1,-2(1)	Ghost frame becomes new active frame 
156:    LDA  3,1(7)	Return address in ac 
157:    JMP  7,-141(7)	CALL outputb
158:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outputb
159:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
160:    LDC  3,3(6)	Load integer constant 
161:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
162:     LD  4,-3(1)	Pop left into ac1 
163:    TGT  3,4,3	Op > 
164:     ST  3,-3(1)	Push left side 
* TOFF dec: -4
165:    LDC  3,3(6)	Load integer constant 
166:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -3
167:     LD  4,-3(1)	Pop left into ac1 
168:    TGT  3,4,3	Op > 
* TOFF inc: -2
169:     LD  4,-2(1)	Pop left into ac1 
170:     OR  3,4,3	Op OR 
171:     ST  3,-2(1)	Push left side 
* TOFF dec: -3
172:    LDC  3,3(6)	Load integer constant 
173:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -2
174:     LD  4,-2(1)	Pop left into ac1 
175:    TGT  3,4,3	Op > 
* TOFF inc: -1
176:     LD  4,-1(1)	Pop left into ac1 
177:     OR  3,4,3	Op OR 
178:     ST  3,-1(1)	Push left side 
* TOFF dec: -2
179:    LDC  3,3(6)	Load integer constant 
180:    LDC  3,0(6)	Load integer constant 
* TOFF inc: -1
181:     LD  4,-1(1)	Pop left into ac1 
182:    TGT  3,4,3	Op > 
* TOFF inc: 0
183:     LD  4,0(1)	Pop left into ac1 
184:     OR  3,4,3	Op OR 
185:     ST  3,0(1)	Push left side 
* TOFF dec: -1
186:    LDC  3,3(6)	Load integer constant 
187:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 0
188:     LD  4,0(1)	Pop left into ac1 
189:    TGT  3,4,3	Op > 
* TOFF inc: 1
190:     LD  4,1(1)	Pop left into ac1 
191:     OR  3,4,3	Op OR 
192:     ST  3,1(1)	Push left side 
* TOFF dec: 0
193:    LDC  3,3(6)	Load integer constant 
194:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 1
195:     LD  4,1(1)	Pop left into ac1 
196:    TGT  3,4,3	Op > 
* TOFF inc: 2
197:     LD  4,2(1)	Pop left into ac1 
198:     OR  3,4,3	Op OR 
199:     ST  3,2(1)	Push left side 
* TOFF dec: 1
200:    LDC  3,3(6)	Load integer constant 
201:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 2
202:     LD  4,2(1)	Pop left into ac1 
203:    TGT  3,4,3	Op > 
* TOFF inc: 3
204:     LD  4,3(1)	Pop left into ac1 
205:     OR  3,4,3	Op OR 
206:     ST  3,3(1)	Push left side 
* TOFF dec: 2
207:    LDC  3,3(6)	Load integer constant 
208:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 3
209:     LD  4,3(1)	Pop left into ac1 
210:    TGT  3,4,3	Op > 
* TOFF inc: 4
211:     LD  4,4(1)	Pop left into ac1 
212:     OR  3,4,3	Op OR 
213:     ST  3,4(1)	Push left side 
* TOFF dec: 3
214:    LDC  3,3(6)	Load integer constant 
215:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 4
216:     LD  4,4(1)	Pop left into ac1 
217:    TGT  3,4,3	Op > 
* TOFF inc: 5
218:     LD  4,5(1)	Pop left into ac1 
219:     OR  3,4,3	Op OR 
220:     ST  3,5(1)	Push left side 
* TOFF dec: 4
221:    LDC  3,3(6)	Load integer constant 
222:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 5
223:     LD  4,5(1)	Pop left into ac1 
224:    TGT  3,4,3	Op > 
* TOFF inc: 6
225:     LD  4,6(1)	Pop left into ac1 
226:     OR  3,4,3	Op OR 
227:     ST  3,6(1)	Push left side 
* TOFF dec: 5
228:    LDC  3,3(6)	Load integer constant 
229:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 6
230:     LD  4,6(1)	Pop left into ac1 
231:    TGT  3,4,3	Op > 
* TOFF inc: 7
232:     LD  4,7(1)	Pop left into ac1 
233:     OR  3,4,3	Op OR 
234:     ST  3,7(1)	Push left side 
* TOFF dec: 6
235:    LDC  3,3(6)	Load integer constant 
236:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 7
237:     LD  4,7(1)	Pop left into ac1 
238:    TGT  3,4,3	Op > 
* TOFF inc: 8
239:     LD  4,8(1)	Pop left into ac1 
240:     OR  3,4,3	Op OR 
241:     ST  3,8(1)	Push left side 
* TOFF dec: 7
242:    LDC  3,3(6)	Load integer constant 
243:    LDC  3,0(6)	Load integer constant 
* TOFF inc: 8
244:     LD  4,8(1)	Pop left into ac1 
245:    TGT  3,4,3	Op > 
* TOFF inc: 9
246:     LD  4,9(1)	Pop left into ac1 
247:     OR  3,4,3	Op OR 
248:     ST  3,9(1)	Push parameter 
* TOFF dec: 8
* Param end outputb
249:    LDA  1,-2(1)	Ghost frame becomes new active frame 
250:    LDA  3,1(7)	Return address in ac 
251:    JMP  7,-235(7)	CALL outputb
252:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* TOFF set: -2
* EXPRESSION
* CALL outnl
253:     ST  1,-2(1)	Store fp in ghost frame for outnl
* TOFF dec: -3
* TOFF dec: -4
* Param end outnl
254:    LDA  1,-2(1)	Ghost frame becomes new active frame 
255:    LDA  3,1(7)	Return address in ac 
256:    JMP  7,-223(7)	CALL outnl
257:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
258:    LDC  2,0(6)	Set return value to 0 
259:     LD  3,-1(1)	Load return address 
260:     LD  1,0(1)	Adjust fp 
261:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,261(7)	Jump to init [backpatch] 
* INIT
262:    LDA  1,0(0)	set first frame at end of globals 
263:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
264:    LDA  3,1(7)	Return address in ac 
265:    JMP  7,-227(7)	Jump to main 
266:   HALT  0,0,0	DONE! 
* END INIT
