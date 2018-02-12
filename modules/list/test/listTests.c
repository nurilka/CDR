/** 
 *  @file listTests.c
 *  @brief Test the List API, Iterator API and Iterator functions
 * 
 *  @details Tests 
 * 
 *  @author Nurit (H-45), Adv.C-3,  23.05.2017
 * 
 *  @bug No known bugs.
 */


#include 	<stddef.h>			/* size_t */
#include 	<stdlib.h>			/* rand (), malloc */
#include 	<time.h>			/* time() */

#include 	"list.h"
#include 	"list_itr.h"		/* Iterator API */
#include 	"list_functions.h"	/* Iterator functions */
#include 	"listTests.h"		/* tests header */


#define 	SIZE_SMALL	10
#define 	NUM_OF_ITEMS_TO_ADD 200


typedef struct 
{
	int m_num1;
	int m_num2;
	int m_num3;
} Nums;


/*~~~~~~~~~~~~~~~~~ Itr Functions for tests  ~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Predicate function returns a none zero value if predicate holds for element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return none zero if predicate holds
 */
int IfHolds (void* _element, void* _context)
{
}

/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
int DoSmth (void* _element, void* _context)
{
}

/** 
 * @brief Action function to check if a < b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a < _b
 */
int FirstIsSmaller (void* _a, void* _b)
{
}

/** 
 * @brief Action function to check if a == b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a == _b
 */
int AreEqual (void* _a, void* _b)
{
}



/*~~~~~~~~~~~~~~~~~ Test List Create ~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test List Create with input OK
 * 
 * @returns 
 * @retval FAIL	-  the list is NULL
 * @retval PASS	-  the list is created 
 */

int  TestListCreateInputOK ()
{
	List* 	list;
		
	list = List_Create ();
	if ( NULL == list)
	{
		return FAIL;
	}

	List_Destroy(&list, NULL);
	return PASS;
} 

/*~~~~~~~~~~~~~~~~~ Test Valid List ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test All functions with _list == NULL
 * 
 * @returns 
 * @retval FAIL	-  if anything but LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  if LIST_UNINITIALIZED_ERROR
 */
int  TestListInputNULL4All ()
{
	List_Result 	err  	= LIST_SUCCESS;
	int  			data 	= 100;
	int*			pData 	= NULL;
	size_t			errNum 	= 0XFAABCAFE;
	
	err =    List_PushHead     (NULL, (void*)&data);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PushTail     (NULL, (void*)&data);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PopHead     (NULL, (void*)&pData);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PopTail     (NULL, (void*)&pData);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	errNum =    List_Size     (NULL);
	if ( 0 != errNum )
	{
		return FAIL;
	}

	return PASS;
} 
/** 
 * @brief Test All functions with pointer not to list
 * 
 * @returns 
 * @retval FAIL	-  if anything but LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  if LIST_UNINITIALIZED_ERROR
 */
int  TestListInputNotList4All ()
{
	List_Result 	err  	= LIST_SUCCESS;
	int  			data 	= 100;
	int*			pData 	= &data;
	size_t			errNum 	= 0XFAABCAFE;
	
	err =    List_PushHead     ((List*)pData, (void*)&data);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PushTail     ((List*)pData, (void*)&data);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PopHead     ((List*)pData, (void*)&pData);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    List_PopTail     ((List*)pData, (void*)&pData);
	if ( LIST_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	errNum =    List_Size     ((List*)pData);
	if ( 0 != errNum )
	{
		return FAIL;
	}

	return PASS;
} 

/*~~~~~~~~~~~~~~~~~ Test List_Destroy ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test Destroy sanity, call twice
 * 
 * @returns 
 * @retval PASS	
 */
int  TestListDestroySanity ()
{
	List* 			list 	= NULL	;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	List_Destroy(&list, NULL);
	
	return PASS;
}

/*~~~~~~~~~~~~~~~~~ Test ListPushHead ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPushHead Item NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_NULL_ELEMENT_ERROR
 * @retval PASS	-  LIST_NULL_ELEMENT_ERROR
 */
int  TestListPushHeadItemNULL ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( !list )
	{
		return FAIL;
	}
			
	err = 	List_PushHead ( list, NULL );
	if ( LIST_NULL_ELEMENT_ERROR != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
}

/** 
 * @brief Test ListPushHead Input OK one value
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushHeadInputOK ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData 	= &data;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	data = rand() % 50 + 999;		
	err = 	List_PushHead ( list, (void*)&data );
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
} 

/** 
 * @brief Test ListPushHead Inputs OK  multiple entries
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushHeadMultiple ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushHead ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	List_Destroy(&list, NULL);
	return PASS;
} 

/*~~~~~~~~~~~~~~~~~ Test ListPushTail ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPushTail Item NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_NULL_ELEMENT_ERROR
 * @retval PASS	-  LIST_NULL_ELEMENT_ERROR
 */
int  TestListPushTailItemNULL ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( !list )
	{
		return FAIL;
	}
			
	err = 	List_PushTail ( list, NULL );
	if ( LIST_NULL_ELEMENT_ERROR != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
}

/** 
 * @brief Test ListPushTail Input OK one value
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushTailInputOK ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData 	= &data;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	data = rand() % 50 + 999;		
	err = 	List_PushTail ( list, (void*)&data );
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
}

/** 
 * @brief Test ListPushTail Inputs OK  multiple entries
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushTailMultiple ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushTail ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	List_Destroy(&list, NULL);
	return PASS;
}

/*~~~~~~~~~~~~~~~~~ Test ListPopHead ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPopHead Input placeholder NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  LIST_UNINITIALIZED_ERROR
 */
int  TestPopHeadPlaceHolderNULL ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( !list )
	{
		return FAIL;
	}
	err =    List_PopHead  ( list, NULL );
	List_Destroy(&list, NULL);
		
	return ( LIST_NULL_ELEMENT_ERROR != err ) ? FAIL : PASS;
}

