#pragma once
#include <string>
#include <chrono>


	struct LevelNode
	{
		std::string dific;
		short num;
		short data[9][9];
		LevelNode* next;
	};

	class TableInfo
	{
		short data[9][9];
		int clicks;

	public:
		bool primordialCheck[9][9];
		std::chrono::high_resolution_clock::time_point startofsolving;
		std::chrono::high_resolution_clock::time_point endofsolving;

		TableInfo();
		~TableInfo();
		void operator=(short tab[][9]);
		void getData(short tab[][9]);
		void increaseClick();
		int getClicks();
	};
