/**
 * @file delta_list.h
 * @brief Delta encoding list module, built on top of the list module.
 *
 * @note Delta_list type abstraction from regular list not implemented as it would only produce bloat.
 * 		 - It wouldn't add any new functionalities
 * 		 - It would greatly increase the maintenance work.
 * 		 - It would possibly make using list module functions more difficult.
 *
 * 		 Refer to the list module for type definitions.
 * 		 Use guide:
 * 			0. Adjust list module settings
 * 			1. Use list initialization from the list module
 * 			2. Use rest of the list functions freely. This is an extension implementing the delta insertion algorithm.
 * 			   using list's insert and delete functions without calculating operations manually can
 * 			   change the timeline context inside the delta list.
 *
 * @author Ognjen Jarcevic
 *
 * @see Refer to https://everything2.com/title/delta+list for information on delta encoding lists
*/

#ifndef DELTA_LIST_H
#define DELTA_LIST_H

#include "list.h"


/**
 * @brief Inserts the `value` to the delta `list`, at the position determined by the delta encoding algorithm
 *
 * @details Example:
 *		Insert a, with key 10 into an empty delta list:
 *
 *			|a:10|
 *
 *		Insert b, with key 15:
 *
 *			|a:10| --> |b:5 |
 *
 *		(once a's 10ms delay has expired, only 5ms left until b expires, a = 10, b = 10+5 = 15)
 *
 *		Insert c, with key 12:
 *
 *			|a:10| --> |c:2| --> |b:3 |
 *
 *		(a = 10, c = 10+2 = 12, b = 10+2+3 = 15)
 *
 *		Insert d, with key 22:
 *
 *			|a:10| --> |c:2 | --> |b:3 | --> |d:7 |
 *
 *		(a = 10, c = 10+2 = 12, b = 10+2+3 = 15, d = 10+2+3+7 = 22)
 *
 * @param[in] list target list
 * @param[in] value value to be inserted into the list
 *
 * @retval 0 on success, or an error code
*/
int deltaList_insert(List* const list, LIST_MEMB_T value);

#endif //DELTA_LIST_H
