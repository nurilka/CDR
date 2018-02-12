#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashMap.h"


#define TRUE 1
#define FALSE 0
#define PRIME 11
#define CAP 15
#define BASE 256


typedef struct Var Var;

struct Var
{
	size_t m_x;
	size_t m_y;
};

size_t HashFuncCalculate(const void* _string)
{
	size_t hashSymbol;
	unsigned const char *us;

	us = (unsigned const char *) _string;

	hashSymbol = 0;
	while(*us != '\0') 
	{
		hashSymbol = (hashSymbol * BASE + *us);
		us++;
	} 

	return hashSymbol;
}

int IsEqual (const void* _firstKey, const void* _secondKey)
{
	char* first = (char*)_firstKey;
	char* second = (char*)_secondKey;

	if (0 == strcmp ( first, second))
	{
		return TRUE;
	}
	return FALSE;
}



int PrintAllItemInMap(const void* _key, void* _value, void* _context)
{
	char* pVarKey = NULL;
	Var* pVarValue = NULL;

	pVarKey = (char*)_key;
	pVarValue = _value;
	
	printf("----------------\n");
	printf("-name: %s \n", pVarKey);
	printf("----------------\n");
	printf("-value x: %d value y: %d\n", pVarValue->m_x, pVarValue->m_y);
	printf("----------------\n");
	return 1;
}

void FreeKey(void* _key)
{
	char* pVarKey = NULL;

	pVarKey = _key;
	free(pVarKey);
}

void FreeValue(void* _value)
{
	Var* pVarValue = NULL;

	pVarValue = _value;
	free(pVarValue);
}


static Var* CreateVariablesToTest(int _num)
{
	Var* pVar;
	
	pVar = (Var*)malloc(sizeof(Var));
	
	if (!pVar)
	{
		return NULL;
	}
	
	pVar->m_x = _num * PRIME;
	pVar->m_y = _num * PRIME * 2;
	
	return pVar;
}


/*****************************************************************************************************/

int HashMap_InsertTest()
{
	int index;
	char* string;
	Var* pVar2 = NULL;
	HashMap* testMap = NULL;
	Map_Result err;
	FILE* ptr;
	ptr = fopen("name", "r+");

	if (!ptr)
	{
		printf("Cannot open file!\n");
		return FALSE;
	}	
	
	testMap = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	
	for (index = 1; index < (CAP * 5) + 1; ++index)
	{
		string = (char*)malloc(20 * sizeof(char));
		fgets(string, 20, ptr);
		pVar2 = CreateVariablesToTest(index +13);
		err = HashMap_Insert(testMap, string, pVar2);
		
		if (MAP_SUCCESS != err)
		{
			if (MAP_KEY_DUPLICATE_ERROR == err)
			{
				free(string);
				free(pVar2);
				continue;
			}
			else
			{
				return FALSE;
			}
		}
	}
	HashMap_Destroy(&testMap, FreeKey, FreeValue);
	fclose (ptr);
	return TRUE;	
}

/*****************************************************************************************************/

HashMap* SetTest(void)
{
	int index;
	char* string;
	Var* pVar2 = NULL;
	HashMap* testMap = NULL;
	Map_Result err;
	FILE* ptr;
	ptr = fopen("name", "r+");

	if (!ptr)
	{
		printf("Cannot open file!\n");
		return NULL;
	}	
	
	testMap = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	
	for (index = 1; index < (CAP * 5) + 1; ++index)
	{
		string = (char*)malloc(20 * sizeof(char));
		fgets(string, 20, ptr);
		pVar2 = CreateVariablesToTest(index +13);
		err = HashMap_Insert(testMap, string, pVar2);
		
		if (MAP_SUCCESS != err)
		{
			if (MAP_KEY_DUPLICATE_ERROR == err)
			{
				free(string);
				free(pVar2);
				continue;
			}
			else
			{
				return NULL;
			}
		}
	}

	fclose (ptr);
	return testMap;
}

/*****************************************************************************************************/

int HashMap_SizeTest(HashMap* _testMap)
{
	size_t testSize = 0;
	testSize = HashMap_Size(_testMap);
	if ((CAP * 5) - 10 == testSize)
	{
		return TRUE;
	}

	return FALSE;
}



int HashMap_SizeTestEmpty(HashMap* _testMap)
{
	size_t testSize = 0;
	testSize = HashMap_Size(_testMap);
	if (0 == testSize)
	{
		return TRUE;
	}
	
	return FALSE;
}



