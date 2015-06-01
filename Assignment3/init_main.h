#pragma once
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;

extern int Inst_Memory[0x100000];
extern int R[32];
extern int pc;
extern long long int Hi;
extern long long int Lo;
extern FILE* outputfile;

typedef struct inst{
		int opcode;		//inst(31~26) #6
		int rs;			//inst(25~21) #5 
		int rt;			//inst(20~16) #5
		int rd;			//inst(15~11) #5
		int shamt;		//inst(10~ 6) #5
		int funct;		//inst( 5~ 0) #6
}instruction;

typedef struct latch_IF_ID{
	int PC_toID;
	int instructionMem;
}latchIFtoID;

typedef struct latch_ID_EX{
	instruction inst;
	int PC_toEX;
	int ReadData1;//rs
	int ReadData2;//rt
	int Read_Hi_Lo[2];
	int Signextend;
	int jump_check;
	int jump_adress;
	int rt;
	int rd;
}latchIDtoEX;

typedef struct latch_EX_MEM{
	instruction inst;
	int branch_TF;
	int jump_check;
	int jump_adress;
	int dep_type;
	int PC_toMEM;
	int mem_adress;
	int ALU_result;
	int result_Hi_Lo[2];
	int store_data;
	int Reg_readdata2;
	int rt;
	int rd;
}latchEXtoMEM;

typedef struct latch_MEM_WB{
	instruction inst;
	int PC_toWB;
	int DATA_readdata;
	int dep_type;
	int result_Hi_Lo[2];
	int ALU_result_toWB;
	int rt;
	int rd;
}latchMEMtoWB;


int jumpAddr(int address);
int SignExtImm(int imm);
int ZeroExtImm(int imm);
int BranchAddr(int imm);
void init_if_id(latchIFtoID* fd);
void init_id_ex(latch_ID_EX* de);
void init_ex_mem(latch_EX_MEM* em);
void init_mem_wb(latch_MEM_WB* mw);