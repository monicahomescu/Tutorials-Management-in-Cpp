#include "ComparatorDescendingByLikes.h"

bool ComparatorDescendingByLikes::compare(Tutorial t1, Tutorial t2)
{
	if (t1.getLikes() >= t2.getLikes())
		return true;
	return false;
}
