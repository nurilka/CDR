/** 
 *  @file list_itr.c
 *  @brief  List Iterator API functions
 * 
 *  @details 
 * 
 *  @author Nurit (H-45), Adv.C-3,  23.05.2017
 * 
 *  @bug No known bugs.
 */ 

#include 	<stdlib.h>			/* free() */

#include 	"list.h"			/* List API */
#include	"list_internal.h"	/* Node struct */

#include 	"list_itr.h"		/* Iterator API */
#include 	"list_functions.h"	/* Iterator functions */


#define     LIST_MAGIC		0xFEEDCAFE		/* List identifier */
#define 	ITR_NOT_VALID	0xDEADBEEF		/* Invalid iterator */

/* MACROs*/
#define 	IS_VALID_LIST(ptr)    ((ptr) && ((ptr)->m_magic == LIST_MAGIC) )

#define		HEAD(NODE) 			((NODE)->m_head)
#define		TAIL(NODE)			((NODE)->m_tail)
#define		TAILPTR(NODE)		(&(NODE)->m_tail)


/*---------------------- List Iterator API  ---------------------------*/

/** Get itertator to the list's beginning */
ListItr ListItr_Begin	(const List* _list)
{
	return ( IS_VALID_LIST (_list) ) ? HEAD(_list).m_next : (void*)ITR_NOT_VALID;
}

/**  Get itertator to the list end */
ListItr ListItr_End		(const List* _list)
{
	return ( IS_VALID_LIST (_list) ) ? (void*)TAILPTR(_list) : (void*)ITR_NOT_VALID;
}

/** retruns none zero if _a and _b iterators refer to same node */
int ListItr_Equals		(const ListItr _a, const ListItr _b)
{
	return (_a == _b) ? rand()%100 + 1 : 0;
}

/** Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItr_Next	(ListItr _itr)
{
	Node*	tmpItr;
	
	tmpItr = (Node*)_itr;
	return ( tmpItr->m_next != NULL ) ? (void*)tmpItr->m_next : _itr;
}

/** Get itertator to the previous element */
ListItr ListItr_Prev	(ListItr _itr)
{
	Node*	tmpItr;
	
	tmpItr = (Node*)_itr;
	return ( (void*)ITR_NOT_VALID != tmpItr->m_previous->m_data) ? (void*)tmpItr->m_previous : _itr;
}

/** Get data from the list node the iterator is pointing to  */
void* 	ListItr_Get	(ListItr _itr)
{
	Node*	tmpItr;
	
	tmpItr = (Node*)_itr;
	return ( !tmpItr->m_next ) ? NULL : tmpItr->m_data;
}

/** Set data at the node where the iterator is pointing at return the old data*/
void* 	ListItr_Set	(ListItr _itr, void* _element)
{
	Node*	tmpItr;
	void*	retVal;
	
	tmpItr = (Node*)_itr;
	
	if ( !tmpItr->m_next  || ! _element)
	{
		return NULL;
	} 
	retVal 			= tmpItr->m_data;
	tmpItr->m_data 	= _element;
	
	return retVal;
}

/** Inserts a new node before node the iterator is pointing at */
ListItr ListItr_InsertBefore	(ListItr _itr, void* _element)
{
	Node*	refNode;
	Node*	newNode;
	
	refNode = (Node*)_itr;
	
	if ( ! _element )
	{
		return NULL;
	} 
	newNode = NodeCreate (_element);
	if ( !newNode )
	{
		return NULL;
	}
	
	NodeInsertBefore ( newNode, refNode );
	return newNode;
}

/** Removes the node the iterator is pointing at, return user data 
	at the end the iterator points to a place in heap that is not usable anymore */
void* 	ListItr_Remove	(ListItr _itr)
{
	Node*	removeNode;
	void*   retVal;
		
	removeNode = (Node*)_itr;

	NodeRemove		( removeNode, &retVal );
	free(removeNode);
	
	return retVal;
}

/*---------------------- List Iterator Functions  ---------------------------*/
/** 
 * @brief execute an action for all elements in a half open range
 * @details call -action for each element in the range [begin..end)
 * iteration will stop if Action function returns 0 for an element
 */
ListItr ListItr_ForEach (ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	int 	res = -1;
	ListItr current = NULL;
	
	if ( !_begin || !_end || !_action || ! _context )
	{
		return NULL;
	} 
	
	current = _begin;
	while ( ! ListItr_Equals ( current,  _end) )
	{
		res = _action ( ListItr_Get (current), _context);
		if ( !res )
		{
			break;
		}
		current = ListItr_Next (current);
	}
	
	return _begin;
}

