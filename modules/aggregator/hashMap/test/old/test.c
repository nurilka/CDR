
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"
#include "list.h"
#include "list_itr.h"
#include "list_functions.h"

#define PASS 	1
#define FAIL 	0

#define TRUE 	1
#define FALSE	0

#define NUM_OF_ITEMS_TO_ADD 200
#define	MAX_STR_SIZE	50


/*----------- Declarations -----------------*/
int TestHashMapInputNULL4All ();
int TestHashMapCreateSanity();
int TestHashMapDestroySanity();
int TestHashMapInsertSanity();
int TestHashMapInsertMultiple();



/*---------------------- MAIN ----------------------------*/
int main()
{
	printf("\n----------Hash Map Tests-----------\n");
	printf("TestHashMapInputNULL4All res is %s\t\n",(TestHashMapInputNULL4All()==PASS) ? "PASS": "FAIL");
	printf("TestHashMapCreateSanity res is %s\t\n",(TestHashMapCreateSanity()==PASS)? "PASS": "FAIL");
	printf("TestHashMapDestroySanity res is %s\t\n",(TestHashMapDestroySanity()==PASS)? "PASS": "FAIL");
	printf("TestHashMapInsertSanity res is %s\t\n",(TestHashMapInsertSanity()==PASS)? "PASS": "FAIL");
	printf("TestHashMapInsertMultiple res is %s\t\n",(TestHashMapInsertMultiple()==PASS)? "PASS": "FAIL");

	return 0;
}

/*

HashMap* HashMap_Create (size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);

void HashMap_Destroy (HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

Map_Result HashMap_Rehash (HashMap *_map, size_t newCapacity);

Map_Result HashMap_Insert (HashMap* _map, const void* _key, const void* _value);

Map_Result HashMap_Remove (HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue);

Map_Result HashMap_Find (const HashMap* _map, const void* _searchKey, void** _pValue);

size_t HashMap_Size (const HashMap* _map);

size_t HashMap_ForEach (const HashMap* _map, KeyValueActionFunction _action, void* _context);
*/



/*---------- Tests ----------------*/
typedef struct 
{
	int m_x;
	int m_y;
} Point;

typedef struct 
{
	int m_num1;
	int m_num2;
	int m_num3;
}Nums;

typedef struct
{
	char 	m_sex;
	char* 	m_name;
} Person;



/*--------- Auxiliary Functions ------------*/
static int	 EqualKeys (const int* _key1, const int* _key2)
{
	return (*_key1 == *_key2) ? TRUE : FALSE;
}

static int 	EqualStr (const char* _str1, char* _str2)
{
	return (strcmp(_str1, _str2)) ? TRUE : FALSE;
}

static size_t HashCode_1 (const int* _key)
{
	return *_key;
}

static size_t HashCode_2 (const int* _key)
{
	return *_key ^ 0xCAFECAFE;
}

/*static void freeKey(char * key)
{
	if(key)
	{
		free(key);
	}
}

static void	ActionPrintInt (const int* _key, int* _value, void* _context)
{	
	printf("key: %d , value: %d\n" , *_key , *_value );
}

*/


/*~~~~~~~~~~~~~~~~~ Test Valid Map ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Test All functions with _map == NULL
 * 
 * @returns 
 * @retval FAIL	-  if anything but LIST_UNINITIALIZED_ERROR
 * @retval PASS	-  if LIST_UNINITIALIZED_ERROR
 */
