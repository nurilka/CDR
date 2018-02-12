/** 
 *  @file list.c
 *  @brief Create a Generic Double Linked List data type
 * 
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap and store pointer to element provided by user.
 * 
 *  @author Nurit (H-45), Adv.C-3,  23.05.2017
 * 
 *  @bug No known bugs.
 */ 

#include 	<stddef.h>  /* size_t */
#include 	<stdlib.h>   /* malloc() */

#include 	"list.h"			/* List API */
#include	"list_internal.h"	/* List struct, Node struct */


#define     LIST_MAGIC		0xFEEDCAFE		/* List identifier */
#define 	ITR_NOT_VALID	0xDEADBEEF		/* Invalid iterator */

/* MACROs*/
#define 	IS_VALID_LIST(ptr)    ((ptr) && (ptr)->m_magic == LIST_MAGIC )
#define 	SET_VALID_LIST(ptr)   ((ptr)->m_magic = LIST_MAGIC )
#define 	SET_INVALID_LIST(ptr) ((ptr)->m_magic = LIST_MAGIC << 1 )

#define 	IS_HEAD(NODE) 		{(NODE)->m_previous == NULL ? TRUE : FALSE; }
#define 	IS_TAIL(NODE) 		{(NODE)->m_next == NULL ? TRUE : FALSE; }
#define		HEAD(NODE) 			((NODE)->m_head)
#define		TAIL(NODE)			((NODE)->m_tail)


typedef void (*_elementDestroy)(void* _item);



/*-------- NON-API List Functions - Prototypes in List Internal  ------------*/
/* Create new node  */
Node*	NodeCreate	( void* _item )
{
	Node* newNode;
	
	newNode = (Node*)malloc(sizeof(Node));
	if ( !newNode )
	{
		return NULL;
	}
	newNode->m_data 		= _item;
	newNode->m_next			= NULL;
	newNode->m_previous		= NULL;
	
	return  newNode;
}

/* Insert newNode after the refNode  */
void	NodeInsertAfter		( Node* _newNode, Node* _refNode )
{
	_refNode->m_next->m_previous 	= _newNode;
	_newNode->m_next				= _refNode->m_next;
	_refNode->m_next				= _newNode;
	_newNode->m_previous			= _refNode;
}

/* Insert newNode before the refNode  */
void	NodeInsertBefore	( Node* _newNode, Node* _refNode )
{	
	_refNode->m_previous->m_next 	= _newNode;
	_newNode->m_previous			= _refNode->m_previous;
	_refNode->m_previous			= _newNode;
	_newNode->m_next				= _refNode;
}

/* Remove the refNode  */
void	NodeRemove		( Node* _removeNode, void** _pItem )
{
	*_pItem = _removeNode->m_data;
	
	_removeNode->m_next->m_previous = _removeNode->m_previous;
	_removeNode->m_previous->m_next = _removeNode->m_next;	
} 

/*------------------- API Functions ----------------------------*/

/** Create list */
List* 	List_Create	(void)
{
	List* list;
	
	list = (List*)malloc(sizeof(List));
	if ( !list )
	{
		return NULL;
	}
	
	/* initialize the members */
	list->m_head.m_data			= (void*)ITR_NOT_VALID;
	list->m_head.m_next 		= &(list->m_tail);
	list->m_head.m_previous 	= NULL;
	
	list->m_tail.m_data			= (void*)ITR_NOT_VALID;
	list->m_tail.m_previous 	= &(list->m_head);
	list->m_tail.m_next 		= NULL;
	
	SET_VALID_LIST (list);
	
	return list;
}

/** Destroys the list completely. Optionally returns data using funct provided by user */
void 	List_Destroy	(List** _pList, _elementDestroy _doDestr)
{
	void*  data = NULL;
	Node*  tail = NULL;
	Node*  current = NULL;
	Node*  tmp	= NULL;
	
	if ( _pList && IS_VALID_LIST(*_pList) )
	{
		tail 	= &(TAIL(*_pList));
		current = HEAD(*_pList).m_next;
		
		while ( current != tail  )
		{
			tmp = current;
			current = current->m_next;
			NodeRemove	(tmp ,&data );
			if ( _doDestr ) 	/* gives O(n) of "if" checks */
			{
				_doDestr (data);
			}
			free (tmp);
		}
			
		SET_INVALID_LIST (*_pList);
		free (*_pList);
		*_pList = NULL;
	}
	
}	 
/** Add element to head of list, after head->next --avg O(1)-- */
List_Result List_PushHead	(List* _list, void* _item)
{
	Node* newNode;
	
	if( !IS_VALID_LIST (_list) )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if ( ! _item )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	newNode = NodeCreate (_item );
	if ( !newNode )
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	NodeInsertAfter ( newNode, &HEAD(_list) );
	
	return LIST_SUCCESS;
}

/** Add element to the list's tail --avg O(1)-- */
List_Result 	List_PushTail	(List* _list, void* _item)
{
	Node* newNode;
	
	if( !IS_VALID_LIST (_list) )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if ( ! _item )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	newNode = NodeCreate ( _item );
	if ( !newNode )
	{
		return LIST_ALLOCATION_ERROR;
	}

	NodeInsertBefore ( newNode, &TAIL(_list));
		
	return LIST_SUCCESS;
}

/** Remove element from list's head  --avg O(1)-- */
List_Result 	List_PopHead	(List* _list, void** _pItem)
{
	Node* removeNode;
	
	if ( !IS_VALID_LIST (_list) )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if ( !_pItem )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	
	/* set the node to remove */
	removeNode = HEAD(_list).m_next;
	if( removeNode == &TAIL(_list) )
	{
		return LIST_EMPTY;
	}

	NodeRemove		( removeNode, _pItem );
	free(removeNode);
	
	return LIST_SUCCESS;
}

/** Remove element from list's tail --avg O(1)-- */
List_Result List_PopTail(List* _list, void** _pItem)
{
	Node* removeNode;
	
	if ( !IS_VALID_LIST (_list) )
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if ( !_pItem )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
		
	/* set the node to remove */
	removeNode = TAIL(_list).m_previous;
	if( removeNode == &HEAD(_list) )
	{
		return LIST_EMPTY;
	}

	NodeRemove		( removeNode,  _pItem );
	free (removeNode);
	
	return LIST_SUCCESS;
}

/** Get number of elements in the list */
static size_t	ListCountRecursive	( Node*  _countPosition )
{
	if ( NULL == _countPosition->m_next )
	{
		return 0;
	}
	return   ListCountRecursive	( _countPosition->m_next ) + 1;
} 
/*-------------------------*/
size_t 	List_Size	(const List* _list)
{
	Node* 	countPosition;
	
	if ( !IS_VALID_LIST (_list)  )
	{
		return 0;
	}
	countPosition = HEAD(_list).m_next;	

	return 	ListCountRecursive	( countPosition );
}






