#include "Ui.h"
#include "FileRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include <string>
#include <crtdbg.h>
#include <cassert>
#include <iostream>
#include <crtdbg.h>

int main()
{
	{
		int file = 0;
		std::cout << "Select the type of file:" << std::endl;
		std::cout << "1 - CSV" << std::endl;
		std::cout << "2 - HTML" << std::endl;
		std::cout << "Enter option: ";
		std::cin >> file;
		std::cin.ignore();
		if (file != 1 && file != 2)
			std::cout << "The option should be 1 or 2!" << std::endl;
		while (file != 1 && file != 2)
		{
			std::cout << "Enter option: ";
			std::cin >> file;
			if (file != 1 && file != 2)
				std::cout << "The option should be 1 or 2!" << std::endl;
		}
		Repository* userRepo = nullptr;
		if (file == 1)
			userRepo = new CSVRepository;
		else
			userRepo = new HTMLRepository;
		FileRepository adminRepo{};
		Service serv{ adminRepo,  *userRepo };
		Ui ui{ serv };
		ui.startProgram();
	}
	
	//_CrtDumpMemoryLeaks();

	return 0;
}
