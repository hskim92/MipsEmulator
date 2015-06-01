#include "inst_fetch.h"

inst_fetch::inst_fetch(void)
{
}

inst_fetch::~inst_fetch(void)
{
}

int inst_fetch::litobi(int inst)
{
	return ((inst >> 24) & 0x000000ff) |
		((inst >> 8) & 0x0000ff00) |
		((inst << 8) & 0x00ff0000) |
		((inst << 24) & 0xff000000);
}

int inst_fetch::IF(latchIFtoID* output, latchIDtoEX* pre_output)
{
	if((pre_output->jump_adress) == -1 || (pre_output->PC_toEX) == -1){
		pc = -1;
	}
	else
	{
		if(pc ==  -1){
			return 1;
		}
		if(pre_output->jump_check == 0){
			output->instructionMem = litobi(Inst_Memory[(pre_output->PC_toEX)>>2]);
		}
		else if(pre_output->jump_check == 1){
			output->instructionMem = litobi(Inst_Memory[(pre_output->jump_adress)>>2]);
			pc = pre_output->jump_adress;
		}
		else if(pre_output->jump_check == 2){
			return 1;
		}
		pc = pc+4;
	}
	fprintf(outputfile, "Instruction Fetch\t(pc = 0x%08x) : %08x\n", pc-4, output->instructionMem);
	output->PC_toID = pc;
	if(output) return 1;
	else return 0; 
}