/** 
 * @brief Test ListPopHead with empty list
 * 
 * @returns 
 * @retval FAIL	-  not LIST_EMPTY
 * @retval PASS	-  LIST_EMPTY
 */
int  TestPopHeadListEmpty ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData	= NULL;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	pData 	= &data;
	err =    List_PopHead  ( list, (void*)&pData );
	List_Destroy(&list, NULL);
		
	if ( LIST_EMPTY != err )
	{
		return FAIL;
	}
	
	return PASS;
} 

/** 
 * @brief Test ListPopHead one item Input OK
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPopHeadInputOK ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData 	= NULL;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	

	srand((unsigned int)time(NULL));
	data = rand() % 50 + 999;		
	err = 	List_PushHead ( list, (void*)&data );
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	err = List_PopHead (list, (void*)&pData);
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	if ( pData != &(data) )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
} 

/** 
 * @brief Test ListPopHead Inputs OK  multiple entries added from Head
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopHeadMultAddedFromHead ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushHead ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	for ( i = (SIZE_SMALL -1); i < 0; --i)
	{                              
		err = 	List_PopHead (list, (void*)&pData);
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
		if ( pData != &(data[i]) )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	
	List_Destroy(&list, NULL);
	return PASS;
} 

/** 
 * @brief Test ListPopHead Inputs OK  multiple entries added from Tail
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopHeadMultipleFromTail ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushTail ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PopHead (list, (void*)&pData);
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
		if ( pData != &(data[i]) )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	List_Destroy(&list, NULL);
	return PASS;
} 
 

/*------------ List_PopTail Test -------------*/
/** 
 * @brief Test ListPopTail Input placeholder NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  LIST_UNINITIALIZED_ERROR
 */
int  TestPopTailPlaceHolderNULL ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( !list )
	{
		return FAIL;
	}
	err =    List_PopTail  ( list, NULL );
	List_Destroy(&list, NULL);
		
	return ( LIST_NULL_ELEMENT_ERROR != err ) ? FAIL : PASS;
}

/** 
 * @brief Test ListPopTail with empty list
 * 
 * @returns 
 * @retval FAIL	-  not LIST_EMPTY
 * @retval PASS	-  LIST_EMPTY
 */
int  TestPopTailListEmpty ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData 	= &data;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	err =    List_PopTail  ( list, (void*)&pData );
	List_Destroy(&list, NULL);
		
	if ( LIST_EMPTY != err )
	{
		return FAIL;
	}
	
	return PASS;
} 

/** 
 * @brief Test ListPopTail one item Input OK
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPopTailInputOK ()
{
	List_Result 	err  	= LIST_SUCCESS;
	List* 			list 	= NULL	;
	int  			data 	= 100;
	int*			pData 	= &data;
	int 			flag 	= PASS;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	data = rand() % 50 + 999;		
	err = 	List_PushTail ( list, (void*)&data );
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	err = List_PopTail (list, (void*)&pData);
	if ( LIST_SUCCESS != err )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	if ( pData != &(data) )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);
	return PASS;
} 

/** 
 * @brief Test ListPopTail Inputs OK  multiple entries added from Head
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopTailMultAddedFromHead ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushHead ( list,(void*) &data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;;
		}
	}
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PopTail (list, (void*)&pData);
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
		if ( pData != &(data[i]) )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	List_Destroy(&list, NULL);
	return PASS;
} 

/** 
 * @brief Test ListPopTail Inputs OK  multiple entries added from Tail
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopTailMultipleFromTail ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushTail ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	for ( i = (SIZE_SMALL - 1); i < 0; --i)
	{                              
		err = 	List_PopTail (list, (void*)&pData);
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
		if ( pData != &(data[i]) )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	List_Destroy(&list, NULL);
	return PASS;
} 


/*------------ List_Size Test -------------*/
/** 
 * @brief Test List_Size list empty
 * 
 * @returns 
 * @retval FAIL	-  returned non 0
 * @retval PASS	-  returned 0
 */
