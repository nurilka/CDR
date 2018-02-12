
/** 
 *  @file reporter.c
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */

#include "reporter.h"
#include "ch_protocol.h"
#include "channelCDR.h"
#include "aggregator.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>


#define MAX_KEY_SIZE 16


typedef struct RepArgs
{
	int 	m_chID;
	int 	m_doReport;
	void* 	m_searchKey;
	Aggregator* m_aggr;
	pthread_mutex_t m_mutex;
	pthread_cond_t 	m_cond;
}RepArgs;


/*------------------------ static -------------------------*/
static CDR_Rec* SendMsg_Create (void)
{
	CDR_Rec* sendMsg;
		
	sendMsg = (CDR_Rec*)malloc(sizeof(CDR_Rec));
	if ( !sendMsg )
	{
		return NULL;
	}
	return sendMsg;
}


static int GetAggrEntry (RepArgs* _reporterArgs, CDR_Rec* _getRecPtr, void* _searchKey)
{
	Aggr_Res  aggrErr;
	char 	  key[MAX_KEY_SIZE] = {0};

	aggrErr = Aggregator_Remove (_reporterArgs->m_aggr, _searchKey,  (void**)&key, (void**)&_getRecPtr);
	if (aggrErr != SUCCESS)
	{
		printf ("no such key \n");
		return FAIL;
	}
	return SUCCESS;
}


static int SendRepToUIChannel (RepArgs* _reporterArgs, CDR_Rec* _sendMsg)
{
	int res; 
	
	if ( !_sendMsg )
	{
		return FAIL;
	}
	
	res = ChannelCDR_Send (_reporterArgs->m_chID, (void*)_sendMsg, sizeof(CDR_Rec));
	if (res < 0 ) 
	{
		free (_sendMsg);
		return FAIL;
	}
	free (_sendMsg);
	return SUCCESS;
}

/*--------------------- Reporter API -----------------------*/
void RepWaitAction (RepArgs* _reporterArgs, int* _repStatus)
{
	pthread_mutex_lock (&reporterArgs->m_mutex);
	
	   reporterArgs->m_doReport = *_repStatus;
	   pthread_cond_broadcast (&reporterArgs->m_cond);

	pthread_mutex_unlock (&reporterArgs->m_mutex);
}

	
RepArgs* RepArgs_Create (int _channelID, Aggregator* _aggr )
{
	RepArgs* reporterArgs;
	int res = -1;
	
	if ( !_aggr || _channelID < 0)
	{
		return NULL;
	}
	
	reporterArgs = (RecArgs*)malloc(sizeof(RecArgs));
	if (!reporterArgs)
	{
		return reporterArgs;
	}
	
	reporterArgs->m_chID = _channelID;
	reporterArgs->m_doReport = 0;
	reporterArgs->m_aggr = _aggr;
	if ((res = pthread_mutex_init( &reporterArgs->m_mutex, NULL)) < 0)
	{
		free (reporterArgs);
		return NULL;
	}
	if ((res = pthread_cond_init( &reporterArgs->m_cond, NULL)) < 0)
	{
		pthread_mutex_destroy ( &reporterArgs->m_mutex);
		free (reporterArgs);
		return NULL;
	}
	return reporterArgs;
}


void RepArgs_Destroy (RepArgs* _reporterArgs)
{
	if (_reporterArgs)
	{
		pthread_mutex_dextroy( &_reporterArgs->m_mutex);
		pthread_cond_destroy ( &_reporterArgs->m_cond);
	
		free (_reporterArgs);
	}
}


void* Run_Reporter (void* _reporterArgs)
{
	RecArgs*  reporterArgs = (RecArgs*)_reporterArgs;
	CDR_Rec*  getRecMsg;
	int res = -1;
	
	if ( !_reporterArgs )
	{
		return NULL;
	}
	/*TODO add switch case for different user options --> move this code to Report_Create*/
	while (1)
	{
		while (reporterArgs->m_doReport != 1)
		{
			/* wait fro predicate to change, TODO timedwait */
			pthread_cond_wait (&reporterArgs->m_cond, &reporterArgs->m_mutex);
		}
	
		getRecMsg = CreateSendMsg (reporterArgs);
		if (!getRecMsg)
		{
			return NULL;
		}
	
		res = GetAggrEntry (reporterArgs, getRecMsg, reporterArgs->m_searchKey);
		if (res != SUCCESS)
		{
			free (getRecMsg);
		}
		res = SendRepToUIChannel (reporterArgs, getRecMsg);
		if (res != SUCCESS)
		{
			free (getRecMsg);
		}
		free (getRecMsg);
	}
	return NULL;
}


