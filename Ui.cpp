#include "Ui.h"
#include "Exceptions.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Ui::addUi()
{
	std::cout << "Enter the title: ";
	std::string title;
	getline(std::cin, title);

	std::cout << "Enter the presenter: ";
	std::string presenter;
	std::getline(std::cin, presenter);

	std::cout << "Enter the duration: ";
	std::string duration;
	getline(std::cin, duration);

	std::cout << "Enter the likes: ";
	std::string s;
	getline(std::cin, s);
	
	if (val.validateLikes(s) != "")
		std::cout << val.validateLikes(s);
	else
	{
		int likes = 0;

		int nr = 0;
		int p = 1;
		int n = s.length();
		for (int i = n - 1; i >= 0; i--)
		{
			nr += (s[i] - '0') * p;
			p *= 10;
		}
		likes = nr;


		std::cout << "Enter the link: ";
		std::string link;
		std::getline(std::cin, link);

		Tutorial t{ title, presenter, duration, likes, link };

		try
		{
			val.errors(t);
		}
		catch (ValidationException& ex)
		{
			std::cout << ex.getMessage();
			return;
		}
		try
		{
			this->serv.addServ(t);
			std::cout << "The tutorial was added!\n";
		}
		catch (RepositoryException& ex)
		{
			std::cout << ex.getMessage();
		}
	}
}

void Ui::deleteUi()
{
	std::cout << "Enter the title: ";
	std::string title;
	getline(std::cin, title);

	std::cout << "Enter the presenter: ";
	std::string presenter;
	std::getline(std::cin, presenter);

	try
	{
		this->serv.deleteServ(title, presenter);
		std::cout << "The tutorial was deleted!\n";
		this->serv.deleteWlist(this->serv.getWlist().findTutorial(title, presenter));
	}
	catch (RepositoryException& ex)
	{
		std::cout << ex.getMessage();
	}
}

void Ui::updateUi()
{
	std::cout << "Enter the title to find: ";
	std::string findTitle;
	getline(std::cin, findTitle);

	std::cout << "Enter the presenter to find: ";
	std::string findPresenter;
	std::getline(std::cin, findPresenter);

	std::cout << "Enter the title: ";
	std::string title;
	getline(std::cin, title);

	std::cout << "Enter the presenter: ";
	std::string presenter;
	std::getline(std::cin, presenter);

	std::cout << "Enter the duration: ";
	std::string duration;
	getline(std::cin, duration);

	std::cout << "Enter the likes: ";
	std::string s;
	getline(std::cin, s);

	if (val.validateLikes(s) != "")
		std::cout << val.validateLikes(s);
	else
	{
		int likes = 0;
		int nr = 0;
		int p = 1;
		int n = s.length();
		for (int i = n - 1; i >= 0; i--)
		{
			nr += (s[i] - '0') * p;
			p *= 10;
		}
		likes = nr;


		std::cout << "Enter the link: ";
		std::string link;
		std::getline(std::cin, link);

		Tutorial t{ title, presenter, duration, likes, link };

		try
		{
			val.errors(t);
		}
		catch (ValidationException& ex)
		{
			std::cout << ex.getMessage();
			return;
		}
		try
		{
			Tutorial f = this->serv.getRepo().findTutorial(findTitle, findPresenter);
			this->serv.updateServ(findTitle, findPresenter, t);
			std::cout << "The tutorial was updated!\n";
			this->serv.deleteWlist(f);
			this->serv.addWlist(t);
		}
		catch (RepositoryException& ex)
		{
			std::cout << ex.getMessage();
		}
	}
}

void Ui::listUi()
{
	try
	{
		std::string s = this->serv.listTutorials();
		std::cout << "Tutorials in the database:\n";
		std::cout << s;
	}
	catch (RepositoryException& ex)
	{
		std::cout << ex.getMessage();
	}
}