int  TestListSizeEmptyList ()
{
	List* 		list;
	size_t 		err;
	
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	err = List_Size (list);
	List_Destroy(&list, NULL);	
	
	if ( 0 != err )
	{
		return FAIL;
	}
	return PASS;
} 

/** 
 * @brief Test List_Size After Push
 * 
 * @returns 
 * @retval FAIL	-  times push on empty != List size
 * @retval PASS	-  times push on empty == List size
 */
int  TestListSizeAfterPush ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushTail ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;;
		}
	}

	if ( SIZE_SMALL != List_Size (list) )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);	
	return PASS;
}


/** 
 * @brief Test List_Size After Pop
 * 
 * @returns 
 * @retval FAIL	-  times Push then Pop != List size
 * @retval PASS	-  times Push then Pop == List size
 */
int  TestListSizeAfterPop ()
{
	List_Result err  		= LIST_SUCCESS;
	List* 		list 		= NULL;
	int*		pData 		= NULL;
	int 		flag 		= PASS;
	int 		i 			= 0;
	int  		data[SIZE_SMALL] 	= {0};
		
	list = 	List_Create	();
	if ( NULL == list )
	{
		return FAIL;
	}
	
	srand((unsigned int)time(NULL));
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{ 
		data[i] = (char)(rand() % 27 + 65);
	}
	
	for ( i = 0; i < (SIZE_SMALL); ++i)
	{                              
		err = 	List_PushTail ( list, (void*)&data[i] );
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}
	for ( i = 0; i < (SIZE_SMALL - 3); ++i)
	{                              
		err = 	List_PopTail (list, (void*)&pData);
		if ( LIST_SUCCESS != err )
		{
			List_Destroy(&list, NULL);
			return FAIL;
		}
	}

	if ( (SIZE_SMALL - (SIZE_SMALL-3)) != List_Size (list) )
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	
	List_Destroy(&list, NULL);	
	return PASS;
} 

/*********************** TESTS SHANI **********************************/
int ListCreate()
{
	List* list;
	list=List_Create();
	if(list==NULL)
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	List_Destroy(&list, NULL);
	return PASS;
}

/*------------------------------------------*/
int DoubleDestroy()
{
	List* list;
	list=List_Create();
	if(list==NULL)
	{
		return FAIL;
	}
	List_Destroy ( &list, NULL);
	List_Destroy ( &list, NULL);
	return PASS;
}

/*------------------------------------------*/
int ListPushHeadWithNull()
{
	List_Result err;
	int num=6;
	
	err=List_PushHead(NULL,(void*) &num);
	if(err==LIST_UNINITIALIZED_ERROR)
	{
		return PASS;
	}
	return FAIL;
}

/*------------------------------------------*/
int ListPushHeadStructNotList()
{
	List_Result err = LIST_SUCCESS;
	Nums nums;
	int num=6;
	
	nums.m_num1 = 10;
	nums.m_num2 = 20;
	nums.m_num3 = 30;

	err=List_PushHead((List*) &nums,(void*) &num);
	if(err==LIST_UNINITIALIZED_ERROR)
	{
		return PASS;
	}
	return FAIL;
}

/*------------------------------------------*/
int ListPushHeadNullItem()
{
	List_Result err;
	List* list;
	
	list=List_Create();
	if(list==NULL)
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	err=List_PushHead(list, NULL);
	if(err==LIST_NULL_ELEMENT_ERROR)
	{
		List_Destroy(&list, NULL);
		return PASS;
	}
	List_Destroy(&list, NULL);
	return FAIL;
}

/*------------------------------------------*/
int ListPushHeadDeleteTailOneItem()
{
	List_Result err;
	List* list;
	int item=7;
	int *itemPtr;
	
	list=List_Create();
	if(list==NULL)
	{
		List_Destroy(&list, NULL);
		return FAIL;
	}
	err=List_PushHead(list, &item);
	err=List_PopTail(list, (void**) &itemPtr);
	if(err == LIST_SUCCESS && *itemPtr == item )
	{
		List_Destroy(&list, NULL);
		return PASS;
	}
	List_Destroy(&list, NULL);
	return FAIL;
}

