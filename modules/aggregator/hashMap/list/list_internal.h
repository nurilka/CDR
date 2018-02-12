
#ifndef  __NON_API_LIST_H__
#define  __NON_API_LIST_H__

/** 
 *  @file list_internal.h
 *  @brief Node data type
 * 
 *  @details required both for List implementation and for Iterator implementation
 * 
 *  @author Nurit (H-45), Adv. C-3, 23.05.2017 
 * 
 *  @bug No known bugs.
 */ 
 
 

typedef struct Node Node;
struct 	Node 
{
	void*	m_data;			/*  */
	Node*	m_next;
	Node*	m_previous;
};

struct 	List
{
	size_t		m_magic;	/* list identifier check */
	Node 		m_head;		/* sentinel */
	Node		m_tail;					
};

/*------------------- NON-API List Functions ----------------------------*/
/** 
 * @brief Create new node
 *
 * @params _item : data to insert into the newly created node
 * @return pointer to Node type object
 */
Node*	NodeCreate	( void* _item );

/** 
 * @brief Insert newNode after the refNode
 *
 * @params _newNode : node to insert
 * @params _refNode : reference node to insert after
 * @return 
 */
void	NodeInsertAfter		( Node* _newNode, Node* _refNode );

/** 
 * @brief Insert newNode before the refNode
 *
 * @params _newNode : node to insert
 * @params _refNode : reference node to insert before
 * @return 
 */
void	NodeInsertBefore	( Node* _newNode, Node* _refNode );

/** 
 * @brief Remove the referenced node, return data 
 *
 * @params[in]  _removeNode : node to remove
 * @params[out] _pItem 		: placeholder for data
 * @return 
 */
void	NodeRemove		( Node* _removeNode, void** _pItem ); 




#endif /* #ifndef  __NON_API_LIST_H__ */
