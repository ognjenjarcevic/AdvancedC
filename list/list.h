/**
 * @file list.h
 * @brief Linked list module, abstracts linked list for use on embedded systems with limited resources
 *
 * @author Ognjen Jarcevic
 *
 * @see Refer to https://everything2.com/title/delta+list for information on delta encoding lists
*/


#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <inttypes.h>

////////////////////////// MODULE SETTINGS ///////////////////////////////////////
/// These are platform and use-case specific settings. Which ensure compatibility with other compilers and platforms
/// Adjusting these settings affects list member sizes, their data ranges
/// and consequently resources and time required for all function executions
/// When changing some TYPES, corresponding DERIVATIVES ***MUST*** also be changed by hand

//////////////////////// TYPES ////////////////////////////////

/** @brief    List member values are of this type, should be signed number
 *  @details  Signed numbers should be used in order to ensure compatibility with some list types that use subtraction
 *		      For example delta lists which expand on this module.
 */
#define LIST_MEMB_T int16_t

/** @brief List length and positions are of this type, should be unsigned number, can also be signed number type
 *  @details Unsigned types are recommended, or extra precausion is needed when using signed types.
 *			 This is due to guard clauses checking if the positions are negative being absent from the code.
 *         	 For example inserting new element at position -4 produces unexpected behaviour.
*/
#define LIST_POS_T uint16_t

/** @brief Output buffer used to print list is of this size, cshould be unsigned number, can also be signed number type
 *  @note  Optimal type should be calculated manually as it depends on list's data range and length.
*/
#define LIST_OUT_BUF_LEN_T uint32_t


//////////////////////// DERIVATIVES //////////////////////////

/** @brief Corresponding print format specifier for list member */
#define LIST_MEMB_PRI PRId16

/** @brief Corresponding scan format specifier for list member */
#define LIST_MEMB_SCN SCNd16

/** @brief Maximum supported length for all lists, value must fit inside the list position type */
#define LIST_LEN_SUPPORTED_MAXIMUM ((LIST_POS_T)1024)

/** @brief Text message that is to be printed inside the output buffer when the list is empty
 *  @details Must fit inside the output buffer list type
 */
#define LIST_EMPTY_MESSAGE "empty"

/** @brief  List empty message exact length */
#define LIST_EMPTY_MESSAGE_SIZE (sizeof(LIST_EMPTY_MESSAGE))

//////////////////////////////////////////////////////////////////////////////////

/** @brief Structure that is used for working with lists */
typedef struct ListStruct
{
	/** @brief Address of the first element of the list, commonly called list head */
	LIST_MEMB_T* head;

	/** @brief Number of elements currently inside the list */
	LIST_POS_T lengthCurrent;

	/** @brief Maximum number of members that this list can, set during list initialization, don't modify manually */
	LIST_POS_T lengthMaximum;
} List;

/**
 * @brief Initializes the list, making it ready for use
 *
 * @note This list operation should be done before any others
 *		 and its call is a prerequisite for all further operations performed on this list
 *
 * @param[out] list 	  list that is to be initialized
 * @param[in]  headMemory pointer to the beginning of a memory block that is to be used for storing the list,
 * 						  head of the list will be stored at this location
 * @param[in]  lengthMaximum maximum length of this list
 * 						     must be less or equal to the defined maximum supported length for all lists
 *
 * @retval 0 on success, or an error code
*/
int list_init(List* list, LIST_MEMB_T* headMemory, const LIST_POS_T lengthMaximum);
/**
 * @brief Inserts an element with `value` into the `list` at `position`
 * 		  If there is an element already located at the position, new element will be inserted before it.
 *
 * @details This isn't well optimized for execution speed, because it shifts all elements after `position`
 * 			one slot to the right, which is simple, but not optimal or good solution.
 *
 * @param[in] list target list
 * @param[in] position desired position of the new element
 * @param[in] value value to be inserted into the list
 *
 * @retval 0 on success, or an error code
*/
int list_insert(List* const list, LIST_POS_T position, LIST_MEMB_T value);

/**
 * @brief Deletes an element with from the `list` at `position`.
 *
 * @param[in] list target list
 * @param[in] position position of the element that is to be deleted
 *
 * @details This isn't well optimized for execution speed, because it shifts all elements after `position`
 * 			one slot to the left, which is simple, but not optimal or good solution.
 *
 * @retval 0 on success, or an error code
*/
int list_delete(List* const list, LIST_POS_T position);

/**
 * @brief Prints the entire list, or an message indicating that the list is empty
 *
 * @param[in] list target list
 * @param[out] outBuff char buffer that will contain textual representation of the target list
 * @param[in] outBuffSize size of the output buffer, indicating maximum number of characters that can be used
 *
 * @retval 0 on success, or an error code
*/
int list_print(List* const list, char* outBuff, LIST_OUT_BUF_LEN_T outBuffSize);

#endif // LIST_H
