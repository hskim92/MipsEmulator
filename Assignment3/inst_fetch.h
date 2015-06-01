#pragma once
#include"init_main.h"

class inst_fetch
{
public:
	inst_fetch(void);
	~inst_fetch(void);

	int litobi(int inst);
	int IF(latchIFtoID* output, latchIDtoEX* pre_output);
};

