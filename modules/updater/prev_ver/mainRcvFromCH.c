
#include "ch_protocol.h"
#include "channelCDR.h"
#include "aggregator.h"


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>


int isEqual (const void* _firstKey, const void* _secondKey)
{
	char* key1 = (char*)_firstKey;
	char* key2 = (char*)_secondKey;
	
	return (strcmp(key1, key2) == 0) ? 1: 0;
}



/*------------------------ MAIN ------------------------------*/
int main (void)
{
	CDR_Rec*  rcvMsg;
	CDR_Rec*  getRec;
	char 	  key[16] = {0};
	Aggr_Res  aggrErr = AGGR_SUCCESS;
	int 	  aggrSize = 10, chID = -1, res = 0, i;
	Aggregator*	aggr;
	
		
	aggr = Aggregator_Create (aggrSize, isEqual);
	if (!aggr)
	{
		return FAIL;
	}
	
	chID = ChannelCDR_Open (FILE_NAME, KEY_ID);
	if (chID < 0)
	{
		perror("channel open");
		return FAIL;
	}
	
	 
	for (i = 0; i < 3; ++i)
	{
		rcvMsg = (CDR_Rec*)malloc(sizeof(CDR_Rec));
		if ( !rcvMsg )
		{
			return FAIL;
		}
		
		res = ChannelCDR_Receive (chID,  (void*)rcvMsg, sizeof(CDR_Rec) );
		if (res < 0)
		{
			perror("channel receive");
			ChannelCDR_Close (chID);
			return FAIL;
		}
		printf("1:brand: %s\n", rcvMsg->m_brandName);
		printf ("1: IMEI: %s\n", rcvMsg->m_IMEI);
		printf ("1: downMB: %d	\n", rcvMsg->m_downMB);
		
		aggrErr = Aggregator_Remove (aggr, rcvMsg->m_IMSI, (void**)&key, (void**)&getRec);
		if ( aggrErr == AGGR_SUCCESS )
		{
			printf ("before: downMB: %d	\n", getRec->m_downMB);
			rcvMsg->m_duration += getRec->m_duration;
			printf ("added: duration: %d	\n", rcvMsg->m_downMB);
			rcvMsg->m_upMB += getRec->m_upMB;
			rcvMsg->m_downMB += getRec->m_downMB;
			printf ("added: downMB: %d	\n", rcvMsg->m_downMB);
			
			free (getRec);
		}
		else if (aggrErr != AGGR_NO_SUCH_ENTRY)
		{
			free (rcvMsg);
			return FAIL;
		}
		aggrErr = Aggregator_Insert (aggr, rcvMsg->m_IMSI, rcvMsg);
		if ( aggrErr != AGGR_SUCCESS )
		{
			free (getRec);
			free (rcvMsg);
			return FAIL;
		}
	}
	aggrErr = Aggregator_Remove (aggr, rcvMsg->m_IMSI, (void**)&key, (void**)&getRec);
	printf ("2: IMSI: %s\n", getRec->m_IMSI);
	printf("2: downMB: %d\n", getRec->m_downMB);		

	/* ChannelCDR_Close (chID); */
	
	return 0;
}


