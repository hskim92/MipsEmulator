#include "WB_value.h"

WB_value::WB_value(void)
{
}


WB_value::~WB_value(void)
{
}

int WB_value::Write_back(latchMEMtoWB* input)
{
	if(input->inst.opcode + input->inst.funct + input->inst.rd + input->inst.rs + input->inst.rt + input->inst.shamt == 0){
		return 1;
	}
	fprintf(outputfile, "Write_back\t(pc = 0x%08x) : ALUdata-%d, Memorydata-%d, rd-%d, rt-%d \n",input->PC_toWB-4, input->ALU_result_toWB, input->DATA_readdata, input->rd, input->rt);
	switch(input->inst.opcode)
	{
		//r[rd] = result
		//R type instruction
	case 0x00:
	case 0x1c:
		if(input->inst.funct == 0x08)//jr
			break;
		switch(input->inst.funct)
		{
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x1b:
			Hi = input->result_Hi_Lo[0];
			Lo = input->result_Hi_Lo[1];
		default:
			R[input->rd] = input->ALU_result_toWB;
		}		
		break;
		//J type instruction
	case 0x03:	// r[rt] = alu_result
	case 0x08:	
	case 0x09:	
	case 0x0c:
	case 0x0f:
	case 0x0d:
	case 0x0a:
	case 0x0b:
		R[input->rt] = input->ALU_result_toWB;
		break;
	case 0x30: //r[rt] = m[]
	case 0x23:
	case 0x24:
	case 0x25:
		R[input->rt] = input->DATA_readdata;
		break;
	default:
		break;
	}
	return 1;
}