
/** 
 *  @file hashMap.c
 *  @brief Generic Hash map of key-value pairs implemented with separate chaining using linked lists.
 *	
 *  @details  
 *
 *  @author Nurit (H-45), Adv.C-7, 	30.05.2017
 * 
 *  @bug No known bugs.
 */

#include <stddef.h>  	/* size_t */
#include <stdlib.h>		/*free(), malloc()*/

#include "hashMap.h"


#define		CALC_HASH_INDEX(MAP, KEY) ((MAP)->m_hashCode(KEY) % (MAP)->m_capacity)

struct HashMap 
{
	size_t 				m_capacity;
	HashFunction		m_hashCode;
	EqualityFunction	m_isEqual;
	List**				m_buckets;	
	size_t				m_nPairs;
	size_t				m_nChains;	
};

typedef struct Pair
{
	const void*	m_key;
	const void*	m_value;
} Pair;


/*--------------------- NON API Functions -----------------------*/
static Pair* Create_Pair ( const void* _key, const void* _value )
{
	Pair* pair;
	
	pair = (Pair*)malloc(sizeof(Pair));
	if ( !pair)
	{
		return NULL;
	}
	pair->m_key 	= _key;
	pair->m_value 	= _value;
	
	return pair;
}

static ListItr	Find_Link (const  HashMap* _map, size_t _ind, const void* _key)
{
	ListItr current;
	void*	data;
	
	current = ListItr_Begin (_map->m_buckets[_ind]);
	do 
	{
		data = ListItr_Get	(current); 		/*TODO curr++*/
		if ( _map->m_isEqual(data, _key) )
		{
			return current;
		}
	} while ( current );		/*TODO curr == end*/
	
	return NULL;
}

static size_t Calc_Max_Chain (const HashMap* _map)
{
	size_t index;
	size_t countMax = 0, max = 0; 

	for ( index = 0; index < _map->m_capacity; ++index )
	{
		countMax = List_Size (_map->m_buckets[index]);
		if ( max < countMax )	
		{
			max = countMax;
		}
	}
	return max;	
}

/*--------------------- API Functions ---------------------------*/
/** Create a new hash map with given capcity and key characteristics 
	return newly created map or null on failure */
HashMap* HashMap_Create (size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* 	map;
	
	if ( !_capacity || !_hashFunc || !_keysEqualFunc )
	{
		return NULL;
	}
	
	map = (HashMap*)malloc(sizeof(HashMap));
	if (! map)
	{
		return NULL;
	}
	
	map->m_capacity = _capacity;			/*TODO calloc before init*/
	map->m_hashCode = _hashFunc;
	map->m_isEqual 	= _keysEqualFunc;
	map->m_nPairs 	= 0;
	map->m_nChains 	= 0;
	
	map->m_buckets  = (List**)calloc(_capacity, sizeof(List*));
	if ( ! map->m_buckets )
	{
		free (map);
		return NULL;
	}
	return map;
}

/** destroy hash map and set *_map to null 
 	optionally destroy all keys and values using user provided functions */
void HashMap_Destroy (HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t 	index;
	Pair* 	data;
	void* 	key;
	void*   val;
	ListItr itr, itrNext;

	if ( _map && *_map )
	{
 		for ( index = 0; index < (*_map)->m_capacity; ++index )
		{
			itr = ListItr_Begin ((*_map)->m_buckets[index]);
			while (itr)			/*TODO check if itr!=end*/
			{
				itrNext = ListItr_Next(itr);
				data = (Pair*)ListItr_Remove (itr);
				key = data->m_key;
				val = data->m_value;
								
				if ( *_keyDestroy )			
				{	
					(*_keyDestroy)(key);
				}
				if ( *_valDestroy )
				{
					(*_valDestroy)(val);
				}
				itr = itrNext;
			}
			List_Destroy (&((*_map)->m_buckets[index]), NULL);
		}
		free (*_map);
		*_map = NULL;
	}
}
                   
/** Adjust map capacity and rehash all key/value pairs
	return MAP_SUCCESS or MAP_ALLOCATION_ERROR */
Map_Result HashMap_Rehash (HashMap *_map, size_t _newCapacity)
{
	size_t 		index = 0, currentCap;
	int			i;
	Pair*		data;
	ListItr		itr = NULL, itrNext = NULL;
	List**		tmpBuckets;
	List_Result	err = LIST_SUCCESS;
	
	if (!_map || !_newCapacity )
	{
		return MAP_ALLOCATION_ERROR;
	}
		
	tmpBuckets  = (List**)calloc(_newCapacity, sizeof(List*));
	if ( ! tmpBuckets)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	currentCap = _map->m_capacity;
	_map->m_capacity = _newCapacity;
	_map->m_nChains = 0;

	for ( i = 0; i < currentCap; ++i )
	{
		itr = ListItr_Begin (_map->m_buckets[i]);
		while (itr)					/*TODO check to end*/
		{
			itrNext = ListItr_Next(itr);
			data = (Pair*)ListItr_Remove (itr);
			itr = itrNext;
			
			index = CALC_HASH_INDEX ( _map, data->m_key ); 
			/* if the bucket empty - create new list */
			if (! tmpBuckets[index])
			{
				tmpBuckets[index] = List_Create();
				++_map->m_nChains;
			}
			/* add new link to chain */
			err = List_PushHead	( tmpBuckets[index], (void*)data);
			if ( LIST_SUCCESS != err )				/*TODO memory leak?*/
			{
				return MAP_ALLOCATION_ERROR;
			}
			/* TODO after for !!!!check empty list, if empty - destroy list in this bucket */
			if ( ListItr_Equals(itr, ListItr_Next(itr) ) )
			{
				List_Destroy( &(_map->m_buckets[i]), NULL);
				_map->m_buckets[index] = 0;
			}
		}
	}
	free(_map->m_buckets);
	_map->m_buckets = tmpBuckets;
	
	return MAP_SUCCESS;
}

