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

#include "ch_protocol.h" 	/* CDR_Rec struct in h*/
#include "uich_protocol.h"	/* UserOpt struct in h */
#include "repch_protocol.h"
#include "channelCDR.h"
#include "aggregator.h"
#include "updater.h"		/* UpdArgs struct in h */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>		/* strcmp */


#define AGGR_SIZE	 10
#define NUM_UPDATERS 2
#define NUM_REPORTERS 1
#define NUM_EOF	1


/*--------------- Aggregator -----------------------------*/
int isEqual (const void* _firstKey, const void* _secondKey)
{
	char* key1 = (char*)_firstKey;
	char* key2 = (char*)_secondKey;
	
	return (strcmp(key1, key2) == 0) ? 1: 0;
}

/*--------------- Channels -------------------------------*/
typedef struct chIDs
{
	int m_idRdUpd;
	int m_idUIctrl;
	int m_idRepUI;
}chIDs;

typedef struct chKey
{
	char m_keyRdUpd;
	char m_keyUIctrl;
	char m_keyRepUI;	
}chKey;

static int OpenCommChannels (chIDs* _channels, chKey* _keys )
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

static void CloseCommChannels (chIDs* _channels)
{
	ChannelCDR_Close (_channels->m_idRdUpd);
	ChannelCDR_Close (_channels->m_idUIctrl);
	ChannelCDR_Close (_channels->m_idRepUI);
}

/*--------------- Threads -----------------------------*/
int Updaters_Start (pthread_t* _updaters, UpdArgs* _args, int _nUpdaters)
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


static int Reporters_Start (pthread_t* _reporters, RepArgs* _args, int _nReporters)
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
}

static void JoinAllThreads (pthread_t* _thrIDs, int _nThreads)
{
	int i;
	
	for (i = 0; i < _nThreads; ++i )
	{
		pthread_join (_thrIDs[i], NULL);
	}
}


/*---------------------- API ---------------------*/
typedef struct Controller
{
	chIDs m_channels;
	chKey m_keyIDs;
	Aggregator* m_aggr;
	int m_aggrSize;
	UpdArgs* m_updaterArgs;
	RepArgs* m_reporterArgs;
	
}Controller;

Controller* Controller_Create (FILE* _cnfg, EqualityF _isEqual, int _numEOF)
{
	int  	chRes = 0, res = 0;

	Controller* ctrl;
	
	ctrl = (Controller*)malloc(sizeof(Controller));
	if (!ctrl)
	{
		return NULL;
	}
	
	/* open cnfg file to read params: aggrSize, keys*/

	ctrl->m_keyIDs.m_keyRdUpd = 'X';
	ctrl->m_keyIDs.m_keyUIctrl = 'Y';
	ctrl->m_keyIDs.m_keyRepUI = 'Z';
	
	chRes = OpenCommChannels (&ctrl->m_channels, &ctrl->m_keyIDs);
	if (chRes != SUCCESS )
	{
		free (ctrl);
		return FAIL;
	}
	
	ctrl->m_aggr = Aggregator_Create (AGGR_SIZE, _isEqual);
	if (!ctrl->m_aggr)
	{
		CloseCommChannels (&ctrl->m_channels);
		free (ctrl);
		return FAIL;
	}
	
	ctrl->m_updaterArgs = UpdArgs_Create (ctrl->m_channels.m_idRdUpd, _numEOF, ctrl->m_aggr);
	if (! ctrl->m_updaterArgs )
	{
		Aggregator_Destroy(&ctrl->m_aggr);
		CloseCommChannels (&ctrl->m_channels);
		free (ctrl);
		return FAIL;
	}

 	ctrl->m_reporterArgs = RepArgs_Create (ctrl->m_channels.m_idRepUI, _numEOF, ctrl->m_aggr);
	if (!ctrl->m_reporterArgs)
	{
		UpdaterArgs_Destroy(ctrl->m_updaterArgs);
		Aggregator_Destroy(&ctrl->m_aggr);
		CloseCommChannels (&ctrl->m_channels);
		free (ctrl);
		return FAIL;
	}
	return ctrl;
}


void Controller_Destroy (Controller* _ctrl)
{
	if (!_ctrl)
	{
		return;
	}
	
	UpdArgs_Destroy (ctrl->m_updaterArgs);
 	RepArgs_Destroy (ctrl->m_reporterArgs);
	Aggregator_Destroy(&ctrl->m_aggr);
	CloseCommChannels (&ctrl->m_channels);
	free (ctrl);
}


void Controller_ReceiveUReq (Controller* _ctrl)
{
	int cont = TRUE, length = 0;
	UserOpt uOpt;
	
	while (cont)
	{
		/* wait for instructions in channel UI-->ctrl */
		ChannelCDR_Receive (_ctrl->m_channels.m_idUIctrl,  &uOpt, sizeof(UserOpt) );
		printf( "received: %d\n", uOpt.m_uOpt);
		
		switch( uOpt.m_uOpt )
		{
			case SHUT_DOWN:
				printf("shut down in progress\n");
				cont = FALSE;
				break;
				
			case PAUSE:
				/* TODO pause the system */
				break;
				
			case RESUME:
				/* TODO resume the system */	
				break;
			
			case SUBSCR_REPORT:
				length = strlen( uOpt.m_ID);
				memcpy( _ctrl->m_reporterArgs->m_IMSI, uOpt.m_ID , length +1 );
				RepWaitAction ( _ctrl->m_reporterArgs, (int*)&uOpt.m_uOpt)
				printf("report required\n");
				break;

			case OPER_REPORT:
				/* TODO do operator rep */	
				break;
				
			default:
				break;		
		}
	}
}

int SetupWorkflow (Controller* ctrl, int nUpdaters, int nReporters)
{
	int res;
	
	res = UpdatersStart (updaters, ctrl->updaterArgs, NUM_UPDATERS);
 	if (res != SUCCESS)
 	{
 		Controller_Destroy (ctrl);
 		return FAIL;
 	}
	
 	res = ReportersStart (reporters, ctrl.reporterArgs, NUM_REPORTERS);
 	if (res != SUCCESS)
 	{
		JoinAllThreads (updaters, NUM_UPDATERS);
 		Controller_Destroy (ctrl);
 		return FAIL;
 	} 
 	return res;
}



/*------------------------ MAIN ------------------------------*/
int main (void)
{
	Controller* ctrl;
	int 	repStatus = 1;
	FILE* 	cnfg;
	
 	pthread_t 	updaters[NUM_UPDATERS];
 	pthread_t 	reporters[NUM_REPORTERS];
 	
	
	ctrl = Controller_Create (cnfg, isEqual, NUM_EOF);
	if (!ctrl)
	{
		return FAIL;
	}
	
	
 	
 	/* TODO receive user request, update params, so the required info could be acquired.
 		create condition, under which all this runs/stops/shuts down */	
	Controller_ReceiveUReq (_ctrl);
 	
 		
 	JoinAllThreads (updaters, NUM_UPDATERS);
	JoinAllThreads (reporters, NUM_REPORTERS); 
 	Controller_Destroy (ctrl);
 
 	return 0;	
 }
 
 
 
