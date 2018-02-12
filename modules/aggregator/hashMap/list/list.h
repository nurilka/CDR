#ifndef __LIST_H__
#define __LIST_H__

/** 
 *  @file list.h
 *  @brief Create a Generic Double Linked List data type
 * 
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap. Nodes store pointer to the data provided by user
 * 
 *  @author Author Nurit (H-45), Adv. C-3, 23.05.2017
 * 
 *  @bug No known bugs.
 */ 

#include 	<stddef.h>  		/* size_t */

typedef struct List List;

typedef enum List_Result 
{
	LIST_SUCCESS,
	LIST_UNINITIALIZED_ERROR,	/** Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,		/** Node allocation failed due to heap error   */
	LIST_NULL_ELEMENT_ERROR,	/** _item is NULL */
	LIST_EMPTY					/** No nodes in list */

} List_Result;

/** 
 * @brief Create a list
 * 
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* List_Create	(void);

/** 
 * @brief Destroy list
 * @details Destroys the list completely 
 *          optionally destroys data using user provided function
 *
 * @params[in] _pList : A pointer to previously created List returned via ListCreate
 *					   on completion *_pList will be null
 * @params[in] _elementDestroy : A function pointer to be used to destroy data inserted into the list
 *             or a null if no such destroy is required
 */
void List_Destroy	(List** _pList, void (*_elementDestroy)(void* _item));

/** 
 * @brief Add element to head of list
 * @details time complexity: O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
List_Result List_PushHead	(List* _list, void* _item);

/** 
 * @brief Add element to the list's tail
 * @details time complexity O(1).
 *
 * @params _list 
 * @params _item
 * @returns  error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure 
 */
List_Result List_PushTail	(List* _list, void* _item);

/** @brief Remove element from list's head
 *  @details if successfull, stores a pointer to the removed item in _item
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL
 * @retval LIST_EMPTY on list with head == tail
 */
List_Result List_PopHead	(List* _list, void** _pItem);

/** @brief Remove element from list's tail
 *  @details time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL
 * @retval LIST_EMPTY on list with head == tail 
 */
List_Result List_PopTail	(List* _list, void** _pItem);

/** @brief Get number of elements in the list
 * Average time complexity O(n).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 *
 * @returns size_t 
 * @retval 0 on error or empty list
 * @retval 
 */
size_t 	List_Size	(const List* _list);


#endif /* __LIST_H__ */
