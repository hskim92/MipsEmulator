#include "MEM_acc.h"


MEM_acc::MEM_acc(void)
{
}


MEM_acc::~MEM_acc(void)
{
}

int MEM_acc::Mem_access(latchEXtoMEM* input, latchMEMtoWB* output)
{
	output->PC_toWB = input->PC_toMEM;
	if(input->inst.opcode + input->inst.funct + input->inst.rd + input->inst.rs + input->inst.rt + input->inst.shamt == 0){
		return 1;
	}
	fprintf(outputfile, "Memory_Access\t(PC = 0x%08x) : ", input->PC_toMEM - 4);
	output->inst = input->inst;
	output->rt = input->rt;
	output->rd = input->rd;	
	output->dep_type = input->dep_type;
	switch(input->inst.opcode)
	{
		//r[rd] = result
		//R type instruction
	case 0x00:
		//if(input->inst.funct == 0x08)
			//pc = input->ALU_result;
	case 0x1c:
		output->ALU_result_toWB = input->ALU_result;
		output->result_Hi_Lo[0] = input->result_Hi_Lo[0];
		output->result_Hi_Lo[1] = input->result_Hi_Lo[1];
		break;
		//J type instruction
	case 0x02:
	case 0x03:
		//pc = input->ALU_result;
		output->rt = input->rt;
		output->DATA_readdata = input->PC_toMEM;
		output->ALU_result_toWB = input->ALU_result;
		break;
		// I type instruction
	case 0x08:	// r[rt] = alu_result
	case 0x09:	
	case 0x0c:
	case 0x0f:
	case 0x0d:
	case 0x0a:
	case 0x0b:
		output->ALU_result_toWB = input->ALU_result;
		break;
	case 0x04:// branch
	case 0x05:
		//if(input->branch_prediction == 0) - dummy
		//pc = input->ALU_result;			- dummy
		break;
	case 0x30: //r[rt] = m[]
	case 0x23:
		output->DATA_readdata = Inst_Memory[input->mem_adress>>2];
		output->ALU_result_toWB = output->DATA_readdata;
		break;
		// r[rt] = m[alu_result];
	case 0x24:
		output->DATA_readdata = 0x000000ff & Inst_Memory[input->mem_adress>>2] ;
		output->ALU_result_toWB = output->DATA_readdata;
		break;
	case 0x25:	
		output->DATA_readdata = 0x0000ffff & Inst_Memory[input->mem_adress>>2] ;
		output->ALU_result_toWB = output->DATA_readdata;
		break;
	case 0x28:	
		Inst_Memory[input->mem_adress>>2] = Inst_Memory[input->mem_adress>>2] & 0xffffff00 | input->Reg_readdata2 & 0x000000ff;
		output->DATA_readdata = Inst_Memory[input->mem_adress>>2];
		output->ALU_result_toWB = output->DATA_readdata;
		break;
	case 0x29:	
		Inst_Memory[input->mem_adress>>2] = Inst_Memory[input->mem_adress>>2] & 0xffff0000 | input->Reg_readdata2 & 0x0000ffff;
		output->DATA_readdata = Inst_Memory[input->mem_adress>>2];
		output->ALU_result_toWB = output->DATA_readdata;
		break;
	case 0x2b:	
		Inst_Memory[input->mem_adress>>2] = input->Reg_readdata2;
		output->DATA_readdata = Inst_Memory[input->mem_adress>>2];
		output->ALU_result_toWB = output->DATA_readdata;
		break;
	default:
		fprintf(outputfile, "error\n");
	}
	fprintf(outputfile, "ALUdata-%d, Memory data-%d, rd-%d, rt-%d \n",output->ALU_result_toWB, output->DATA_readdata, output->rd, output->rt);
	if(input->inst.opcode == 0x23 || input->inst.opcode == 0x24 || input->inst.opcode == 0x25 || input->inst.opcode == 0x30){
		fprintf(outputfile, "<pre-inst result> R[%d] = 0x%08x\n", output->rt, output->DATA_readdata);
	}
	if(output) return 1;
	else return 0;
}