void Ui::sortUi()
{
	std::cout << "0 - Sort ascending by title.\n";
	std::cout << "1 - Sort descending by likes.\n";
	std::cout << "Enter the decision: ";
	int d;
	std::cin >> d;
	std::cin.ignore();
	std::vector<Tutorial> v = this->serv.getRepo().getTutorials();
	if (d == 0)
	{
		ComparatorAscendingByTitle c{};
		this->serv.sort(v, c);
		for (auto t : v)
			std::cout << t;
	}
	else
	{
		ComparatorDescendingByLikes c{};
		this->serv.sort(v, c);
		for (auto t : v)
			std::cout << t;
	}
}

void Ui::menuAdministrator()
{
	std::string s = "--------------------\n";
	s += "0 - Exist administrator mode.\n";
	s += "1 - Add tutorial.\n";
	s += "2 - Delete tutorial.\n";
	s += "3 - Update tutorial.\n";
	s += "4 - List tutorials.\n";
	s += "5 - Sort tutorials.\n";
	s += "--------------------\n";
	std::cout << s;
}

void Ui::administratorMode()
{
	while (true)
	{
		this->menuAdministrator();
		std::cout << "Enter command: ";
		std::string i;
		getline(std::cin, i);
		if (i != "0" && i != "1" && i != "2" && i != "3" && i != "4" && i != "5")
			std::cout << "The command should be a digit between 0 and 5!\n";
		else
		{
			int c = i[0] - '0';
			if (c == 0)
				break;
			switch (c)
			{
			case 1:
				this->addUi();
				this->serv.getRepo().write();
				break;
			case 2:
				this->deleteUi();
				this->serv.getRepo().write();
				this->serv.getWlist().write();
				break;
			case 3:
				this->updateUi();
				this->serv.getRepo().write();
				this->serv.getWlist().write();
				break;
			case 4:
				this->listUi();
				break;
			case 5:
				this->sortUi();
				break;
			}
		}
	}
}

void Ui::menuPresenter()
{
	std::string s = "--------------------------------------------\n";
	s += "0 - Exist presenter tutorials.\n";
	s += "1 - Add tutorial to watchlist.\n";
	s += "2 - Go to next tutorial.\n";
	s += "--------------------------------------------\n";
	std::cout << s;
}

void Ui::presenterMode()
{
	try
	{
		std::cout << "Enter the presenter: ";
		std::string presenter;
		std::getline(std::cin, presenter);
		std::vector<Tutorial> tutorials = this->serv.seePresenterTutorials(presenter);
		int index = 0;
		std::cout << "Title: " + tutorials[index].getTitle() + " | Presenter: " + tutorials[index].getPresenter() + " | Duration: " + tutorials[index].getDuration() + " | Likes: " + std::to_string(tutorials[index].getLikes()) + "\n";
		tutorials[index].play();
		while (true)
		{
			this->menuPresenter();
			std::cout << "Enter command: ";
			std::string i;
			getline(std::cin, i);
			if (i != "0" && i != "1" && i != "2")
				std::cout << "The command should be a digit between 0 and 2!\n";
			else
			{
				int c = i[0] - '0';
				if (c == 0)
					break;
				switch (c)
				{
				case 1:
					try
					{
						this->serv.addWlist(tutorials[index]);
						std::cout << "The tutorial was added to the watchlist!\n";
						this->serv.getWlist().write();
					}
					catch (RepositoryException& ex)
					{
						std::cout << ex.getMessage();
					}
					break;
				case 2:
					if (index + 1 == tutorials.size())
						index = 0;
					else
						index++;
					std::cout << "Title: " + tutorials[index].getTitle() + " | Presenter: " + tutorials[index].getPresenter() + " | Duration: " + tutorials[index].getDuration() + " | Likes: " + std::to_string(tutorials[index].getLikes()) + "\n";
					tutorials[index].play();
					break;
				}
			}
		}
	}
	catch (RepositoryException& ex)
	{
		std::cout << ex.getMessage();
	}
}

void Ui::menuWlist()
{
	std::string s = "--------------------------------------------\n";
	s += "0 - Exist watchlist.\n";
	s += "1 - Delete and like tutorial.\n";
	s += "2 - Go to next tutorial.\n";
	s += "3 - Open watchlist.\n";
	s += "--------------------------------------------\n";
	std::cout << s;
}

