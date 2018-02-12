
#include <stdio.h>
#include <stdlib.h>

#include 	"hashMap.h"
#include 	"list.h"
#include 	"list_itr.h"		/* Iterator API */
#include 	"list_functions.h"	/* Iterator functions */

#define CALCULATE_HASH( Func ,key ,capacity) ( (Func((key)) )% (capacity))

#define PASS 0
#define FAIL -1

#define NUM_OF_ITEMS_TO_ADD 10


/*----------- Declare -------------------*/
int insertAndRemoveOneItem();
int insertAndRemoveTwoItemsSameHashCode();
int RemoveItemNotExist();
int insertAndRemove();
int insertAndRemoveWithRandKey();
int insertAndFindOneItem();
int insertAndFindTwice();
int FindItemNotExist();
int insertAndFind();
int NumOfPairs();
int RehashAndFindingAllNums();
int ForEachPrint();


/*------------------------------------------
   				TEST RUNS
------------------------------------------*/
int main()
{
	printf("----------hash tests-----------\n");
	printf("insertAndRemoveOneItem res is %s\t\n",(insertAndRemoveOneItem()==PASS) ? "PASS": "FAIL");
	printf("insertAndRemoveTwoItemsSameHashCode res is %s\t\n", (insertAndRemoveTwoItemsSameHashCode()==PASS)? "PASS": "FAIL");	
	printf("RemoveItemNotExist res is %s\t\n", (RemoveItemNotExist()==PASS)? "PASS": "FAIL");	
	printf("insertAndRemove res is %s\t\n", (insertAndRemove()==PASS)? "PASS": "FAIL");			
	printf("insertAndRemoveWithRandKey res is %s\t\n", (insertAndRemoveWithRandKey()==PASS)? "PASS": "FAIL");	
	printf("insertAndFindOneItem res is %s\t\n", (insertAndFindOneItem()==PASS)? "PASS": "FAIL");				
	printf("insertAndFindTwice res is %s\t\n", (insertAndFindTwice()==PASS)? "PASS": "FAIL");					
	printf("FindItemNotExist res is %s\t\n", (FindItemNotExist()==PASS)? "PASS": "FAIL");						
	printf("insertAndFind res is %s\t\n", (insertAndFind()==PASS)? "PASS": "FAIL");		
	printf("NumOfPairs res is %s\t\n", (NumOfPairs()==PASS)? "PASS": "FAIL");		
	printf("RehashAndFindingAllNums res is %s\t\n", (RehashAndFindingAllNums()==PASS)? "PASS": "FAIL");			
	printf("RehashAndFindingAllNums res is %s\t\n", (RehashAndFindingAllNums()==PASS)? "PASS": "FAIL");
	printf("ForEachPrint res is %s\t\n", (ForEachPrint()==PASS)? "PASS": "FAIL");
	
	
	return 0;
}


/*------------------------------------------
				USER FUNCTIONS
------------------------------------------*/
size_t HashFunc(const int* _key)
{
	int a= (int) *_key;
	
	return(size_t) (( a*a) /2);
}
int isEqual(const int* _firstKey, const int* _secondKey)
{
	return (*_firstKey == *_secondKey) ? 1 : 0; 
}

int	Action(const int* _key, int* _value, void* _context)
{	
	printf("key: %d , val: %d\n" , *_key , *_value );
	return 1;
}

/*------------------------------------------
				LIST TESTS
------------------------------------------*/

typedef struct 
{
	int m_num1;
	int m_num2;
	int m_num3;
}Nums;


/*-----------------------------------------*/

int insertAndRemoveOneItem()
{
	
	HashMap* map;
	int key= 12;
	int val= 589;
	int searchKey = 12, searchVal = 15;
	int* pval;
	int* pkey;
	
	pkey = &searchKey; pval = &searchVal;

	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key , &val);

	HashMap_Remove( map,  &key,(void**) &pkey ,(void**) &pval);
	if( key == *pkey && val == *pval)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return PASS;
	}
	HashMap_Destroy( &map , NULL , NULL );
	return FAIL;
}

/*------------------------------------------*/

