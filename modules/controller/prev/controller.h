#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <stddef.h>  /* size_t */

/** 
 *  @file Manager.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author 
 * 
 *  @bug No known bugs.
 *
 */


typedef struct Manager Manager;

typedef struct
{
	size_t 	m_capacity;
	int 	m_readerThreads;
	int 	m_parserThreads;
	int 	m_updaterThreads;
	
}


/** 
 * @brief Create a new updater unit
 * @param[in]
 * @param[in] 
 * @param[in] 
 * @return newly created updater or null on failure
 */
int BillingSystem_Init ();


/**
 * @brief 
 * @param[in] 
 * @param[optional] 
 * @param[optional] 
 * @details 
 */
void BillingSystem_Shutdown ();

s
/**
 * @brief 
 * @param[in] 
 * @param[optional] 
 * @param[optional] 
 * @details 
 */
void BillingSystem_Pause ();


#endif /* __MANAGER_H__ */