/** 
 * @brief Finds the first element in a range satsifying a predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return an iterator pointing to the first node with data found or to _end if not
 */
ListItr ListItr_FindFirst (ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	int 	res = 0;
	ListItr current = NULL;
	
	if ( !_begin || !_end || !_predicate || ! _context )
	{
		return NULL;
	} 
	
	current = _begin;
	while ( ! ListItr_Equals ( current,  _end) )
	{
		res = _predicate (ListItr_Get (current), _context);
		if ( res )
		{
			return current;
		}
		current = ListItr_Next (current);
	}
	
	return _end;
}

/** 
 * @brief count elements in a sub list satisfying predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return count of all elements e where _predicate(e, _context) != 0
 */
size_t ListItr_CountIf (ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	int 	res = 0;
	size_t  counter = 0;
	ListItr current = NULL;
	
	if ( !_begin || !_end || !_predicate || ! _context )
	{
		return 0;
	} 
	
	current = _begin;
	while ( ! ListItr_Equals ( current,  _end) )
	{
		res = _predicate (ListItr_Get (current), _context);
		if ( !res )
		{
			++counter;
		}
		current = ListItr_Next (current);
	}
	
	return counter;
}

/** 
 * @brief Sorts a sublist in place using the bubble sort algorithm
 * Complexity O(n^2)
 *
 * @params _begin : Iterator to sublist start
 * @params _end : Iterator to sublist end
 * @params _less : less compare function
 * 
 */
void ListItr_Sort (ListItr _begin, ListItr _end, LessFunction _less)
{
	int 		sorted = 0;
	int 		res = 0;
	void*		currentData = NULL;
	void*		nextData = NULL;
	ListItr		current, next, last;

	
	if ( !_begin || !_end || !_less )
	{
		return;
	} 
	
	current = _begin;
	last 	= _end;

	while (!sorted)
	{
		sorted = 1;
		while ( ! ListItr_Equals ( current,  last) )
		{
			next 		= ListItr_Next (current);
			
			currentData = ListItr_Get(current);
			nextData 	= ListItr_Get(next);
			
			res = _less ( nextData, currentData );
			if ( res )
			{
				ListItr_Set(current, nextData);
				ListItr_Set(next, currentData);
				sorted = 0;
			}
			current = ListItr_Next (current);
			last 	= ListItr_Prev (last);
		}
	}
	
	return;
}

/** 
 * @brief Splice all element from [_begin.._end) into _dst
 * @details remove all elements from the half open range [_begin.._end)
 * and insert them before _dest
 * O(n)
 *
 * @warning The function assumes that : 
 *  _begin and _end are in the correct order and on the same list
 *  _dset is not between them
 * Otherwise behavior is undefined
 * all three iterators can belong to same list
 */
ListItr ListItr_Splice (ListItr _dest, ListItr _begin, ListItr _end)
{
	void*		currentData = NULL;
	ListItr		current, prev, first;

	
	first	 = _begin;
	current	 = ListItr_Prev (_end);
	
	while ( ! ListItr_Equals ( current,  first) )
	{
		prev = ListItr_Prev (current);
		currentData = ListItr_Remove ( current);	
		_dest = ListItr_InsertBefore ( _dest, currentData);
		current = prev;
	}
	return _dest;
}

/** 
 * @brief Merges two given sub lists into destination 
 * @details Merge elements from two sub lists defined by [_firstbegin.._firstEnd)
 * and [_secondBegin.._secondEnd) in optionaly sorted order using _less function.
 * merged elements will be inserted before _destBegin
 * if a _less function is provided then merge will be sorted
 * 
 * @warning this will removes all merged items from source ranges.
 * O(?)
 *  
 */
ListItr ListItr_Merge (ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less);
			
/** 
 * @brief Removes a sublist [_begin.._end) from a list and creates a new list
 * with all removed items.
 * O(?)
 *
 */
List* ListItr_Cut (ListItr _begin, ListItr _end);


/** 
 * @brief Removes all duplicate elements from a sorted sublist [_begin.._end) 
 * and rertun a new list with all removed items.
 * O(?)
 * post condition: [_begin.._end) contains only unique elements
 */
List* ListItr_Unique (ListItr _begin, ListItr _end, EqualsFunction _equals);



