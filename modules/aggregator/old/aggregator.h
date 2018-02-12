#ifndef __AGGREGATOR_H__
#define __AGGREGATOR_H__

/** 
 *  @file aggregator.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */

#include <stddef.h>  	/* size_t */

typedef struct Aggregator Aggregator;

typedef enum Aggr_Res {
	AGGR_SUCCESS = 0,
	AGGR_INVAL_ERR, 		/**< Uninitialized aggregator error 	*/
	AGGR_NULL_INPUT, 		/**< Key was null 				*/
	AGGR_INPUT_EXISTS, 		/**< Duplicate key error 		*/
	AGGR_NO_SUCH_ENTRY, 	/**< Key not found 				*/
	AGGR_ALLOC_ERR 			/**< Allocation error 	 		*/
} Aggr_Res;




typedef int (*EqualityF)(const void* _firstKey, const void* _secondKey);
/** 
 * @brief Create a new aggregator with given capcity.
 * @param[in] _capacity - Expected max capacity 
 * @return newly created aggregator or null on failure
 */
Aggregator* Aggregator_Create (size_t _capacity, EqualityF _keysEqualFunc);


/**
 * @brief destroy aggregator *_aggr to null
 * @param[in] _aggr : aggregator to be destroyed
 */
void Aggregator_Destroy (Aggregator** _aggrPtr);


/** 
 * @brief Insert a key-value pair into the aggregator.
 * @param[in] _aggr - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  AGGR_SUCCESS	on success
 * @retval  AGGR_INPUT_EXISTS	if key already present in the aggregator
 * @retval  AGGR_NULL_INPUT
 * @retval  AGGR_ALLOC_ERR on failure to allocate key-value pair
 * @retval  AGGR_INVAL_ERR
 * 
 * @warning key must be unique and destinct
 */
Aggr_Res Aggregator_InsertData (Aggregator* _aggr, const void* _key, const void* _value);


/** 
 * @brief Remove a key-value pair from the aggregator.
 * @param[in] _aggr - Aggregator to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the aggregator
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  AGGR_SUCCESS	on success
 * @retval  AGGR_NULL_INPUT
 * @retval  AGGR_INVAL_ERR
 * @retval  AGGR_NO_SUCH_ENTRY if key not found
 * 
 * @warning key must be unique and distinct
 */
Aggr_Res Aggregator_GetData (Aggregator* _aggr, const void* _searchKey, void** _pKey, void** _pValue);




#endif /* __AGGREGATOR_H__ */
