#ifndef __UPDATER_H__
#define __UPDATER_H__

/** 
 *  @file updater.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */
 
#include "aggregator.h"
#include "pthread.h"

typedef struct UpdArgs
{
	int 		m_runRes;
	int 		m_nEOFmsgs;
	int 		m_chID;
	Aggregator* m_aggr;
	pthread_mutex_t* m_mutex;
	
}UpdArgs;



/** 
 * @brief Run Updater
 * @param[in] _updaterArgs - arguments received from calling function 
 * @return status inside _updaterArgs;
 */
void* Run_Updater (void* _updaterArgs);



#endif /* __UPDATER_H__*/
