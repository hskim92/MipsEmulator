#pragma once
#include"init_main.h"

class Rtype
{
public:
	Rtype(void);
	~Rtype(void);

	void rtypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void add(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void addu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void and(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void jr(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void nor(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void or(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void slt(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sltu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sll(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void srl(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sub(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void subu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void div(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void divu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void mfhi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void mflo(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void mult(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void multu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void mul(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
};

