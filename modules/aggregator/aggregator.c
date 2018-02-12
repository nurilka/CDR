
/** 
 *  @file aggregator.c
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */

#include "aggregator.h"
#include "hashMap.h"


#include <stdlib.h>		/* free(), malloc()*/
#include <pthread.h>	/* mutex */


static size_t StrHashFunc (const void* _key)
{
	const char* str = _key;
    size_t hashCode = 5381;
    int c;

    while ( 0 != (c = *str++) )
        hashCode = ((hashCode << 5) + hashCode) + c; /* hashCode * 33 + c */

    return hashCode;
}



struct Aggregator
{
	HashMap*	  	m_map;
	pthread_mutex_t m_mutex;
};

/** Create a new aggregator with given capcity. */
Aggregator* Aggregator_Create (size_t _capacity, EqualityF _keysEqualFunc)
{
	Aggregator* aggr;
	
	if ( !_capacity || !_keysEqualFunc)
	{
		return NULL;
	}
	
	if ( !(aggr = (Aggregator*)malloc(sizeof(Aggregator))) )
	{
		return NULL;
	}
	
	if ( pthread_mutex_init (&aggr->m_mutex, NULL) != 0 )
	{
		free (aggr); 
		return NULL;
	}
	
	if (! (aggr->m_map = HashMap_Create (_capacity, StrHashFunc, _keysEqualFunc)) )
	{
		pthread_mutex_destroy(&aggr->m_mutex);
		free (aggr);
		return NULL;
	}
	return aggr;	
}


/** destroy aggregator and set *_aggr to null */
void Aggregator_Destroy (Aggregator** _aggrPtr)
{
	if (_aggrPtr && *_aggrPtr)
	{
		HashMap_Destroy (&(*_aggrPtr)->m_map, NULL, NULL);
		pthread_mutex_destroy(&(*_aggrPtr)->m_mutex);
		free (*_aggrPtr);
		*_aggrPtr = NULL;
	}
}

static Aggr_Res MapErr_toAggrErr (Map_Result _mapErr)
{
	Aggr_Res aggrErr;
	
	switch (_mapErr)
	{
		case MAP_SUCCESS:
				aggrErr = AGGR_SUCCESS;
				break;
		case MAP_KEY_DUPLICATE_ERROR:
				aggrErr = AGGR_INPUT_EXISTS;
				break;
		case MAP_KEY_NULL_ERROR:
				aggrErr = AGGR_NULL_INPUT;
				break;
		case MAP_KEY_NOT_FOUND_ERROR:
				aggrErr = AGGR_NO_SUCH_ENTRY;
				break;
		case MAP_ALLOCATION_ERROR:
				aggrErr = AGGR_ALLOC_ERR;
				break;
		case MAP_UNINITIALIZED_ERROR:
				aggrErr = AGGR_INVAL_ERR;
				break;
		default:
				break;
	}
	return aggrErr;
}

/**  Insert a key-value pair into the aggregator. */
Aggr_Res Aggregator_Insert (Aggregator* _aggr, const void* _key, const void* _value)
{
	Map_Result mapErr;
	Aggr_Res   aggrErr;
	
	/* other args are checked inside the HashMap function */
	if ( !_aggr )
	{
		return AGGR_INVAL_ERR;
	}
	
	pthread_mutex_lock (&_aggr->m_mutex);
	
		mapErr = HashMap_Insert (_aggr->m_map, _key,  _value);
		aggrErr = MapErr_toAggrErr (mapErr);
	
	pthread_mutex_unlock (&_aggr->m_mutex);
	
	return aggrErr;
}


/** Remove a key-value pair from the aggregator. */
Aggr_Res Aggregator_Remove (Aggregator* _aggr, const void* _searchKey, void** _pKey, void** _pValue)
{
	Map_Result mapErr;
	Aggr_Res   aggrErr;
	
	/* other args are checked inside the HashMap function */
	if ( !_aggr || !_searchKey )
	{
		return AGGR_INVAL_ERR;
	}
	
	pthread_mutex_lock (&_aggr->m_mutex);
	
		mapErr = HashMap_Remove (_aggr->m_map, _searchKey, _pKey,  _pValue);
		aggrErr = MapErr_toAggrErr (mapErr);
	
	pthread_mutex_unlock (&_aggr->m_mutex);
	
	return aggrErr;
}








