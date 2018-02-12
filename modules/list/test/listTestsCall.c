
/** 
 *  @file listTestsCall.h
 *  @brief Iterator Functions
 * 
 *  @details 
 * 
 *  @author Author Nurit (H-45), Adv. C-3, 23.05.2017
 * 
 *  @bug No known bugs.
 */


#include 	<stdio.h>		/* printf */
#include	<string.h>		/* strcpy */

#include 	"listTests.h"	/* tests header */

#define 	NAME_SIZE	100


static void PrintTestResult ( char* _testName, int _cond )
{
	printf ("\n%s test result: \t%s", _testName, (_cond) ? "PASS" : "FAIL");
	putchar('\n');
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main ()
{
	char  testName[NAME_SIZE];
	
	
	printf("------------ List_Create Test -------------\n");
	strcpy(testName,"TestListCreateInputOK"); 
	PrintTestResult (testName, (PASS == TestListCreateInputOK ()) );

	printf("------------ Valid List Test ---------------\n");
	strcpy(testName,"TestListInputNULL4All"); 
	PrintTestResult (testName, (PASS == TestListInputNULL4All ()) );
	strcpy(testName,"TestListInputNotList4All");
	PrintTestResult (testName, (PASS == TestListInputNotList4All ()) );	

	
	printf("------------ List_Destroy Test -------------\n");
	strcpy(testName,"TestListDestroySanity");
	PrintTestResult (testName, (PASS == TestListDestroySanity ()) );

	printf("------------ List_PushHead Test -------------\n");
	strcpy(testName,"TestListPushHeadItemNULL");
	PrintTestResult (testName, (PASS == TestListPushHeadItemNULL ()) );
	strcpy(testName,"TestListPushHeadInputOK");
	PrintTestResult (testName, (PASS == TestListPushHeadInputOK ()) );
	strcpy(testName,"TestListPushHeadMultiple");
	PrintTestResult (testName, (PASS == TestListPushHeadMultiple ()) );

	printf("------------ List_PushTail Test -------------\n");
	strcpy(testName,"TestListPushTailItemNULL");
	PrintTestResult (testName, (PASS == TestListPushTailItemNULL ()) );
	strcpy(testName,"TestListPushTailInputOK");
	PrintTestResult (testName, (PASS == TestListPushTailInputOK ()) );
	strcpy(testName,"TestListPushTailMultiple");
	PrintTestResult (testName, (PASS == TestListPushTailMultiple ()) );

	printf("------------ List_PopHead Test -------------\n");
	strcpy(testName,"TestPopHeadPlaceHolderNULL");
	PrintTestResult (testName, (PASS == TestPopHeadPlaceHolderNULL ()) );
	strcpy(testName,"TestPopHeadListEmpty");
	PrintTestResult (testName, (PASS == TestPopHeadListEmpty ()) );
	strcpy(testName,"TestListPopHeadInputOK");
	PrintTestResult (testName, (PASS == TestListPopHeadInputOK ()) );
	strcpy(testName,"TestPopHeadMultAddedFromHead");
	PrintTestResult (testName, (PASS == TestPopHeadMultAddedFromHead ()) );
	strcpy(testName,"TestPopHeadMultipleFromTail");
	PrintTestResult (testName, (PASS == TestPopHeadMultipleFromTail ()) );
	
	printf("------------ List_PopTail Test -------------\n");
	strcpy(testName,"TestPopTailPlaceHolderNULL");
	PrintTestResult (testName, (PASS == TestPopTailPlaceHolderNULL ()) );
	strcpy(testName,"TestPopTailListEmpty");
	PrintTestResult (testName, (PASS == TestPopTailListEmpty ()) );
	strcpy(testName,"TestListPopTailInputOK");
	PrintTestResult (testName, (PASS == TestListPopTailInputOK ()) );
	strcpy(testName,"TestPopTailMultAddedFromHead");
	PrintTestResult (testName, (PASS == TestPopTailMultAddedFromHead ()) );
	strcpy(testName,"TestPopTailMultipleFromTail");
	PrintTestResult (testName, (PASS == TestPopTailMultipleFromTail ()) );

	printf("--------------- List_Size Test -----------------\n");
	strcpy(testName,"TestListSizeEmptyList");
	PrintTestResult (testName, (PASS == TestListSizeEmptyList ()) );
	strcpy(testName,"TestListSizeAfterPush");
	PrintTestResult (testName, (PASS == TestListSizeAfterPush ()) );
	strcpy(testName,"TestListSizeAfterPop");
	PrintTestResult (testName, (PASS == TestListSizeAfterPop ()) );

	printf("------------ List_ForEach Test -------------\n");	
	/*printf("\nListForEach -  Print: %s ", ( FAIL == TestListForEachPrint () ) ?  "FAIL" : "PASS");
	putchar('\n');*/
	
	printf("\n----------list tests-----------\n");
	printf("ListCreate res is %s\t\n",(ListCreate()==PASS) ? "PASS": "FAIL");
	printf("DoubleDestroy res is %s\t\n",(DoubleDestroy()==PASS)? "PASS": "FAIL");
	printf("ListPushHeadWithNull res is %s\t\n",(ListPushHeadWithNull()==PASS)? "PASS": "FAIL");
	printf("ListPushHeadStructNotList res is %s\t\n",(ListPushHeadStructNotList()==PASS)? "PASS": "FAIL");
	printf("ListPushHeadNullItem res is %s\t\n",(ListPushHeadNullItem()==PASS)? "PASS": "FAIL");
	printf("ListPushHeadPopTail res is %s\t\n",(ListPushHeadPopTail()==PASS)? "PASS": "FAIL");
	printf("ListPushHeadPopHead res is %s\t\n",(ListPushHeadPopHead()==PASS)? "PASS": "FAIL");
	
	printf("\n----------itr tests-----------\n");
	printf("ListItrBeginAndGet res is %s\t\n",(ListItrBeginAndGet()==PASS)? "PASS": "FAIL");
	printf("ListItrEndAndGet res is %s\t\n",(ListItrEndAndGet()==PASS)? "PASS": "FAIL");
	printf("ListItrEndAndItrBeginEquals res is %s\t\n",(ListItrEndAndItrBeginEquals()==PASS)? "PASS": "FAIL");	
	printf("ListItrPrevIsBackToBegin res is %s\t\n",(ListItrPrevIsBackToBegin()==PASS)? "PASS": "FAIL");	
	
	
	return 0;
} 


























