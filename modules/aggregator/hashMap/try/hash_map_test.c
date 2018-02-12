#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

#define PASS 1
#define FAIL 0


int TestInsertAndForEach();
int TestFind();
int TestDestroy();
int TestRemove();
int TestSize();
int TestStats();
int TestRehash();
int TestDuplicate();

int main ()
{
	printf("\n");
	TestInsertAndForEach() 	  == PASS ? printf("TestInsertAndForEach			PASS\n")  :printf("TestInsertAndForEach FAIL\n");
	TestFind() 	 			  == PASS ? printf("TestFind				PASS\n") 			  :printf("TestFind FAIL\n");
	TestDestroy() 	  		  == PASS ? printf("TestDestroy				PASS\n")  		  :printf("TestDestroy FAIL\n");
	TestRemove() 	 		  == PASS ? printf("TestRemove				PASS\n")  		  :printf("TestRemove FAIL\n");
	TestSize() 	  			  == PASS ? printf("TestSize				PASS\n")  			  :printf("TestSize FAIL\n");
	TestStats() 	 		  == PASS ? printf("TestStats				PASS\n")  			  :printf("TestStats FAIL\n");
	TestRehash() 	 		  == PASS ? printf("TestRehash				PASS\n")  		  :printf("TestRehash FAIL\n");
	TestDuplicate() 	 	  == PASS ? printf("TestDuplicate				PASS\n")  		  :printf("TestDuplicate FAIL\n");
	printf("\n");

	return(1);
}
/*------------------------------User Functions--------------------------*/
size_t HashFunc(const int *_key)
{
	int key=*_key;
	
	return((key)%15);
}
size_t HashFuncChar(char *str) /*char hush func*/
{
    unsigned long hash = 5381;
    int c;

    while ( *str++)
	{
		c=*str;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash;
}
int LessFunc(int *_a,int *_b)
{
	if(_a < _b)
	{
		return(5);
	}
	
	return(0);
}
int CompareFunc(char *_a,char *_b)
{
	if(strcmp(_a,_b) == 0)
	{
		return(5);
	}
	
	return(0);
}
int Print(const char* _key, int* _value, void* _context)
{
	printf(" key : %-10s , value : \"%d\"\n",_key,*_value);
	
	return(1);
		
}
/*--------------------------------test functions------------------------*/
int TestInsertAndForEach()
{
	int i=0;	
	HashMap *ptr=NULL;
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};/*malloc*/
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	
	HashMap_ForEach(ptr,(KeyValueActionFunction)Print,NULL);
	printf("\n");
	HashMap_Destroy(&ptr,NULL,NULL);
	
	
	return(PASS);
	
}
/* ---------------------------------------------------------------------*/
int TestFind()
{
	int i=0;
	char find[10]= "world";
	int *intResult;
	HashMap *ptr=NULL;
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
		
	HashMap_Find(ptr,find,(void*)&intResult);
			
	if(*intResult == 210)
	{
		HashMap_Destroy(&ptr,NULL,NULL);
		return(PASS);
	}
	HashMap_Destroy(&ptr,NULL,NULL);
	return(FAIL);
}
/* ---------------------------------------------------------------------*/
int TestDestroy()
{
	int i=0;
	HashMap *ptr=NULL;
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};
	
	
	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
		
	HashMap_Destroy(&ptr,NULL,NULL);
	
	return(PASS);
	
}
/* ---------------------------------------------------------------------*/
int TestRemove()
{
	int i=0;
	char remove[10]= "world";
	int *intRemove=NULL;
	char *getRemove=NULL;
	HashMap *ptr=NULL;
	
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	HashMap_Remove(ptr,remove,(void*)&getRemove,(void*)&intRemove);
	
	if(*intRemove == 210)
	{	
		HashMap_Destroy(&ptr,NULL,NULL);	
		return(PASS);
	}
	HashMap_Destroy(&ptr,NULL,NULL);	
	return(FAIL);
	
}
/* ---------------------------------------------------------------------*/
int TestSize()
{
	int i=0;
	size_t size=0;
	HashMap *ptr=NULL;
	
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	size=HashMap_Size(ptr);
	
	if(size == 10)
	{	
		HashMap_Destroy(&ptr,NULL,NULL);	
		return(PASS);
	}
	HashMap_Destroy(&ptr,NULL,NULL);	
	return(FAIL);
}
/* ---------------------------------------------------------------------*/
int TestStats()
{
	int i=0;
	HashMap *ptr=NULL;
	Map_Stats stats;
	
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	
	stats=HashMap_GetStatistics(ptr);
	
	printf("\nnumberOfBuckets %lu\n",stats.numberOfBuckets);
	printf("numberOfChains %lu\n",stats.numberOfChains);
	printf("maxChainLength %lu\n",stats.maxChainLength);
	printf("averageChainLength %lu\n\n",stats.averageChainLength);
	
	HashMap_Destroy(&ptr,NULL,NULL);
	
	return(PASS);
}
/* ---------------------------------------------------------------------*/
int TestRehash()
{
	int i=0;
	HashMap *ptr=NULL;
	
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	
	HashMap_Rehash(ptr,30);
	
	HashMap_ForEach(ptr,(KeyValueActionFunction)Print,NULL);
	
	HashMap_Destroy(&ptr,NULL,NULL);
	
	return(PASS);
}
/* ---------------------------------------------------------------------*/
int TestDuplicate()
{
	int i=0;
	HashMap *ptr=NULL;
	char duplicated[10]="bursa";
	int newVal=555;
	Map_Result err;
	
	int array[10]={5204,210,354,874954,12315,7456,1235,15657,9875,32156};
	char *string[10]={"hey","world","how","do","you","bursa","is","he","analysis","market"};

	ptr=HashMap_Create(15,(HashFunction)HashFuncChar,(EqualityFunction)CompareFunc);
	for(i=0; i<10; i++)
	{
		HashMap_Insert(ptr, string[i],array+i);
	}
	
	err=HashMap_Insert(ptr, &duplicated,&newVal);
	
	if(err == 3)
	{
		HashMap_Destroy(&ptr,NULL,NULL);
		return(PASS);
	}
	
	HashMap_Destroy(&ptr,NULL,NULL);
	return(FAIL);
}
/* ---------------------------------------------------------------------*/
