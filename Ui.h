#pragma once
#include "Service.h"
#include "Exceptions.h"
#include "Comparator.h"
#include "ComparatorAscendingByTitle.h"
#include "ComparatorDescendingByLikes.h"

class Ui
{
private:
	Service& serv;
	InputValidator val;

public:
	Ui(Service& s) : serv(s) {}

	void addUi();

	void deleteUi();

	void updateUi();

	void listUi();

	void sortUi();

	void menuAdministrator();

	void administratorMode();

	void menuPresenter();

	void presenterMode();

	void menuWlist();

	void wlistMode();

	void menuUser();

	void userMode();

	void startProgram();
};
