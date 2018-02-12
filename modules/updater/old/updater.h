#ifndef __UPDATER_H__
#define __UPDATER_H__

#include <stddef.h>  /* size_t */

/** 
 *  @file Updater.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author 
 * 
 *  @bug No known bugs.
 *
 * Get UBI instance from Q
 * Put in storage

 */


typedef struct Updater Updater;


typedef size_t (*StoreFunction)(void* _arg);

typedef enum Upd_Res {
	UPD_SUCCESS = 0,
	UPD_UNINITIALIZED_ERROR, 		/**< Uninitialized updater error*/
	UPD_ALLOCATION_ERROR, 			/**< Allocation error 	 		*/
	UPD_THREADS_ERROR				/**< Threads create error 		*/
} Upd_Res;

/** 
 * @brief Create a new updater unit
 * @param[in]
 * @param[in] 
 * @param[in] 
 * @return newly created updater or null on failure
 */
Updater* Updater_Create (size_t _capacity, );


/**
 * @brief destroy updater and set *_updater to null
 * @param[in] _updater : updater to be destroyed
 * @param[optional] 
 * @param[optional] 
 * @details 
 */
void Updater_Destroy (Updater** _map, );


/** 
 * @brief Insert a key-value pair into the hash map.
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  UPD_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failure to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Upd_Res Updater_Store (Updater* _updater, const void* _key, const void* _value);


/** 
 * @brief Remove a key-value pair from the hash map.
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_UNINITIALIZED_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * 
 */
Upd_Res Updater_GetData (Updater* _updater, );





#endif /* __HASHMAP_H__ */





