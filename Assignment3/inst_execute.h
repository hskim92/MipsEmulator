#pragma once
#include"init_main.h"
#include"Rtype.h"
#include"Jtype.h"
#include"Itype.h"

class inst_execute
{
public:
	inst_execute(void);
	~inst_execute(void);

	int execute(latchIDtoEX* input, latchEXtoMEM* output, latchEXtoMEM* MEM_dep, latchMEMtoWB* mem_output, latchMEMtoWB* wb_dep);
	void dep_check(latchIDtoEX* input, latchEXtoMEM* MEM_dep, latchMEMtoWB* mem_output, latchMEMtoWB* wb_dep);
};

