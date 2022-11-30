#include "ComparatorAscendingByTitle.h"

bool ComparatorAscendingByTitle::compare(Tutorial t1, Tutorial t2)
{
	if (t1.getTitle() <= t2.getTitle())
		return true;
	return false;
}
