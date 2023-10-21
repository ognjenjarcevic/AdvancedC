#include <stddef.h>
#include <errno.h>
#include <stdio.h>

#include "list.h"

int list_init(List* list, LIST_MEMB_T* headMemory, const LIST_POS_T lengthMaximum)
{
	if ((list == NULL) || (headMemory == NULL))
	{
		return -EINVAL;
	}
	// Max list size can't be 0
	if ((lengthMaximum < 1) || (lengthMaximum > LIST_LEN_SUPPORTED_MAXIMUM))
	{
		return -EDOM;
	}

	list->head = headMemory;
	list->lengthMaximum = lengthMaximum;
	list->lengthCurrent = 0;

	return 0;
}

int list_insert(List* const list, LIST_POS_T position, LIST_MEMB_T value)
{
	// List doesn't exist
	if (list == NULL)
	{
		return -EINVAL;
	}
	// Invalid position.
	if (position > list->lengthCurrent)
	{
		return -EDOM;
	}
	// TODO: insert value check
	// No more free memory.
	if (list->lengthCurrent == list->lengthMaximum)
	{
		return -ERANGE;
	}

	// Shift everything after position one place to the right to make space at head[position]
	// From the last element to the one currently at position
	for (LIST_POS_T i = list->lengthCurrent; i > position; i--)
	{
		list->head[i] = list->head[i-1];
	}
	list->head[position] = value;

	list->lengthCurrent++;
	return 0;
}

int list_delete(List* const list, LIST_POS_T position)
{
	// List doesn't exist.
	if (list == NULL)
	{
		return -EINVAL;
	}
	// List empty, nothing to delete
	if (list->lengthCurrent == 0)
	{
		return -EDOM;
	}
	// Invalid position.
	if (position > list->lengthCurrent - 1)
	{
		return -EDOM;
	}

	// Shift everything after position one place to the left
	// From the position to the last element.
	for (LIST_POS_T i = position; i < list->lengthCurrent - 1; i++)
	{
		list->head[i] = list->head[i+1];
	}

	list->lengthCurrent--;
	return 0;
}

int list_print(List* const list, char* outBuff, LIST_OUT_BUF_LEN_T outBuffSize)
{
	if ((list == NULL) || (outBuff == NULL))
	{
		return -EINVAL;
	}

	// If empty list: only space for hard coded message is needed
	if (list->lengthCurrent == 0)
	{
			if (outBuffSize < LIST_EMPTY_MESSAGE_SIZE)
			{
				return -EDOM;
			}

			snprintf(outBuff, LIST_EMPTY_MESSAGE_SIZE, "%s", LIST_EMPTY_MESSAGE);
			return 0;
	}

	// If list not empty:

	// Each list requires AT BARE MINIMUM (currElem*3) - 2 if all numbers are [0, 9]
	// = Digit, comma and space for each except for the last number
	// This is just a guard clause
	const LIST_OUT_BUF_LEN_T buffSizeMin = (list->lengthCurrent * 3) - 2;
	if (outBuffSize < buffSizeMin)
	{
		return -EDOM;
	}

	// i, charsPrinted, charsAvailable are declared in this scope to use after the loop
	LIST_POS_T i = 0;
	LIST_OUT_BUF_LEN_T charsAvailable = 0;
	LIST_OUT_BUF_LEN_T charsPrinted = 0;
	// Print all numbers except for the last one.
	// Note: edge cases for charsPrinted checks may need adjusting, due to shenanigans.
 	for (; i < list->lengthCurrent - 1; i++)
	{
		// 2 characters are needed for last character which is printed outside this loop
		// = 1 needs to be left for '\0' at the end, and 1 minimum for last number in the list
		charsAvailable = outBuffSize - charsPrinted - 2;

		// 3 characters are required to print the current character at minimum
		// 3 is minimum to print a number in "number, " format
		if (charsAvailable < 3)
		{
			return -ERANGE;
		}

		charsPrinted += snprintf(outBuff+charsPrinted, charsAvailable, "%"LIST_MEMB_PRI", ", list->head[i]);
	}

	charsAvailable = outBuffSize - charsPrinted;
	// No space for number and '\0'
	if (charsAvailable < 2)
	{
		return -ERANGE;
	}

	charsPrinted += snprintf(outBuff+charsPrinted, charsAvailable, "%"LIST_MEMB_PRI"", list->head[i]);

	//'\0' wasn't written to buffer, end of buffer reached
	if (charsPrinted == outBuffSize)
	{
		return -ERANGE;
	}

	return 0;
}
