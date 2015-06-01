#include "Rtype.h"

Rtype::Rtype(void)
{
}


Rtype::~Rtype(void)
{
}

void Rtype::rtypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	if(inst.opcode == 0x00)
	{
		switch (inst.funct)
		{
		case 0x20:	Rtype::add(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x21:	Rtype::addu(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x24:	Rtype::and(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x08:	Rtype::jr(inst, input, output, MEM_dep, wb_dep);			break;
		case 0x27:	Rtype::nor(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x25:	Rtype::or(inst, input, output, MEM_dep, wb_dep);			break;
		case 0x2a:	Rtype::slt(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x2b:	Rtype::sltu(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x00:	Rtype::sll(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x02:	Rtype::srl(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x22:	Rtype::sub(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x23:	Rtype::subu(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x1a:	Rtype::div(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x1b:	Rtype::divu(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x10:	Rtype::mfhi(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x12:	Rtype::mflo(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x18:	Rtype::mult(inst, input, output, MEM_dep, wb_dep);		break;
		case 0x19:	Rtype::multu(inst, input, output, MEM_dep, wb_dep);		break;
		default:
			break;
		}
	}
	else if(inst.opcode == 0x1c)
	{
		if(inst.funct == 0x02)
			Rtype::mul(inst, input, output, MEM_dep, wb_dep);
	}
	else
		fprintf(outputfile, "not correct R type instruction inst\n");
}

void Rtype::add(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 + input->ReadData2;
	fprintf(outputfile, "<add> R[%d] = R[%d] + R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::addu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 + input->ReadData2;
	fprintf(outputfile, "<addu> R[%d] = R[%d] + R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::and(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 & input->ReadData2;
	fprintf(outputfile, "<and> R[%d] = R[%d] & R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::jr(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 0;
	output->ALU_result = input->ReadData1;
	fprintf(outputfile, "<jr> pc = R[%d]\t", inst.rs);
	fprintf(outputfile, "<result> pc = 0x%08x\n", output->ALU_result); 
}
void Rtype::nor(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = ~ ( input->ReadData1 | input->ReadData2 );
	fprintf(outputfile, "<nor> R[%d] = ~(R[%d] | R[%d])\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::or(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 | input->ReadData2;
	fprintf(outputfile, "<or> R[%d] = R[%d] | R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::slt(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = (input->ReadData1 < input->ReadData2)? 1 : 0 ;
	fprintf(outputfile, "<slt> R[%d] = (R[%d] < R[%d])? 1 : 0\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::sltu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = (input->ReadData1 < input->ReadData2)? 1 : 0 ;
	fprintf(outputfile, "<sltu> R[%d] = (R[%d] < R[%d])? 1 : 0\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::sll(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData2 << inst.shamt;
	fprintf(outputfile, "<sll> R[%d] = R[%d] << 0x%08x\t", inst.rd, inst.rt, inst.shamt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::srl(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData2 >> inst.shamt;
	fprintf(outputfile, "<srl> R[%d] = R[%d] >> 0x%08x\t", inst.rd, inst.rt, inst.shamt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::sub(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 - input->ReadData2;
	fprintf(outputfile, "<sub> R[%d] = R[%d] - R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::subu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 - input->ReadData2;
	fprintf(outputfile, "<subu> R[%d] = R[%d] - R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::div(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 4;
	output->result_Hi_Lo[1] = input->ReadData1 / input->ReadData2;
	output->result_Hi_Lo[0] = input->ReadData1 % input->ReadData2;
	fprintf(outputfile, "<div> Lo = R[%d] / R[%d], Hi = R[%d] % R[%d]\t", inst.rs, inst.rt, inst.rs, inst.rt);
	fprintf(outputfile, "<result> Lo = %ld; Hi = %ld\n", output->result_Hi_Lo[1], output->result_Hi_Lo[0]); 
}
void Rtype::divu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 4;
	output->result_Hi_Lo[1] = input->ReadData1 / input->ReadData2;
	output->result_Hi_Lo[0] = input->ReadData1 % input->ReadData2;
	fprintf(outputfile, "<div> Lo = R[%d] / R[%d], Hi = R[%d] % R[%d]\t", inst.rs, inst.rt, inst.rs, inst.rt);
	fprintf(outputfile, "<result> Lo = %ld; Hi = %ld\n", output->result_Hi_Lo[1], output->result_Hi_Lo[0]); 
}
void Rtype::mfhi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->Read_Hi_Lo[0];
	fprintf(outputfile, "<mfhi> R[%d] = Hi\t", inst.rd);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::mflo(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->Read_Hi_Lo[1];
	fprintf(outputfile, "<mflo> R[%d] = Lo\t", inst.rd);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}
void Rtype::mult(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 4;
	output->result_Hi_Lo[0] = ((input->ReadData1 >> 16) * (input->ReadData2 >> 16)) << 16;
	output->result_Hi_Lo[1] = (input->ReadData1 & 0x0000ffff) * (input->ReadData2 & 0x0000ffff);
	fprintf(outputfile, "<mult> {Hi, Lo} = R[%d] * R[%d]\t", inst.rs, inst.rt);
	fprintf(outputfile, "<result> Lo = %ld; Hi = %ld\n", output->result_Hi_Lo[1], output->result_Hi_Lo[0]); 
}
void Rtype::multu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 4;
	output->result_Hi_Lo[0] = ((input->ReadData1 >> 16) * (input->ReadData2 >> 16)) << 16;
	output->result_Hi_Lo[1] = (input->ReadData1 & 0x0000ffff) * (input->ReadData2 & 0x0000ffff);
	fprintf(outputfile, "<multu> {Hi, Lo} = R[%d] * R[%d]\t", inst.rs, inst.rt);
	fprintf(outputfile, "<result> Lo = %ld; Hi = %ld\n", output->result_Hi_Lo[1], output->result_Hi_Lo[0]); 
}
void Rtype::mul(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 1;
	output->ALU_result = input->ReadData1 * input->ReadData2;
	fprintf(outputfile, "<mul> R[%d] = R[%d] * R[%d]\t", inst.rd, inst.rs, inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rd, output->ALU_result); 
}