int insertAndRemoveTwoItemsSameHashCode()
{
	
	HashMap* map;
	int key1= 12;
	int val1= 589;
	
	int key2= 50;
	int val2= -14;
	int* pval;
	int* pkey;

	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key1 , &val1);
	HashMap_Insert( map, &key2 , &val2);
	
	HashMap_Remove( map,  &key1,(void**) &pkey ,(void**) &pval);
	if( key1 != *pkey || val1 != *pval)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return FAIL;
	}
	if(HashMap_Remove( map,  &key1,(void**) &pkey ,(void**) &pval) == MAP_KEY_NOT_FOUND_ERROR)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return PASS;
	}	
	HashMap_Destroy( &map , NULL , NULL );
	return FAIL;
}

/*------------------------------------------*/

int RemoveItemNotExist()
{
	
	HashMap* map;
	int key1= 12;
	int key2= 24;
	int val1= 589;
	
	int* pval;
	int* pkey;

	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key1 , &val1);
	
	HashMap_Remove( map,  &key1,(void**) &pkey ,(void**) &pval);
	if(HashMap_Remove( map,  &key2,(void**) &pkey ,(void**) &pval) == MAP_KEY_NOT_FOUND_ERROR)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return PASS;
	}	
	HashMap_Destroy( &map , NULL , NULL );
	return FAIL;
}

/*------------------------------------------*/

int insertAndRemove()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;
	
	int* pval;
	int* pkey;


	Map_Result err;
	
	printf("insertAndRemove\n");
	
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = i+i*2 ;
		val[i] = rand() %1000 -500;
		printf("(k,v)=(%d,%d)\n", key[i], val[i]);
		err = HashMap_Insert( map, &key[i] , &val[i]);
		printf("ERR: %d\n", err);
	}
	

	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		printf("Remove! (k,v)=(%d,%d) --->    ", key[i], val[i]);
		HashMap_Remove( map,  &key[i],(void**) &pkey ,(void**) &pval);
		printf("Removed! (k,v)=(%d,%d)\n", *pkey, *pval);
		if( key[i] != *pkey || val[i] != *pval)
		{
			HashMap_Destroy( &map , NULL , NULL );
			return FAIL;
		}
	}
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*------------------------------------------*/

int insertAndRemoveWithRandKey()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;
	
	int* pval;
	int* pkey;

	

	
	printf("insertAndRemoveWithRandKey\n");
	
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = rand() %1000 ;
		val[i] = rand() %1000 -500;
		printf("(k,v)=(%d,%d)\n", key[i], val[i]);
		HashMap_Insert( map, &key[i] , &val[i]);

		
	}
	
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		printf("Remove! (k,v)=(%d,%d) --->    ", key[i], val[i]);
		HashMap_Remove( map,  &key[i],(void**) &pkey ,(void**) &pval);
		printf("Removed! (k,v)=(%d,%d)\n", *pkey, *pval);
		if(((key[i] != *pkey) && (*pkey != 0))|| (val[i] != *pval && *pval != 0))
		{
			HashMap_Destroy( &map , NULL , NULL );
			return FAIL;
		}
		*pval=0;
		*pkey=0;
	}
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*------------------------------------------------*/


int insertAndFindOneItem()
{
	
	HashMap* map;
	int key= 12;
	int val= 589;
	int* pval;

	
	printf("insertAndFindOneItem\n");

	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key , &val);

	HashMap_Find( map,  &key ,(void**) &pval);
	if( val == *pval)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return PASS;
	}
	HashMap_Destroy( &map , NULL , NULL );
	return FAIL;
}

/*------------------------------------------*/

int insertAndFindTwice()
{
	
	HashMap* map;
	int key1= 12;
	int val1= 589;
	
	int key2= 50;
	int val2= -14;
	int* pval;


	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key1 , &val1);
	HashMap_Insert( map, &key2 , &val2);
	
	HashMap_Find( map,  &key1 ,(void**) &pval);
	if(  val1 != *pval)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return FAIL;
	}
	HashMap_Find( map,  &key1 ,(void**) &pval);
	if(  val1 != *pval)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return FAIL;
	}
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*------------------------------------------*/

