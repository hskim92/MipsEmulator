#pragma once
#include"init_main.h"

int Inst_Memory[0x100000];
int R[32];
int pc;
long long int Hi;
long long int Lo;
FILE* outputfile;

int jumpAddr(int address)
{
	return ((pc + 4) & 0xf0000000) | address << 2;
}

int SignExtImm(int imm)
{
	if( (imm & 0x00008000) >> 15 == 1)
		return imm | 0xffff0000;
	else
		return imm;
}
int ZeroExtImm(int imm)
{
	return imm & 0x0000ffff;
}
int BranchAddr(int imm)
{
	if( (imm & 0x00008000) >> 15 == 1)
		return (imm << 2) | 0xfffc0000;
	else
		return imm << 2;
}

void init_if_id(latchIFtoID* fd)
{
	fd->instructionMem = 0;
	fd->PC_toID = 0;
}
void init_id_ex(latch_ID_EX* de)
{
	de->inst.funct=0;
	de->inst.opcode=0;
	de->inst.rd=0;
	de->inst.rs=0;
	de->inst.rt=0;
	de->jump_adress = 0;
	de->jump_check = 0;
	de->inst.shamt=0;
	de->PC_toEX = 0;
	de->rd =0;
	de->ReadData1 =0 ;
	de->ReadData2=0;
	de->Read_Hi_Lo[0] = 0;
	de->Read_Hi_Lo[1] = 0;
	de->rt=0;
	de->Signextend=0;
}
void init_ex_mem(latch_EX_MEM* em)
{
	em->ALU_result=0;
	em->branch_TF=0;
	em->inst.funct=0;
	em->inst.opcode=0;
	em->inst.rd=0;
	em->inst.rs=0;
	em->inst.rt=0;
	em->inst.shamt=0;
	em->PC_toMEM=0;
	em->rd=0;
	em->jump_adress = 0;
	em->jump_check = 0;
	em->mem_adress=0;
	em->Reg_readdata2=0;
	em->result_Hi_Lo[0]=0;
	em->result_Hi_Lo[1]=0;
	em->rt=0;
	em->store_data=0;
}
void init_mem_wb(latch_MEM_WB* mw)
{
	mw->ALU_result_toWB=0;
	mw->DATA_readdata=0;
	mw->inst.funct=0;
	mw->inst.opcode=0;
	mw->inst.rd=0;
	mw->inst.rs=0;
	mw->inst.rt=0;
	mw->inst.shamt=0;
	mw->rd=0;
	mw->result_Hi_Lo[0]=0;
	mw->result_Hi_Lo[1]=0;
	mw->rt=0;
}