
/** 
 *  @file listTests.h
 *  @brief Tests API for List, Iterator, and Iterator functions
 * 
 *  @details Tests API
 * 
 *  @author Nurit (H-45), Adv.C-3,  23.05.2017
 * 
 *  @bug No known bugs.
 */

#ifndef __LISTTESTS_H__
#define __LISTTESTS_H__

#define 	PASS	1
#define 	FAIL	-1


/*~~~~~~~~~~~~~~~~~ Test List Create ~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test List Create with input OK
 * 
 * @returns 
 * @retval FAIL	-  the list is NULL
 * @retval PASS	-  the list is created 
 */

int  TestListCreateInputOK (); 

/*~~~~~~~~~~~~~~~~~ Test Valid List ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test All functions with _list == NULL
 * 
 * @returns 
 * @retval FAIL	-  if anything but LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  if LIST_UNINITIALIZED_ERROR
 */
int  TestListInputNULL4All ();
 
/** 
 * @brief Test All functions with pointer not to list
 * 
 * @returns 
 * @retval FAIL	-  if anything but LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  if LIST_UNINITIALIZED_ERROR
 */
int  TestListInputNotList4All ();


/*~~~~~~~~~~~~~~~~~ Test ListDestroy ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test Destroy sanity, call twice
 * 
 * @returns 
 * @retval PASS	
 */
int  TestListDestroySanity ();

/*~~~~~~~~~~~~~~~~~ Test ListPushHead ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPushHead Item NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_NULL_ELEMENT_ERROR
 * @retval PASS	-  LIST_NULL_ELEMENT_ERROR
 */
int  TestListPushHeadItemNULL ();

/** 
 * @brief Test ListPushHead Input OK one value
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushHeadInputOK (); 

/** 
 * @brief Test ListPushHead Inputs OK  multiple entries
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushHeadMultiple (); 

/*~~~~~~~~~~~~~~~~~ Test ListPushTail ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPushTail Item NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_NULL_ELEMENT_ERROR
 * @retval PASS	-  LIST_NULL_ELEMENT_ERROR
 */
int  TestListPushTailItemNULL ();

/** 
 * @brief Test ListPushTail Input OK one value
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushTailInputOK ();

/** 
 * @brief Test ListPushTail Inputs OK  multiple entries
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPushTailMultiple ();

/*~~~~~~~~~~~~~~~~~ Test ListPopHead ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test ListPopHead Input placeholder NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  LIST_UNINITIALIZED_ERROR
 */
int  TestPopHeadPlaceHolderNULL ();

/** 
 * @brief Test ListPopHead with empty list
 * 
 * @returns 
 * @retval FAIL	-  not LIST_EMPTY
 * @retval PASS	-  LIST_EMPTY
 */
int  TestPopHeadListEmpty (); 

/** 
 * @brief Test ListPopHead one item Input OK
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPopHeadInputOK ();

/** 
 * @brief Test ListPopHead Inputs OK  multiple entries added from Head
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopHeadMultAddedFromHead (); 

/** 
 * @brief Test ListPopHead Inputs OK  multiple entries added from Tail
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopHeadMultipleFromTail (); 

/*------------ List_PopTail Test -------------*/
/** 
 * @brief Test ListPopTail Input placeholder NULL
 * 
 * @returns 
 * @retval FAIL	-  not LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  LIST_UNINITIALIZED_ERROR
 */
int  TestPopTailPlaceHolderNULL ();

/** 
 * @brief Test ListPopTail with empty list
 * 
 * @returns 
 * @retval FAIL	-  not LIST_EMPTY
 * @retval PASS	-  LIST_EMPTY
 */
int  TestPopTailListEmpty ();

/** 
 * @brief Test ListPopTail one item Input OK
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestListPopTailInputOK ();

/** 
 * @brief Test ListPopTail Inputs OK  multiple entries added from Head
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopTailMultAddedFromHead ();

/** 
 * @brief Test ListPopTail Inputs OK  multiple entries added from Tail
 * 
 * @returns 
 * @retval FAIL	-  not LIST_SUCCESS
 * @retval PASS	-  LIST_SUCCESS
 */
int  TestPopTailMultipleFromTail ();


/*------------ List_Size Test -------------*/
/** 
 * @brief Test List_Size list empty
 * 
 * @returns 
 * @retval FAIL	-  returned non 0
 * @retval PASS	-  returned 0
 */
int  TestListSizeEmptyList ();

/** 
 * @brief Test List_Size After Push
 * 
 * @returns 
 * @retval FAIL	-  times push on empty != List size
 * @retval PASS	-  times push on empty == List size
 */
int  TestListSizeAfterPush ();


/** 
 * @brief Test List_Size After Pop
 * 
 * @returns 
 * @retval FAIL	-  times Push then Pop != List size
 * @retval PASS	-  times Push then Pop == List size
 */
int  TestListSizeAfterPop ();

int ListCreate();
int DoubleDestroy();
int ListPushHeadWithNull();
int ListPushHeadStructNotList();
int ListPushHeadNullItem();
int ListPushHeadPopTail();
int ListPushHeadPopHead();
/*itr tests*/
int ListItrBeginAndGet();
int ListItrEndAndGet();
int ListItrEndAndItrBeginEquals();
int ListItrPrevIsBackToBegin();



#endif /* #ifndef __LISTTESTS_H__ */









