* C- compiler version C-F23
* File compiled:  a001.c-
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
  0:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* Compound Body
  1:    LDC  3,666(6)	Load integer constant 
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
  2:    LDC  2,0(6)	Set return value to 0 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION main
* 
  0:    JMP  7,5(7)	Jump to init [backpatch] 
* INIT
  6:    LDA  1,0(0)	set first frame at end of globals 
  7:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
  8:    LDA  3,1(7)	Return address in ac 
  9:    JMP  7,-10(7)	Jump to main 
 10:   HALT  0,0,0	DONE! 
* END INIT
