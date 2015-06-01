#pragma once
#include"init_main.h"

class inst_decode
{
public:
	inst_decode(void);
	~inst_decode(void);

	int inst_decode::decode(latchIFtoID* input, latchIDtoEX* output, latchEXtoMEM* ex_dep, latchMEMtoWB* mem_dep);
};

