#include "inst_execute.h"

inst_execute::inst_execute(void)
{
}

inst_execute::~inst_execute(void)
{
}

int inst_execute::execute(latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* mem_output, latchMEMtoWB* wb_dep)
{
	output->PC_toMEM = input->PC_toEX;
	if(input->inst.opcode + input->inst.funct + input->inst.rd + input->inst.rs + input->inst.rt + input->inst.shamt == 0){
		return 1;
	}
	Rtype rtype;
	Jtype jtype;
	Itype itype;
	output->inst = input->inst;
	output->Reg_readdata2 = input->ReadData2;
	output->rt = input->rt;
	output->rd = input->inst.rd;
	fprintf(outputfile, "Execute\t\t(pc: 0x%08x) : \t ", input->PC_toEX - 4);
	inst_execute::dep_check(input, MEM_dep, mem_output,wb_dep);
	switch(input->inst.opcode)
	{
		//R type instruction
	case 0x00:
	case 0x10:
	case 0x1c:
		rtype.rtypeinst(input->inst, input, output, MEM_dep, wb_dep);
		break;
		//J type instruction
	case 0x02:
	case 0x03:
		jtype.jtypeinst(input->inst, input, output, MEM_dep, wb_dep);
		break;
		// I type instruction
	default:
		itype.Itypeinst(input->inst, input, output, MEM_dep, wb_dep);
		break;
	}
	if(output) return 1;
	else return 0;

}

void inst_execute::dep_check(latchIDtoEX* input, latchEXtoMEM* MEM_dep, latchMEMtoWB* mem_output, latchMEMtoWB* wb_dep)
{
	int imm=0;
	//MEM_dep->dep_type ¾øÀ¸¸é 0, rd write 1, rt write 2, mem write 3, hi_lo write 4
	if(wb_dep->dep_type != 0){
		switch(wb_dep->dep_type){
		case 1:
			if(input->inst.rs == wb_dep->inst.rd){	
				input->ReadData1 = wb_dep->ALU_result_toWB;
			}
			if(input->inst.rt == wb_dep->inst.rd){
				input->ReadData2 = wb_dep->ALU_result_toWB;
			}
			break;
		case 2:
			if(input->inst.rs == wb_dep->inst.rt){
				input->ReadData1 = wb_dep->ALU_result_toWB;
			}
			if(input->inst.rt == wb_dep->inst.rt){
				input->ReadData2 = wb_dep->ALU_result_toWB;
			}
			break;
		case 3:
			break;
		case 4:
			input->Read_Hi_Lo[0] = wb_dep->result_Hi_Lo[0];
			input->Read_Hi_Lo[1] = wb_dep->result_Hi_Lo[1];
			break;
		default:
			break;
		}
	}
	if(MEM_dep->dep_type != 0){
		switch(MEM_dep->dep_type){
		case 1:
			if(input->inst.rs == MEM_dep->inst.rd){
				input->ReadData1 = MEM_dep->ALU_result;
			}
			if(input->inst.rt == MEM_dep->inst.rd){
				input->ReadData2 = MEM_dep->ALU_result;
			}
			break;
		case 2:
			if(input->inst.rs == MEM_dep->inst.rt){
				if(MEM_dep->inst.opcode == 0x23 || MEM_dep->inst.opcode == 0x24 || MEM_dep->inst.opcode == 0x25 || MEM_dep->inst.opcode == 0x30){
					input->ReadData1 = mem_output->DATA_readdata;				
				}
				else{
					input->ReadData1 = MEM_dep->ALU_result;
				}
			}
			if(input->inst.rt == MEM_dep->inst.rt){
				if(MEM_dep->inst.opcode == 0x23 || MEM_dep->inst.opcode == 0x24 || MEM_dep->inst.opcode == 0x25 || MEM_dep->inst.opcode == 0x30){
					input->ReadData2 = mem_output->DATA_readdata;				
				}
				else{
					input->ReadData2 = MEM_dep->ALU_result;
				}
			}
			break;
		case 3:
			break;
		case 4:
			input->Read_Hi_Lo[0] = MEM_dep->result_Hi_Lo[0];
			input->Read_Hi_Lo[1] = MEM_dep->result_Hi_Lo[1];
			break;
		default:
			break;
		}
	}
}