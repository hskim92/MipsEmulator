#include "Itype.h"

Itype::Itype(void)
{
}


Itype::~Itype(void)
{
}

void Itype::Itypeinst(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	int imm = (inst.rd) << 11 | (inst.shamt) <<  6 | inst.funct;
	switch (inst.opcode)
	{
	case 0x08:	Itype::addi(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x09:	Itype::addiu(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x0c:	Itype::andi(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x04:	Itype::beq(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x05:	Itype::bne(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x24:	Itype::lbu(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x25:	Itype::lhu(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x30:	Itype::ll(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x0f:	Itype::lui(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x23:	Itype::lw(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x0d:	Itype::ori(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x0a:	Itype::slti(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x0b:	Itype::sltiu(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x28:	Itype::sb(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x29:	Itype::sh(inst, input, output, imm, MEM_dep, wb_dep);		break;
	case 0x2b:	Itype::sw(inst, input, output, imm, MEM_dep, wb_dep);		break;
	default:
		fprintf(outputfile, "not correct I type instruction\n");
		break;
	}

}

void Itype::addi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = input->ReadData1 + SignExtImm(imm);
	fprintf(outputfile, "<addi> R[%d] = R[%d] + SignExtImm\t", inst.rt, inst.rs);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::addiu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = input->ReadData1 + SignExtImm(imm);
	fprintf(outputfile, "<addiu> R[%d] = R[%d] + SignExtImm(%x)\t", inst.rt, inst.rs, SignExtImm(imm));
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::andi(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = input->ReadData1 & SignExtImm(imm);
	fprintf(outputfile, "<andi> R[%d] = R[%d] & ZeroExtImm\t", inst.rt, inst.rs);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::beq(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 0;
	output->jump_check = input->jump_check;
	if( input->ReadData2 == input->ReadData1 ){
		output->ALU_result = input->PC_toEX + BranchAddr(imm);
		output->jump_adress = output->ALU_result;
	}
	else{
		output->jump_adress = input->PC_toEX;	
	}
	fprintf(outputfile, "<beq> if(R[%d] == R[%d]) PC = PC+4+BranchAddr(%x)\t", inst.rt, inst.rs, BranchAddr(imm));
	fprintf(outputfile, "<result> PC = 0x%08x\n", output->jump_adress);
}
void Itype::bne(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 0;
	output->jump_check = input->jump_check;
	if( input->ReadData2 != input->ReadData1 ){
		output->ALU_result = input->PC_toEX + BranchAddr(imm);
		output->jump_adress = output->ALU_result;
	}
	else{
		output->jump_adress = input->PC_toEX;
	}
	fprintf(outputfile, "<bne> if(R[%d] != R[%d]) PC = PC+4+BranchAddr(%x)\t", inst.rt, inst.rs, BranchAddr(imm));
	fprintf(outputfile, "<result> PC = 0x%08x\n", output->jump_adress);
}
void Itype::lbu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	fprintf(outputfile, "<lbu> R[%d] = {24'b0, M[R[%d]+SignExtImm(%x)](7:0)}\n",inst.rt, inst.rs, SignExtImm(imm));
	//fprintf(outputfile, "<result> R[%d] = %d\n", inst.rt, output->mem_adress);
}
void Itype::lhu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	fprintf(outputfile, "<lhu> R[%d] = {16'b0, M[R[%d]+SignExtImm](15:0)}\n",inst.rt, inst.rs);
	//fprintf(outputfile, "<result> R[%d] = %d\n", inst.rt, output->mem_adress);
}
void Itype::ll(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	fprintf(outputfile, "<ll> R[%d] = M[R[%d]+SignExtImm]\n",inst.rt, inst.rs);
	//fprintf(outputfile, "<result> R[%d] = %d\n", inst.rt, output->mem_adress);
}
void Itype::lui(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = imm << 16;
	fprintf(outputfile, "<lui> R[%d] = {imm, 16'b0}\t",inst.rt);
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::lw(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	fprintf(outputfile, "<lw> R[%d] = M[R[%d]+SignExtImm(%x)]\n",inst.rt, inst.rs, SignExtImm(imm));
	//fprintf(outputfile, "<result> R[%d] = %d\n", inst.rt, output->mem_adress);
}
void Itype::ori(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = input->ReadData1 | ZeroExtImm(imm) ;
	fprintf(outputfile, "<ori> R[%d] = R[%d] | ZeroExtImm(%x)\t",inst.rt, inst.rs, ZeroExtImm(imm));
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::slti(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = (input->ReadData1 < SignExtImm(imm))? 1 : 0 ;
	fprintf(outputfile, "<slti> R[%d] = (R[%d] < SignExtImm(%x))? 1 : 0\t", inst.rt, inst.rs, SignExtImm(imm));
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::sltiu(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 2;
	output->ALU_result = (input->ReadData1 < SignExtImm(imm))? 1 : 0 ;
	fprintf(outputfile, "<sltiu> R[%d] = (R[%d] < SignExtImm(%x))? 1 : 0\t", inst.rt, inst.rs, SignExtImm(imm));
	fprintf(outputfile, "<result> R[%d] = 0x%08x\n", inst.rt, output->ALU_result);
}
void Itype::sb(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 3;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	output->Reg_readdata2 = input->ReadData2;
	fprintf(outputfile, "<sb> M[R[%d](0x%08x) + SignExtImm(%x)](7:0) = R[%d](7:0)\t", inst.rs, input->ReadData1, SignExtImm(imm), inst.rt);
	fprintf(outputfile, "<result> M[%x](7:0) = 0x%08x\n", output->mem_adress, output->Reg_readdata2);
}
void Itype::sh(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 3;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	output->Reg_readdata2 = input->ReadData2;
	fprintf(outputfile, "<sh> M[R[%d](0x%08x) + SignExtImm](15:0) = R[%d](15:0)\t", inst.rs, input->ReadData1, inst.rt);
	fprintf(outputfile, "<result> M[%x](15:0) = 0x%08x\n", output->mem_adress, output->Reg_readdata2);
}
void Itype::sw(instruction inst, latchIDtoEX* input, latchEXtoMEM* output, int imm, latchEXtoMEM* MEM_dep, latchMEMtoWB* wb_dep)
{
	output->dep_type = 3;
	output->mem_adress = (input->ReadData1 + SignExtImm(imm));
	output->Reg_readdata2 = input->ReadData2;
	fprintf(outputfile, "<sw> M[R[%d](0x%08x) + SignExtImm(%x)] = R[%d]\t", inst.rs, input->ReadData1, SignExtImm(imm), input->rt);
	fprintf(outputfile, "<result> M[%x] = 0x%08x\n", (input->ReadData1 + SignExtImm(imm)), output->Reg_readdata2);
}

