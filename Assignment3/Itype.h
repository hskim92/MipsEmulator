#pragma once
#include"init_main.h"

class Itype
{
public:
	Itype(void);
	~Itype(void);

	void Itypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);

	void addi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void addiu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void andi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void beq(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void bne(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void lbu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void lhu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void ll(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void lui(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void lw(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void ori(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void slti(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sltiu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sb(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sh(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
	void sw(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep);
};