int HashMap_RemoveTest(HashMap* _testMap)
{
	void* name;
	Var* pVar2 = NULL;
	char toFind[20] = "OFRI\n";
	
	HashMap_Remove(_testMap, toFind, (void*)&name, (void*)&pVar2);
	
	
	if ( 0 == strcmp ( name, toFind)  && pVar2->m_x == 154 && pVar2->m_y == 308 )
	{
		return TRUE;
	}
	free(name);

	return FALSE;
}

int HashMap_RemoveTestEmpty(HashMap* _testMap)
{
	void* name;
	Var* pVar2 = NULL;
	char toFind[20] = "OFRI\n";
	
	if (MAP_KEY_NOT_FOUND_ERROR == (HashMap_Remove(_testMap, toFind, (void*)&name, (void*)&pVar2)))
	{
		return TRUE;
	}
	
	return FALSE;
}

int HashMap_FindTest(HashMap* _testMap)
{
	Var* pVar = NULL;

	char toFind[20] = "MISTIE\n";
	
	HashMap_Find(_testMap, toFind, (void*)&pVar);

	
	if (pVar->m_x == 275 && pVar->m_y == 550 )
	{
		return TRUE;
	}

	return FALSE;
}

int HashMap_FindTestEmpty(HashMap* _testMap)
{
	Var* pVar = NULL;
	char toFind[20] = "MISTIE\n";
	
	if (MAP_KEY_NOT_FOUND_ERROR == (HashMap_Find(_testMap, toFind, (void*)&pVar)))
	{
		return TRUE;
	}
	
	return FALSE;
}

int HashMap_RehashTest(HashMap* _testMap)
{
	size_t Cap = 23;
	
	if (MAP_SUCCESS == (HashMap_Rehash(_testMap, Cap)))
	{
		return TRUE;
	}
	
	return FALSE;
}


int HashMap_RehashTestEmpty(HashMap* _testMap)
{
	size_t Cap = 23;
	
	if (MAP_SUCCESS == (HashMap_Rehash(_testMap, Cap)))
	{
		return TRUE;
	}

	return FALSE;
}

int HashMap_DestroyTest(HashMap* _testMap)
{
	HashMap_Destroy(&_testMap, NULL, NULL);
	HashMap_Destroy(&_testMap, NULL, NULL);
	return TRUE;
}


int HashMap_InsertTestDUP(HashMap* _testMap)
{
	size_t num = 23;
	char* stringA;
	char* stringB;
	
	stringA = (char*)malloc(20 * sizeof(char));
	stringB = (char*)malloc(20 * sizeof(char));
	
	stringA = "AAAA";
	stringB = "AAAA";
	
	HashMap_Insert(_testMap, stringA, (void*)num);
	
	if (MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(_testMap, stringB, (void*)num))
	{
		return TRUE;
	}

	return FALSE;
}


int HHashMap_RemoveTestKEY_NOT(HashMap* _testMap)
{
	size_t num = 23, numRemove;
	char* stringA;
	char* stringB;
	char* stringC;
	char* stringD;
	
	stringA = (char*)malloc(20 * sizeof(char));
	stringB = (char*)malloc(20 * sizeof(char));
	stringC = (char*)malloc(20 * sizeof(char));
	
	stringA = "AADD";
	stringB = "BBCC";
	stringC = "FFFF";
	
	HashMap_Insert(_testMap, stringA, (void*)num);
	HashMap_Insert(_testMap, stringB, (void*)num);
	
	if (MAP_KEY_NOT_FOUND_ERROR == HashMap_Remove(_testMap, stringC, (void*)&stringD, (void*)&numRemove))
	{
		return TRUE;
	}

	return FALSE;
}


int HashMap_FindTestKEY_NOT(HashMap* _testMap)
{
	size_t num = 23, numRemove;
	char* stringA;
	char* stringB;
	char* stringC;

	
	stringA = (char*)malloc(20 * sizeof(char));
	stringB = (char*)malloc(20 * sizeof(char));
	stringC = (char*)malloc(20 * sizeof(char));
	
	stringA = "AADD";
	stringB = "BBCC";
	stringC = "FFFF";
	
	HashMap_Insert(_testMap, stringA, (void*)num);
	HashMap_Insert(_testMap, stringB, (void*)num);
	

	if (MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_testMap, stringC, (void*)&numRemove))
	{
		return TRUE;
	}

	return FALSE;
}

