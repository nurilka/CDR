/** 
 *  @file contoller.c
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */

#include "ch_protocol.h" /* CDR_Rec struct in h*/
#include "channelCDR.h"
#include "aggregator.h"
#include "updater.h"	/* UpdArgs struct in h --> TODO make another API func: SetUpdArgs --> move inside*/

#include <pthread.h>
#include <stdlib.h>
#include <string.h>		/* strcmp */


#define AGGR_SIZE	 10
#define NUM_UPDATERS 2
#define NUM_REPORTERS 1
#define NUM_EOF	5


/*--------------- Aggregator -----------------------------*/
int isEqual (const void* _firstKey, const void* _secondKey)
{
	char* key1 = (char*)_firstKey;
	char* key2 = (char*)_secondKey;
	
	return (strcmp(key1, key2) == 0) ? 1: 0;
}

/*--------------- Channels -------------------------------*/
typedef struct chID
{
	int m_idRdUpd;
	int m_idUIctrl;
	int m_idRepUI;
}chID;

typedef struct chKey
{
	char m_keyRdUpd;
	char m_keyUIctrl;
	char m_keyRepUI;	
}chKey;

static int OpenCommChannels (chID* _channels, chKey* _keys )
{
	_channels->m_idRdUpd = ChannelCDR_Open (FILE_NAME, _keys->m_keyRdUpd);
	if (_channels->m_idRdUpd < 0)
	{
		return FAIL;
	}
	
	_channels->m_idUIctrl = ChannelCDR_Open (FILE_NAME, _keys->m_keyUIctrl);
	if (_channels->m_idUIctrl < 0)
	{
		ChannelCDR_Close (_channels->m_idRdUpd);
		return FAIL;
	}
	
	_channels->m_idRepUI = ChannelCDR_Open (FILE_NAME, _keys->m_keyRepUI);
	if (_channels->m_idRdUpd < 0)
	{
		ChannelCDR_Close (_channels->m_idRdUpd);
		ChannelCDR_Close (_channels->m_idUIctrl);
		return FAIL;
	}
	return SUCCESS;
}

static void CloseCommChannels (chID* _channels)
{
	ChannelCDR_Close (_channels->m_idRdUpd);
	ChannelCDR_Close (_channels->m_idUIctrl);
	ChannelCDR_Close (_channels->m_idRepUI);
}

/*--------------- Updater -----------------------------*/
static UpdArgs* SetUpdArgs (chID _channelID, int _nEOF, Aggregator* _aggr, pthread_t* _mutex)
{
	UpdArgs* updaterArgs;
	
	updaterArgs = (UpdArgs*)malloc(sizeof(UpdArgs));
	if (!updaterArgs)
	{
		return updaterArgs;
	}
	
	updaterArgs->m_runRes = SUCCESS;
	updaterArgs->m_chID = _channelID;
	updaterArgs->m_nEOFmsgs = _nEOF;
	updaterArgs->m_aggr = _aggr;
	updaterArgs->m_mutex = _mutex;
	
	return updaterArgs;
}


static int UpdatersStart (pthread_t* _updaters, UpdArgs* _args, int _nUpdaters)
{
	int i;
	
	for (i = 0 ; i < _nUpdaters ; i++)
	{
		if ( pthread_create ((_updaters + i), NULL, Run_Updater, (void*)_args ) != 0)
		{
			return FAIL;
		}
	}
	return SUCCESS;
}

/*--------------- Reporter -----------------------------
static RepArgs* SetRepArgs ( )
{
	return reporterArgs;
}


static int ReportersStart (pthread_t* _reporters, RepArgs* _args, int _nReporters)
{
	int i;
	
	for (i = 0 ; i < _nReporters ; i++)
	{
		if ( pthread_create ((_reporters + i), NULL, Run_Reporter, (void*)_args ) != 0)
		{
			return FAIL;
		}
	}
	return SUCCESS;
}*/

/*--------------- Threads and Sync -----------------------------
typedef struct SyncParams
{
	pthread_mutex_t m_mutex;	
	pthread_cond_t m_cond;		
}SyncParams; 

static SyncParams* SyncParams_Init (void)
{
	int res;
	SyncParams* syncData;
	

	if ( !(syncData = (SyncParams*)malloc(sizeof(SyncParams))) )
	{
		return NULL;
	}

	if ((res = pthread_mutex_init( &syncData->m_mutex, NULL)) < 0)
	{
		free (syncData);
		return NULL;
	}
	
	if ((res = pthread_mutex_init( &syncData->m_mutex, NULL)) < 0)
	{
		SyncParams_Destroy (syncData);
		return NULL;
	}
	
	if ((res = pthread_cond_init(&syncData->m_cond, NULL)) < 0)
	{
		SyncParams_Destroy (syncData);
		return NULL;
	}
	return syncData;
}


static void SyncParams_Destroy (SyncParams* _syncData)
{
	if (_syncData)
	{
		pthread_cond_destroy(&_syncData->m_cond);
		pthread_mutex_destroy(&_syncData->m_mutex);
		free (_syncData);
	}
} */