int FindItemNotExist()
{
	
	HashMap* map;
	int key1= 12;
	int key2= 24;
	int val1= 589;
	
	int* pval;


	map = HashMap_Create( 30 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	HashMap_Insert( map, &key1 , &val1);
	
	if(	HashMap_Find( map,  &key2 ,(void**) &pval) == MAP_KEY_NOT_FOUND_ERROR)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return PASS;
	}	
	HashMap_Destroy( &map , NULL , NULL );
	return FAIL;
}

/*------------------------------------------*/

int insertAndFind()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;
	
	int* pval;

	
	Map_Result err;

	printf("insertAndFind\n");
	
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i = 0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = rand() % 1000 ;
		val[i] = rand() % 1000 + 500;
		err = HashMap_Insert( map, &key[i] , &val[i]);
		printf("ERR! %d [k,v] = [%d, %d]\n", err, key[i], val[i]);
	}
	printf("insertAndFind - done inserting\n");
	for(  i = 0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		printf("insertAndFind - finding [%d, %d]\n", key[i],val[i]);
		HashMap_Find( map,  &key[i] ,(void**) &pval);
		if( val[i] != *pval && *pval != 0)
		{
			printf("insertAndFind - fail fail fail %d\n", i);
			HashMap_Destroy( &map , NULL , NULL );
			return FAIL;
		}
		/*
		*pval = 0;
		*pkey = 0;
		*/
	}
	printf("insertAndFind - done success\n");
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*------------------------------------------*/


int NumOfPairs()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;
	
	int* pval;
	int* pkey;

	
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = i*i ;
		val[i] = rand() %1000 +500;
		HashMap_Insert( map, &key[i] , &val[i]);
	}
	if(HashMap_Size(map) != NUM_OF_ITEMS_TO_ADD)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return FAIL;
	}
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD/2; i++ )
	{
		HashMap_Remove( map,  &key[i],(void**) &pkey ,(void**) &pval);
	}
	if(HashMap_Size(map) != NUM_OF_ITEMS_TO_ADD/2)
	{
		HashMap_Destroy( &map , NULL , NULL );
		return FAIL;
	}
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*------------------------------------------*/

int RehashAndFindingAllNums()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;
	
	int* pval;
	int* pkey;
	
	Map_Result err;

	printf("RehashAndFindingAllNums\n");
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = i+i/2 ;
		val[i] = rand() %1000 +500;
		err = HashMap_Insert( map, &key[i] , &val[i]);
		printf("ERR! %d [k,v] = [%d, %d]\n", err, key[i], val[i]);
	}
	printf("RehashAndFindingAllNums - done inserting!\n");
	HashMap_Rehash(map, 74);
	printf("RehashAndFindingAllNums - done rehash\n");
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD/2; i++ )
	{
		HashMap_Remove( map,  &key[i],(void**) &pkey ,(void**) &pval);
		if( key[i] != *pkey || val[i] != *pval)
		{
			printf("RehashAndFindingAllNums - fail fail fail\n");
			HashMap_Destroy( &map , NULL , NULL );
			return FAIL;
		}
	}
	printf("RehashAndFindingAllNums - success\n");
	HashMap_Destroy( &map , NULL , NULL );
	printf("RehashAndFindingAllNums - destroyed\n");
	return PASS;
}

/*------------------------------------------*/


int ForEachPrint()
{	

	int i;
	int key[NUM_OF_ITEMS_TO_ADD];
	int val[NUM_OF_ITEMS_TO_ADD];
	HashMap* map;


	
	map = HashMap_Create( 40 , (HashFunction) HashFunc ,(EqualityFunction) isEqual );
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		key[i] = rand() %1000 ;
		val[i] = rand() %1000 -500;
		HashMap_Insert( map, &key[i] , &val[i]);
	}
	
	for(  i=0 ; i < NUM_OF_ITEMS_TO_ADD; i++ )
	{
		HashMap_ForEach( map, (KeyValueActionFunction) Action ,NULL);
	}
	HashMap_Destroy( &map , NULL , NULL );
	return PASS;
}

/*---------------------------------------------*/




