#pragma once
#include "TableInfo.h"

class LogicHandler
{
	public:
	static void UpdateTable(TableInfo &current, short x, short y, short update);
	static bool SolveCheck(TableInfo x);
};

