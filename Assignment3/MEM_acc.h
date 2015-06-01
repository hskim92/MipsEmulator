#pragma once
#include"init_main.h"

class MEM_acc
{
public:
	MEM_acc(void);
	~MEM_acc(void);

	int Mem_access(latchEXtoMEM* input, latchMEMtoWB* output);
};

