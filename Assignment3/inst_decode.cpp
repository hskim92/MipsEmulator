#include "inst_decode.h"

inst_decode::inst_decode(void)
{
}

inst_decode::~inst_decode(void)
{
}

int inst_decode::decode(latchIFtoID* input, latchIDtoEX* output, latchEXtoMEM* ex_dep, latchMEMtoWB* mem_dep)
{
	output->PC_toEX = input->PC_toID;
	if(input->instructionMem == 0){
		return 1;
	}
	output->Signextend = SignExtImm(input->instructionMem & 0x0000ffff);
	output->ReadData1 = R[(input->instructionMem & 0x03e00000) >> 21];//rs
	output->ReadData2 = R[(input->instructionMem & 0x001f0000) >> 16];//rt
	output->rt = (input->instructionMem & 0x001f0000) >> 16;
	output->rd = (input->instructionMem & 0x0000f800) >> 11;
	output->Read_Hi_Lo[0] = Hi;
	output->Read_Hi_Lo[1] = Lo;

	output->inst.opcode = (input->instructionMem & 0xfc000000) >> 26 ;
	output->inst.rs = (input->instructionMem & 0x03e00000) >> 21;
	output->inst.rt = (input->instructionMem & 0x001f0000) >> 16;
	output->inst.rd = (input->instructionMem & 0x0000f800) >> 11;
	output->inst.shamt = (input->instructionMem & 0x000007c0) >> 6;
	output->inst.funct = (input->instructionMem & 0x0000003f);
	fprintf(outputfile, "Decode\t\t(pc = 0x%08x) : %x, %x, %x, %x, %x, %x\n",
				output->PC_toEX - 4, output->inst.opcode, output->inst.rs, output->inst.rt, output->inst.rd, output->inst.shamt, output->inst.funct);

	//jtype-j,jal
	if(output->inst.opcode == 0x02 || output->inst.opcode == 0x03){
		output->jump_check = 2;
	}
	//itype-bne,beq
	else if(output->inst.opcode == 0x04 || output->inst.opcode == 0x05){
		output->jump_check = 2;
	}
	//rtype-jr
	else if(output->inst.opcode == 0x00 && output->inst.funct == 0x08){
		output->jump_check = 1;
		if(mem_dep->dep_type != 0){
			switch(mem_dep->dep_type){
			case 1:
				if(mem_dep->inst.rd == output->inst.rs)
					output->ReadData1 = mem_dep->ALU_result_toWB;
				break;
			case 2:
				if(mem_dep->inst.rt == output->inst.rs)
					output->ReadData1 = mem_dep->ALU_result_toWB;
				break;
			default:
				break;
			}
		}
		else if(ex_dep->dep_type != 0){
			switch(ex_dep->dep_type){
			case 1:
				if(ex_dep->inst.rd == output->inst.rs)
					output->ReadData1 = ex_dep->ALU_result;
				break;
			case 2:
				if(ex_dep->inst.rt == output->inst.rs)
					output->ReadData1 = ex_dep->ALU_result;
				break;
			default:
				break;
			}
		}
		output->jump_adress = output->ReadData1;
	}
	else{
		output->jump_check = 0;
	}

	if(output) return 1;
	else return 0;
}