static void JoinAllThreads (pthread_t* _thrIDs, int _nThreads)
{
	int i;
	
	for (i = 0; i < _nThreads; ++i )
	{
		pthread_join (_thrIDs[i], NULL);
	}
}

/*----------- Server -------------------
typedef ServerArgs
{
	int 		m_nReporters;
	int 		m_nUpdaters;
	pthread_t* 	m_reporters;
	pthread_t* 	m_updaters;
	chID* 	 	m_channels;
	Aggregator* m_aggr;

}ServerArgs;

static ServerArgs* StartServer (int _numRep, int _numUpd, AggrArgs* _aggrParam, )
{
	ServerArgs* srvArgs;
	Aggregator* aggr;
	
	if( !(srvArgs = (ServerArgs*)malloc(sizeof(ServerArgs))) )
	{
		return NULL;
	}
	
	srvArgs->m_nReporters = _numRep;
	srvArgs->m_nUpdaters = _numUpd;
	aggr = Aggregator_Create (_aggrParam->m_size, _aggrParam->m_isEqual);
	if (!aggr)
	{
		return NULL;
	}
	
	
	
	
	return srvArgs;
}  */

/* TODO from Cleanup to Shut Down ...*/
/*static void ServerCleanup (ServerArgs* _srvArgs)
{
	CloseCommChannels (_srvArgs->m_channels);
	JoinAllThreads( _srvArgs->m_updaters, _srvArgs->m_nUpdaters);
	JoinAllThreads (_srvArgs->m_reporters, _srvArgs->m_nReporters);
	Aggregator_Destroy (_srvArgs->m_aggr);
	if (_updaterArgs)
	{
		free (_updaterArgs);
	}
	if (_reporterArgs)
	{
		free (_updaterArgs);
	}
	if (_srvArgs)
	{
		free(_srvArgs);
	}
}*/


/*------------------------ MAIN ------------------------------*/
int main (void)
{
	chID	channels = {0};
	chKey 	keyIDs;
	Aggregator* aggr;
	pthread_mutex_t mutex;
	UpdArgs* updaterArgs;

 	pthread_t 	updaters[NUM_UPDATERS];
 	pthread_t 	reporters[NUM_REPORTERS];
 	

	/*ServerArgs* srvArgs;*/

	int  	res = 0;

		
	/* start Controller->Readers process */
	/* 
		1. open channel  Controller -> Readers
		2. readers wait on channel for START message from manager
	*/
	
	/* get keys from the cnfg file */
	keyIDs.m_keyRdUpd = 'X';
	keyIDs.m_keyUIctrl = 'Y';
	keyIDs.m_keyRepUI = 'Z';
	
	chRes = OpenCommChannels (&channels, &keyIDs);
	if (chRes != SUCCESS )
	{
		return FAIL;
	}
	
	/*srvArgs = 
	if (!srvArgs)
	{
		 CloseCommChannels (&channels);
		 return FAIL;
	}*/
	
	aggr = Aggregator_Create (_aggrParam->m_size, _aggrParam->m_isEqual);
	if (!aggr)
	{
		CloseCommChannels (&channels);
		return NULL;
	}
	
	if ((res = pthread_mutex_init( &mutex, NULL)) < 0)
	{
 		CloseCommChannels (&channels);
		return NULL;
	}
	updaterArgs = SetUpdArgs (channels.m_idRdUpd, NUM_EOF, aggr, &mutex);
	if (!updaterArgs)
	{
		CloseCommChannels (&channels);
		return NULL;
	}
	
 	res = UpdatersStart (updaters, updaterArgs, NUM_UPDATERS);
 	if (res != success)
 	{
 		CloseCommChannels (&channels);
 		return FAIL;
 	}
 	
 	/*res = ReportersStart (reporters, reporterArgs, NUM_REPORTERS);
 	if (res != success)
 	{
 		ServerCleanup (ServerArgs* _srvArgs)
 		return FAIL;
 	} */
 	
 	/* receive user request, update params, so the required info could be acquired.
 		create condition, under which all this runs/stops/shuts down */
 	
	/*ServerCleanup (srvArgs); */
	JoinAllThreads( updaters, NUM_UPDATERS);
	JoinAllThreads (reporters, NUM_REPORTERS);
	
	return 0;
}







