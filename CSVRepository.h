#pragma once
#include "Repository.h"
#include <string.h>

class CSVRepository : public Repository
{
private:
	std::string filename = "Tutorials.csv";

public:
	//override functions for file
	void open() override;
	void read() override {};
	void write() override;
};
