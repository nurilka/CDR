#ifndef __REPORTER_H__
#define __REPORTER_H__

/** 
 *  @file reporter.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */
 
#include "aggregator.h"


typedef struct RepArgs RepArgs;

/** 
 * @brief Create reporterArgs
 * @param[in] _channelID - channel id: channel reporter --> user interface
 * @param[in] _aggr - pointer to aggregator                   
 * @return allocated and initiated reporterArgs;
 */
RepArgs* RepArgs_Create (int _channelID, Aggregator* _aggr );


/** 
 * @brief Run Reporter
 * @param[in] _reporterArgs - 
 */
void RepArgs_Destroy (RepArgs* _reporterArgs);


/** 
 * @brief Run Reporter
 * @param[in] _reporterArgs 
 */
void* Run_Reporter (void* _reporterArgs);

void RepWaitAction (RepArgs* _reporterArgs, int* _repStatus);

#endif /* __REPORTER_H__*/
