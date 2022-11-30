#include "HTMLRepository.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

/// <summary>
/// overrides open function
/// </summary>
void HTMLRepository::open()
{
	std::string s = "start ";
	system(s.append(this->filename).c_str());
}

/// <summary>
/// overrides write function
/// </summary>
void HTMLRepository::write()
{
	std::ofstream f(this->filename);
	if (!f.is_open())
		return;
	f << "<!DOCTYPE html><html><head><title>Tutorials</title></head><body><table border=\"1\"";
	f << "<tr>";
	f << "<td>Title</td>";
	f << "<td>Presenter</td>";
	f << "<td>Duaration</td>";
	f << "<td>Likes</td>";
	f << "<td>Link</td>";
	f << "</tr>";
	for (const Tutorial& t : this->tutorials)
	{
		f << "<tr>";
		f << "<td>" + t.getTitle() + "</td>";
		f << "<td>" + t.getPresenter() + "</td>";
		f << "<td>" + t.getDuration() + "</td>";
		f << "<td>" + std::to_string(t.getLikes()) + "</td>";
		f << "<td><a href=\"" + t.getLink() + "\">link</a></td>";
		f << "</tr>";
	}
	f << "</table></body></html>";
	f.close();
}
