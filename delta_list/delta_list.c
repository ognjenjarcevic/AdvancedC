#include "list.h"

#include <stddef.h>
#include <errno.h>

int deltaList_insert(List* const list, LIST_MEMB_T value)
{
	// Invalid list.
	if (list->head == NULL)
	{
		return -EINVAL;
	}
	// Can't insert a non-positive value into a delta encoded list. It doesn't make sense. Sanity check.
	if (value < 1)
	{
		return -EDOM;
	}

	// Goes through the list subtracting from it and seeking where to insert the element
	LIST_POS_T i = 0;
	while (i < list->lengthCurrent && list->head[i] < value)
	{
		value -= list->head[i];
		i++;
	}

	// This will happen if list is empty also, or the element to be inserted is bigger than all others
	if (i == list->lengthCurrent)
	{
		return list_insert(list, i, value);
	}

	// This isn't the last element, adjustments to the elem that is currently at that position will be required
	list->head[i] -= value;
	int retval = list_insert(list, i, value);

	return retval;
}
