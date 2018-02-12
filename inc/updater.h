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
 
#include <pthread.h>
#include "aggregator.h"


typedef struct UpdArgs UpdArgs;

/** 
 * @brief Create updaterArgs
 * @param[in] _channelID - channel id: channel reader --> updater
 * @param[in] _nEOF - number of EOF messages to wait for
 * @param[in] _aggr - pointer to aggregator                   
 * @return allocated and initiated updaterArgs;
 */
UpdArgs* UpdArgs_Create (int _channelID, int _nEOF, Aggregator* _aggr);

/** 
 * @brief Destroy updaterArgs
 * @param[in] _updaterArgs - arguments received from calling function 
 * @return void;
 */
void UpdArgs_Destroy (UpdArgs* _updaterArgs);

/** 
 * @brief Run Updater
 * @param[in] _updaterArgs - arguments received from calling function 
 * @return void
 */
void* Run_Updater (void* _updaterArgs);



#endif /* __UPDATER_H__*/
