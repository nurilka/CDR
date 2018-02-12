
#include "updater.h"
#include "ch_protocol.h"
#include "channelCDR.h"
#include "aggregator.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>		/* print log entries */


#define MAX_KEY_SIZE 16


struct UpdArgs
{
	int 		m_nEOFmsgs;
	int 		m_chID;
	Aggregator* m_aggr;
	pthread_mutex_t m_mutex;
	
}UpdArgs;


/*------------------------ local ----------------------*/
static CDR_Rec* RecMsg_Create (void)
{
	CDR_Rec* rcvMsg;
		
	rcvMsg = (CDR_Rec*)malloc(sizeof(CDR_Rec));
	if ( !rcvMsg )
	{
		return NULL;
	}
	return rcvMsg;
}

static int UpdateAggrEntry (UpdArgs* _updaterArgs, CDR_Rec* _rcvMsgPtr)
{
	Aggr_Res  aggrErr = AGGR_SUCCESS;
	char 	  key[MAX_KEY_SIZE] = {0};
	CDR_Rec*  getRec;
	

	aggrErr = Aggregator_Remove (_updaterArgs->m_aggr, _rcvMsgPtr->m_IMSI, (void**)&key, (void**)&getRec);
	if ( aggrErr == AGGR_SUCCESS )
	{
		_rcvMsgPtr->m_duration += getRec->m_duration;
		_rcvMsgPtr->m_upMB += getRec->m_upMB;
		_rcvMsgPtr->m_downMB += getRec->m_downMB;
		
		free (getRec);
	}
	else if (aggrErr != AGGR_NO_SUCH_ENTRY)
	{
		free (_rcvMsgPtr);
		return FAIL;
	}
	return SUCCESS;
}

static int InsertAggrEntry (UpdArgs* _updaterArgs, CDR_Rec* _rcvMsgPtr)
{
	Aggr_Res  aggrErr = AGGR_SUCCESS;
	
	aggrErr = Aggregator_Insert (_updaterArgs->m_aggr, _rcvMsgPtr->m_IMSI, _rcvMsgPtr);
	if ( aggrErr != AGGR_SUCCESS )
	{
		return FAIL;
	}
	return SUCCESS;
}

static CDR_Rec* CreateReceiveMsg (UpdArgs* _updaterArgs)
{
	CDR_Rec*  rcvMsg;
	int res = 0;
	
	rcvMsg = RecMsg_Create ();
	if ( !rcvMsg )
	{
		return NULL;
	}
	
	res = ChannelCDR_Receive (_updaterArgs->m_chID,  (void*)rcvMsg, sizeof(CDR_Rec) );
	if (res < 0)
	{
		free (rcvMsg);
		return NULL;
	}
	return rcvMsg;
}

static void UpdateInsertToAggr (UpdArgs* _updaterArgs, CDR_Rec* _rcvMsg)
{
	int res = SUCCESS;
	
	res = UpdateAggrEntry (_updaterArgs, _rcvMsg);
	if (res != SUCCESS)
	{
		return ;
	}
	
	res = InsertAggrEntry (_updaterArgs, _rcvMsg);
	if (res != SUCCESS)
	{
		return ;
	}
	return ;
}
	
/* --------------------- Updater API -----------------------*/
UpdArgs* UpdArgs_Create (int _channelID, int _nEOF, Aggregator* _aggr)
{
	UpdArgs* updaterArgs;
	int res = -1;
	
	if (!_aggr || _channelID < 0)
	{
		return NULL;
	}
	
	updaterArgs = (UpdArgs*)malloc(sizeof(UpdArgs));
	if (!updaterArgs)
	{
		return updaterArgs;
	}
	
	updaterArgs->m_chID = _channelID;
	updaterArgs->m_nEOFmsgs = _nEOF;
	updaterArgs->m_aggr = _aggr;
	if ((res = pthread_mutex_init( &updaterArgs->m_mutex, NULL)) < 0)
	{
		free (updaterArgs);
		return NULL;
	}
	
	return updaterArgs;
}


void UpdArgs_Destroy (UpdArgs* _updaterArgs)
{
	if (_updaterArgs)
	{
		pthread_mutex_dextroy( &_updaterArgs->m_mutex);
	
		free (_updaterArgs);
	}
}


void* Run_Updater (void* _updaterArgs)
{
	UpdArgs*  updaterArgs = (UpdArgs*)_updaterArgs;
	CDR_Rec*  rcvMsg;
	
	if ( !_updaterArgs )
	{
		return NULL;
	}
	
	while ( updaterArgs->m_nEOFmsgs )
	{
		rcvMsg = CreateReceiveMsg (updaterArgs);
		if (!rcvMsg)
		{
			return NULL;
		}
		
		/* check if EOF --> Y: decrease updaterArgs->m_nEOFmsgs */		
		if (rcvMsg->m_EOF)
		{
			pthread_mutex_lock (&updaterArgs->m_mutex);
			--updaterArgs->m_nEOFmsgs;
			pthread_mutex_unlock (&updaterArgs->m_mutex);
			continue;
		} 
		pthread_mutex_lock (&updaterArgs->m_mutex);
		
			UpdateInsertToAggr (updaterArgs, rcvMsg);
			
		pthread_mutex_unlock (&updaterArgs->m_mutex);
	}

	return NULL;
}


