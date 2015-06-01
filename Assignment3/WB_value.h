#pragma once
#include"init_main.h"

class WB_value
{
public:
	WB_value(void);
	~WB_value(void);

	int Write_back(latchMEMtoWB* input);
};

