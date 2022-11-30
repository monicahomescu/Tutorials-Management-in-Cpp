#pragma once
#include "Tutorial.h"
#include "Comparator.h"

class ComparatorAscendingByTitle : public Comparator<Tutorial>
{
public:
	bool compare(Tutorial t1, Tutorial t2);
};