/** Insert a key-value pair into the hash map: key must be unique and distinct */
Map_Result HashMap_Insert (HashMap* _map, const void* _key, const void* _value)
{
	size_t 		index = 0;
	ListItr		itr;
	List_Result	err = LIST_SUCCESS;
	Pair* 		pair;
	
	if (!_map )
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_key )
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = CALC_HASH_INDEX ( _map, _key );
	
	/* is the bucket empty */
	if (!_map->m_buckets[index])
	{
		_map->m_buckets[index] = List_Create();
		++_map->m_nChains;
	}
	
	/* return iterator to found key or NULL if unique */
	itr = Find_Link ( _map, index, _key );
	if ( itr )
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	/* create new pair */
	pair = Create_Pair ( _key, _value );
	if (!pair)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	/* add new link to chain */
	err = List_PushHead	(_map->m_buckets[index], (void*)pair);
	if ( LIST_SUCCESS != err )
	{
		return MAP_ALLOCATION_ERROR;			/*TODO free pair before return*/
	}
	++_map->m_nPairs;
	
	return MAP_SUCCESS;
}

/** Remove a key-value pair from the hash map */
Map_Result HashMap_Remove (HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	size_t 		index = 0;
	ListItr		itr, itrNext;
	Pair* 		data;
	
	if (!_map )
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_searchKey )
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = CALC_HASH_INDEX ( _map, _searchKey );
	
	/* return iterator to found key or NULL if unique */
	itr = Find_Link ( _map, index, _searchKey );
	if ( !itr )
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	/* get pointer to data found by key */
	itrNext = ListItr_Next(itr);
	data = (Pair*)ListItr_Remove	(itr);
	if (data)
	{       
		*_pKey 	= data->m_key;
		*_pValue = data->m_value;
		--_map->m_nPairs;
	}
	
	/* check empty list, if empty - destroy list in this bucket */
	if ( ListItr_Equals(itrNext, ListItr_Next(itrNext) ) )
	{
		List_Destroy( &(_map->m_buckets[index]), NULL);
		--_map->m_nChains;
		_map->m_buckets[index] = 0;
	}
	
	return MAP_SUCCESS;
}

/**  Find a value by key */
Map_Result HashMap_Find (const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t 		index = 0;
	ListItr		itr = NULL;
	Pair* 		data;
	
	if (!_map )
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_searchKey )
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = CALC_HASH_INDEX ( _map, _searchKey );
	
	/* return iterator to found key or NULL if unique */
	itr = Find_Link ((const HashMap*) _map, index, _searchKey );
	if ( !itr )
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	/* get pointer to data found by key */
	data = (Pair*)ListItr_Get	(itr);
	if (data)
	{       
		*_pValue = data->m_value;
	}
	
	return MAP_SUCCESS;
}


/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 */
size_t HashMap_Size (const HashMap* _map)
{
	return (_map) ? _map->m_nPairs : 0;
}


/** Iterate over all key-value pairs in the map and call user provided 
 * 	KeyValueActionFunction for each pair.
 * Iteration will stop if the called function returns a zero for a given pair
 * @returns number of times the user function was invoked */
/*typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);*/
size_t HashMap_ForEach (const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t 	counter = 0;
	int 	i;
	Pair*	data;
	ListItr itr;
	
	if ( ! _map || !_action )
	{
		return 0;
	}

	for ( i = 0; i < _map->m_capacity; ++i )
	{
		itr = ListItr_Begin (_map->m_buckets[i]);
		while (itr)					/*TODO check to end, itr->next*/
		{
			data = (Pair*)ListItr_Get (itr);
			if ( _action( data->m_key, data->m_value, _context) )
			{	
				++counter;				/*TODO break*/
			}
		}
	}
	return counter;
}


#define NDEBUG

Map_Stats HashMap_GetStatistics (const HashMap* _map)
{
	Map_Stats stats = {0};
	
	if (_map)
	{
		stats.numberOfBuckets = _map->m_capacity;	/* empty + not empty buckets */
		stats.numberOfChains = _map->m_nChains;	 /* none empty chains (having non zero length) */
		stats.averageChainLength = (_map->m_nPairs/_map->m_nChains);	/* average length of none empty chains */
		stats.maxChainLength = Calc_Max_Chain(_map);	/* length of longest chain */
	}
	return stats;
}