int  TestHashMapInputNULL4All ()
{
	Map_Result 		err  	= MAP_SUCCESS;
	int  			key 	= 100;
	int 			val		= 31415;
	int*			pKey 	= NULL;
	int*			pVal 	= NULL;
	size_t			size 	= 0XFAABCAFE;
	
	err =    HashMap_Rehash     (NULL, 12);
	if ( MAP_ALLOCATION_ERROR != err )
	{
		return FAIL;
	}
	err =    HashMap_Insert     (NULL, (void*)&key, (void*)&val);
	if ( MAP_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    HashMap_Remove     (NULL, (void*)&key, (void*)&pKey, (void*)&pVal);
	if ( MAP_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	err =    HashMap_Find  (NULL, (void*)&key, (void*)&pKey);
	if ( MAP_UNINITIALIZED_ERROR != err )
	{
		return FAIL;
	}
	size =    HashMap_Size (NULL);
	if ( 0 != size )
	{
		return FAIL;
	}
	size =    HashMap_ForEach (NULL, NULL, NULL);
	if ( 0 != size )
	{
		return FAIL;
	}
	
	return PASS;
} 
/** 
 * @brief Create a new hash map with given capcity and key characteristics.
 * @return PASS - if newly created map 
 * @return FAIL - if null on failure
 */
int TestHashMapCreateSanity()
{
	HashMap* 		map;
	HashFunction 	HashCode; 
	EqualityFunction KeysEq;
	
	HashCode = (HashFunction)&HashCode_1;
	KeysEq = (EqualityFunction)&EqualKeys;
	map = HashMap_Create( 4, HashCode, KeysEq );
	
	if(! map )
	{
		return FAIL;
	}
	return PASS;
}

/** 
 * @brief Destroy a hash map Sanity
 * @return PASS - if map is NULL
 * @return FAIL - if map is not NULL
 */
int TestHashMapDestroySanity()
{
	HashMap* 		map;
	HashFunction 	HashCode; 
	EqualityFunction KeysEq;
	
	HashCode = (HashFunction)&HashCode_1;
	KeysEq = (EqualityFunction)&EqualKeys;
	map = HashMap_Create( 4, HashCode, KeysEq );
	
	if(! map )
	{
		return FAIL;
	}
	
	HashMap_Destroy (&map, NULL, NULL);
	return (map) ? FAIL : PASS;
}

/*~~~~~~~~~~~~~~~~~ Test Map Insert ~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Insert one pair into a hash map - Sanity
 * @return PASS - if MAP_SUCCESS
 * @return FAIL - if not MAP_SUCCESS
 */
int TestHashMapInsertSanity()
{
	HashMap* 		map;
	HashFunction 	HashCode; 
	EqualityFunction KeysEq;
	Map_Result		err = MAP_SUCCESS;
	FILE* 			pFile;
	char			fName[] = "randStr.txt";
	int 			key = 0;
	size_t			mapSize = 0;
	char			str[15];


	HashCode = (HashFunction)&HashCode_2;
	KeysEq = (EqualityFunction)&EqualStr;
	map = HashMap_Create( 4, HashCode, KeysEq );
	
	if(! map )
	{
		return FAIL;
	}

	pFile = fopen (fName, "r+");
	if ( !pFile )
	{
		return FAIL;
	}
	/* 	reads a word an puts a cursor at the end  */
	fscanf (pFile, "%d %s", &key, str);
	fclose (pFile);
	
	err = HashMap_Insert (map, (void*)&key, (void*)&str);
	if (MAP_SUCCESS != err)
	{
		return FAIL;
	}
	mapSize = HashMap_Size(map);
	HashMap_Destroy (&map, NULL, NULL);
	return (mapSize != 1) ? FAIL : PASS;
}

/** 
 * @brief Insert pairs into a hash map - sanity
 * @return PASS - if MAP_SUCCESS
 * @return FAIL - if not MAP_SUCCESS
 */
int TestHashMapInsertMultiple()
{
	HashMap* 		map;
	HashFunction 	HashCode; 
	EqualityFunction KeysEq;
	Map_Result		err = MAP_SUCCESS;
	FILE* 			pFile;
	char			fName[] = "randStr.txt";
  	char* 			valsBuf[MAX_STR_SIZE] = {0};
  	int				keysBuf[MAX_STR_SIZE] = {0};
	size_t			i; /*, mapSize = 0;*/

	HashCode = (HashFunction)&HashCode_2;
	KeysEq = (EqualityFunction)&EqualStr;
	map = HashMap_Create( 30, HashCode, KeysEq );
	
	if(! map )
	{
		return FAIL;
	}
  	/* open the file */
	pFile = fopen (fName, "r+");
	if ( !pFile ) 
	{
		fputs ("File open error",stdout);
		HashMap_Destroy (&map, NULL, NULL);
		return FAIL;
	}

	i = 0;
	/* 	reads a word an puts a cursor at the end  */
	while (!feof(pFile))
	{
 		valsBuf[i] = (char*) malloc (sizeof(char)*MAX_STR_SIZE);
 		fscanf (pFile, "%d %s", &keysBuf[i], valsBuf[i]);
		err = HashMap_Insert (map, (void*)&keysBuf[i], (void*)&valsBuf[i]);
		if (MAP_SUCCESS != err)
		{
			return FAIL;
		}
		++i;
	}
	fclose (pFile);
	while (i >= 0)
	{
		free(valsBuf[i-1]);
	}
	
	/*mapSize = HashMap_Size(map);*/
	HashMap_Destroy (&map, NULL, NULL);
	/*return (mapSize != 13) ? FAIL : PASS;*/
	return PASS;
}
 
