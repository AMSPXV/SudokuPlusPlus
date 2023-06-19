#pragma once
#include "TableInfo.h"
#include <string>
#include <fstream>

class FileHandler
{
	public:
	static void PushList(LevelNode*& start, short tab[][9], std::string inputdiff, short inum);
	static bool PopList(LevelNode* &start);
	static int CreateLevelList(LevelNode* &start, std::fstream &levelfile);
	static void ClearList(LevelNode*& start);
	static int WriteLevel(TableInfo &x, std::string diff, short levelnum, LevelNode*& start);
	static void SaveScore(TableInfo &x, std::string diff);
};

