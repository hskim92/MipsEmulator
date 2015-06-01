#pragma once
#include"init_main.h"

class Jtype
{
public:
	Jtype(void);
	~Jtype(void);
	int JumpAddr(int address);

	void jtypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void j(int address, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void jal(int address, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
};

