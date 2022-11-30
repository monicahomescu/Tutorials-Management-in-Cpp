#include "CSVRepository.h"
#include <iostream>
#include <sstream>
#include <fstream>

/// <summary>
/// overrides open function
/// </summary>
void CSVRepository::open()
{
	std::string s = "notepad ";
	system(s.append(this->filename).c_str());
}

/// <summary>
/// overrides write function
/// </summary>
void CSVRepository::write()
{
	std::ofstream f(this->filename);
	if (!f.is_open())
		return;
	for (const Tutorial& t : this->tutorials)
		f << t;
	f.close();
}