void Ui::wlistMode()
{
	try
	{
		std::vector<Tutorial> tutorials = this->serv.getWlist().getAll();
		int index = 0;
		std::cout << "Title: " + tutorials[index].getTitle() + " | Presenter: " + tutorials[index].getPresenter() + " | Duration: " + tutorials[index].getDuration() + " | Likes: " + std::to_string(tutorials[index].getLikes()) + "\n";
		tutorials[index].play();
		std::string d;
		while (true)
		{
			this->menuWlist();
			std::cout << "Enter command: ";
			std::string i;
			getline(std::cin, i);
			if (i != "0" && i != "1" && i != "2" && i != "3")
				std::cout << "The command should be a digit between 0 and 3!\n";
			else
			{
				int c = i[0] - '0';
				if (c == 0)
					break;
				switch (c)
				{
				case 1:
					try
					{
						std::cout << "0 - Don't like tutorial.\n";
						std::cout << "1 - Like tutorial.\n";
						std::cout << "Enter the decision: ";

						std::getline(std::cin, d);
						while (d != "0" && d != "1")
						{
							std::cout << "The decision should be 0 or 1!\n";
							std::cout << "Enter the decision: ";
							std::getline(std::cin, d);
						}
						if (d == "0")
							std::cout << "The tutorial wasn't liked!\n";
						else
							if (d == "1")
							{
								this->serv.likeTutorial(tutorials[index]);
								std::cout << "The tutorial was liked!\n";
								this->serv.getRepo().write();
							}
						this->serv.deleteWlist(tutorials[index]);
						std::cout << "The tutorial was deleted from the watchlist!\n";
						this->serv.getWlist().write();
					}
					catch (RepositoryException& ex)
					{
						std::cout << ex.getMessage();
					}
					index--;
					if (tutorials.size() != 1)
						tutorials = this->serv.getWlist().getAll();
					break;
				case 2:
					if (index + 1 == tutorials.size())
						index = 0;
					else
						index++;
					std::cout << "Title: " + tutorials[index].getTitle() + " | Presenter: " + tutorials[index].getPresenter() + " | Duration: " + tutorials[index].getDuration() + " | Likes: " + std::to_string(tutorials[index].getLikes()) + "\n";
					tutorials[index].play();
					break;
				case 3:
					try
					{
						this->serv.getWlist().open();
					}
					catch (RepositoryException& ex)
					{
						std::cout << ex.getMessage();
					}
				}
			}
		}
	}
	catch (RepositoryException& ex)
	{
		std::cout << ex.getMessage();
	}
}

void Ui::menuUser()
{
	std::string s = "--------------------------------------------\n";
	s += "0 - Exist user mode.\n";
	s += "1 - See tutorials by presenter.\n";
	s += "2 - See watchlist.\n";
	s += "--------------------------------------------\n";
	std::cout << s;
}

void Ui::userMode()
{
	while (true)
	{
		this->menuUser();
		std::cout << "Enter command: ";
		std::string i;
		getline(std::cin, i);
		if (i != "0" && i != "1" && i != "2")
			std::cout << "The command should be a digit between 0 and 2!\n";
		else
		{
			int c = i[0] - '0';
			if (c == 0)
				break;
			switch (c)
			{
			case 1:
				this->presenterMode();
				break;
			case 2:
				this->wlistMode();
				break;
			}
		}
	}
}

void Ui::startProgram()
{
	while (true)
	{
		std::cout << "------------------------------\n";
		std::cout << "0 - Exit program.\n";
		std::cout << "1 - Choose administrator mode.\n";
		std::cout << "2 - Choose user mode.\n";
		std::cout << "------------------------------\n";
		std::cout << "Enter command: ";
		std::string i;
		getline(std::cin, i);
		if (i != "0" && i != "1" && i != "2")
			std::cout << "The command should be a digit between 0 and 2!\n";
		else
		{
			int c = i[0] - '0';
			if (c == 0)
				break;
			switch (c)
			{
			case 1:
				this->administratorMode();
				break;
			case 2:
				this->userMode();
				break;
			}
		}
	}
}