/*------------------------------------------*/
int ListPushHeadPopTail()
{	

	int i;
	List* list=NULL;
	int item[NUM_OF_ITEMS_TO_ADD];
	int *itemPtr;

	
	list=List_Create();
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		item[i] = rand() %1000 ;
		List_PushHead (list , (void*) &item[i] ); 
	}
	
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD ; ++i )
	{
		List_PopTail (list ,(void*) &itemPtr ); 
		if(*itemPtr!=item[i])
		{
			List_Destroy ( &list, NULL);
			return FAIL;
		}
	}	
	List_Destroy ( &list, NULL);
	return PASS;
}

/*------------------------------------------*/
int ListPushHeadPopHead()
{	

	int i;
	List* list=NULL;
	int item[NUM_OF_ITEMS_TO_ADD];
	int *itemPtr;

	
	list=List_Create();
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		item[i] = rand() %1000 ;
		List_PushHead (list , (void*) &item[i] ); 
	}
	
	for(  i=(NUM_OF_ITEMS_TO_ADD-1) ; i >= 0; --i )
	{
		List_PopHead (list ,(void*) &itemPtr ); 
		if(*itemPtr!=item[i])
		{
		List_Destroy ( &list, NULL);
			return FAIL;
		}
	}	
	List_Destroy ( &list, NULL);
	return PASS;
}

/*---------------------ITR TESTS-------------------*/
int ListItrGet()
{	

	List* list=NULL;
	int item=7;

	ListItr end;
	ListItr begin;
	
	list=List_Create();
	
	List_PushHead (list , (void*) &item ); 
	begin = ListItr_Begin(list);
	end = ListItr_End(list);
	end = ListItr_Prev(end);
	if(ListItr_Equals(begin , end) == 1)
	{
		List_Destroy ( &list, NULL);
		return PASS;
	}
	List_Destroy ( &list, NULL);
	return FAIL;	
}

/*------------------------------------------*/
int ListItrBeginAndGet()
{	
	int i;
	List* list=NULL;
	int item[NUM_OF_ITEMS_TO_ADD];
	int *itemPtr={0};
	ListItr begin;

	
	list=List_Create();
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		item[i] = rand() %1000 ;
		List_PushHead (list , (void*) &item[i] ); 
	}
	
	begin = ListItr_Begin(list);
	itemPtr = ListItr_Get(begin);

	if(*itemPtr!=item[NUM_OF_ITEMS_TO_ADD-1])
	{
		List_Destroy ( &list, NULL);
		return FAIL;
	}
	
	List_Destroy ( &list, NULL);
	return PASS;
}

/*------------------------------------------*/
int ListItrEndAndGet()
{	

	int i;
	List* list=NULL;
	int item[NUM_OF_ITEMS_TO_ADD];
	int *itemPtr={0};
	ListItr end;

	
	list=List_Create();
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		item[i] = rand() %1000 ;
		List_PushHead (list , (void*) &item[i] ); 
	}
	
	end = ListItr_End(list);
	end = ListItr_Prev(end);
	itemPtr = ListItr_Get(end);

	if(*itemPtr!=item[0])
	{
		List_Destroy ( &list, NULL);
		return FAIL;
	}
	
	List_Destroy ( &list, NULL);
	return PASS;
}

/*------------------------------------------*/
int ListItrEndAndItrBeginEquals()
{	

	List* list=NULL;
	int item=7;

	ListItr end;
	ListItr begin;
	
	list=List_Create();
	
	List_PushHead (list , (void*) &item ); 
	begin = ListItr_Begin(list);
	end = ListItr_End(list);
	end = ListItr_Prev(end);
	if(ListItr_Equals(begin , end) > 0)
	{
		List_Destroy ( &list, NULL);
		return PASS;
	}
	List_Destroy ( &list, NULL);
	return FAIL;	
}
/*------------------------------------------*/
int ListItrPrevIsBackToBegin ()
{	

	List* list=NULL;
	int item=7;

	ListItr end;
	ListItr begin;
	
	list=List_Create();
	
	List_PushHead (list , (void*) &item ); 
	begin = ListItr_Begin(list);
	end = ListItr_End(list);
	end = ListItr_Prev(end);
	if(ListItr_Equals(begin , end) > 0)
	{
		List_Destroy ( &list, NULL);
		return PASS;
	}
	List_Destroy ( &list, NULL);
	return FAIL;	
}


/*------------------------------------------

int ListItrEndAndGet()
{	

	int i;
	List* list=NULL;
	int item[NUM_OF_ITEMS_TO_ADD];
	int *itemPtr;
	ListItr Begin;

	
	list=List_Create();
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		item[i] = rand() %1000 ;
		List_PushHead (list , (void*) &item[i] ); 
	}
	
	Begin = ListItr_End(list);
	(void*) itemPtr = ListItr_Get(begin);

	if(*itemPtr!=item[0])
	{
		List_Destroy ( &list, NULL);
		return FAIL;
	}
	
	List_Destroy ( &list, NULL);
	return PASS;
}

----------------------------------------------*/




