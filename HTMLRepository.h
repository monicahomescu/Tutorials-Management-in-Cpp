#pragma once
#include "Repository.h"
#include <string.h>

class HTMLRepository : public Repository
{
private:
	std::string filename = "Tutorials.html";

public:
	//override functions for file
	void open() override;
	void read() override {};
	void write() override;
};
