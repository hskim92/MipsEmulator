#include "Jtype.h"

Jtype::Jtype(void)
{
}


Jtype::~Jtype(void)
{
}

int Jtype::JumpAddr(int address)
{
	return ((pc + 4) & 0xf0000000) | address << 2;
}

void Jtype::jtypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	int address = (inst.rs) << 21 | (inst.rt) << 16 | (inst.rd) << 11 |
		(inst.shamt) <<  6 | inst.funct;
	if(inst.opcode == 0x02)
		Jtype::j(address, input, output, MEM_dep, wb_dep);
	else if(inst.opcode == 0x03)
		Jtype::jal(address, input, output, MEM_dep, wb_dep);
	else
		fprintf(outputfile, "not correct J type instruction\n");
}
void Jtype::j(int address, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 0;
	output->ALU_result = JumpAddr(address);
	output->jump_check = input->jump_check;
	output->jump_adress = output->ALU_result;
	fprintf(outputfile, "<j> PC = JumpAddr(0x%08x)\t", JumpAddr(address));
	fprintf(outputfile, "<result> pc = 0x%08x\n", JumpAddr(address));
}
void Jtype::jal(int address, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->rt = 31;
	output->inst.rt = 31;
	output->jump_check = input->jump_check;
	output->jump_adress = JumpAddr(address);
	output->ALU_result = input->PC_toEX + 4;
	fprintf(outputfile, "<jal> R[31] = PC(0x%08x) + 8; PC = JumpAddr(0x%08x)\t", input->PC_toEX-4, JumpAddr(address));
	fprintf(outputfile, "<result> R[31] = 0x%08x; PC = 0x%08x\n", output->ALU_result, JumpAddr(address));
}
