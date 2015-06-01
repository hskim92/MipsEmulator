#include"init_main.h"
#include"inst_fetch.h"
#include"inst_decode.h"
#include"inst_execute.h"
#include"MEM_acc.h"
#include"WB_value.h"

inst_fetch fetch;
inst_decode decode;
inst_execute exe;
MEM_acc mem;
WB_value wb;

int main()
{
	FILE* inputfile;
	int result;
	int check[5]={0,};
	latchIFtoID IF_ID[2]={0,}; //0-output, 1-input
	latchIDtoEX ID_EX[2]={0,};
	latchEXtoMEM EX_MEM[2]={0,};
	latchMEMtoWB MEM_WB[2]={0,};
	int single_inst;
	int cycle_count = 1;

	//initialization
	pc = 0x00000000;
	R[29] = 0x00100000;
	R[31] = 0xffffffff;
	
	inputfile = fopen("simple.bin", "r+");	//input file name
	outputfile = fopen("simple.txt", "w+");	//output file name

	result = fread(Inst_Memory, sizeof(int), 0x100000, inputfile);
	if(result)
	{
		// print all bin file
		for(single_inst=0; single_inst < result; single_inst++)
			fprintf(outputfile, "%08x\n", fetch.litobi(Inst_Memory[single_inst]));
		
		while(pc + IF_ID[1].PC_toID + ID_EX[1].PC_toEX + EX_MEM[1].PC_toMEM + MEM_WB[1].PC_toWB != -5)
		//for(;cycle_count < 30; cycle_count++)
		{
			if(cycle_count>78){
				cycle_count = cycle_count;
			}
			init_if_id(&IF_ID[0]);
			init_id_ex(&ID_EX[0]);
			init_ex_mem(&EX_MEM[0]);
			init_mem_wb(&MEM_WB[0]);
			fprintf(outputfile, "\t%d cycle \n", cycle_count);
			check[4] = wb.Write_back(&MEM_WB[1]);
			if(!check[4])	fprintf(outputfile, "No write back\n");
			check[3] = mem.Mem_access(&EX_MEM[1], &MEM_WB[0]);
			if(!check[3])	fprintf(outputfile, "No memory access\n");
			check[2] = exe.execute(&ID_EX[1], &EX_MEM[0], &EX_MEM[1], &MEM_WB[0], &MEM_WB[1]);
			if(!check[2])	fprintf(outputfile, "No error\n");
			check[1] = decode.decode(&IF_ID[1], &ID_EX[0], &EX_MEM[0], &MEM_WB[0]);
			if(!check[1])	fprintf(outputfile, "No decode\n");
			if(EX_MEM[0].jump_check == 2){//branch pr j, jal
				ID_EX[0].jump_check = 1;
				ID_EX[0].jump_adress = EX_MEM[0].jump_adress;
			}
			check[0] = fetch.IF(&IF_ID[0], &ID_EX[0]);
			if(!check[0])//print cycle count, instruction hexacode
				fprintf(outputfile, "No fetch\n");
			if(EX_MEM[0].jump_check == 2){
				init_id_ex(&ID_EX[0]);
			}
			init_if_id(&IF_ID[1]);
			init_id_ex(&ID_EX[1]);
			init_ex_mem(&EX_MEM[1]);
			init_mem_wb(&MEM_WB[1]);

			IF_ID[1] = IF_ID[0];
			ID_EX[1] = ID_EX[0];
			EX_MEM[1] = EX_MEM[0];
			MEM_WB[1] = MEM_WB[0];
			cycle_count++;
		}
	}	
	fprintf(outputfile, "result : %d\n", R[2]);

	system("pause");
	return 0;
}