int main()
{
	HashMap* testSize;
	/*HashMap* testForEach;*/
	HashMap* testRemove;
	HashMap* testFind;
	HashMap* testRehash;
	HashMap* testEmpty;
	HashMap* testDestroy;
	HashMap* testDuplicate;
	HashMap* testKeyNotFound;
	HashMap* GetStatistics;
	Map_Stats stat;
	
	/*working hash map test*/
	printf("-------------working hash map test-------------\n");
	printf("HashMap_InsertTest:		");
	(TRUE == (HashMap_InsertTest())) ? printf("pass\n") : printf("fail\n");
	testSize = SetTest();
	printf("HashMap_SizeTest:		");
	(TRUE == (HashMap_SizeTest(testSize))) ? printf("pass\n") : printf("fail\n");
	HashMap_Destroy(&testSize, FreeKey, FreeValue);
	testRemove = SetTest();
	printf("HashMap_RemoveTest:		");
	(TRUE == (HashMap_RemoveTest(testRemove))) ? printf("pass\n") : printf("fail\n");	
	HashMap_Destroy(&testRemove, FreeKey, FreeValue);
	testFind = SetTest();
	printf("HashMap_FindTest:		");
	(TRUE == (HashMap_FindTest(testFind))) ? printf("pass\n") : printf("fail\n");
	HashMap_Destroy(&testFind, FreeKey, FreeValue);
	testRehash = SetTest();
	printf("HashMap_RehashTest:		");
	(TRUE == (HashMap_RehashTest(testRehash))) ? printf("pass\n") : printf("fail\n");	
	HashMap_Destroy(&testRehash, FreeKey, FreeValue);
	printf("\n");
	
	/*Empty hash map test*/
	printf("-------------Empty hash map test-------------\n");
	testEmpty = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	printf("HashMap_SizeTestEmpty:		");
	(TRUE == (HashMap_SizeTestEmpty(testEmpty))) ? printf("pass\n") : printf("fail\n");		
	printf("HashMap_FindTestEmpty:		");
	(TRUE == (HashMap_FindTestEmpty(testEmpty))) ? printf("pass\n") : printf("fail\n");
	printf("HashMap_RemoveTestEmpty:	");
	(TRUE == (HashMap_RemoveTestEmpty(testEmpty))) ? printf("pass\n") : printf("fail\n");
	printf("HashMap_RehashTest:		");
	(TRUE == (HashMap_RehashTest(testEmpty))) ? printf("pass\n") : printf("fail\n");
	HashMap_Destroy(&testEmpty, NULL, NULL);
	printf("\n");
	
	/*Destroy hash map test*/
	printf("-------------Destroy hash map test-------------\n");
	testDestroy = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	printf("HashMap_DestroyTest:		");
	(TRUE == (HashMap_DestroyTest(testDestroy))) ? printf("pass\n") : printf("fail\n");	
	printf("\n");
	
	
	/*Eeror hash map test*/
	printf("-------------Eeror hash map test-------------\n");
	testDuplicate = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	printf("HashMap_InsertTestDuplicate:	");
	(TRUE == (HashMap_InsertTestDUP(testDuplicate))) ? printf("pass\n") : printf("fail\n");
	testKeyNotFound = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	printf("HashMap_RemoveTestKeyNotFound:	");
	(TRUE == (HHashMap_RemoveTestKEY_NOT(testKeyNotFound))) ? printf("pass\n") : printf("fail\n");
	testKeyNotFound = HashMap_Create(CAP, HashFuncCalculate, IsEqual);
	printf("HashMap_FindTestKeyNotFound:	");
	(TRUE == (HashMap_FindTestKEY_NOT(testKeyNotFound))) ? printf("pass\n") : printf("fail\n");
	HashMap_Destroy(&testKeyNotFound, NULL, NULL);




	GetStatistics = SetTest();
	stat = HashMap_GetStatistics(GetStatistics);
	
	printf("numberOfBuckets:	%d\n",stat.numberOfBuckets);
	printf("numberOfChains:		%d\n",stat.numberOfChains);
	printf("maxChainLength:		%d\n",stat.maxChainLength);
	printf("averageChainLength:	%d\n",stat.averageChainLength);
	
	
	/*testForEach = SetTest();
	HashMap_ForEach(testForEach, PrintAllItemInMap, NULL);
	HashMap_Destroy(&testForEach, FreeKey, FreeValue);	*/	
	return 0;
}
















