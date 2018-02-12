
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
	
	return (strcmp(*key1,*key2) == 0) ? 1 : 0;
}

/*------------------------ MAIN ------------------------------*/
int main (void)
{
	CDR_Rec  rcvMsg;
	CDR_Rec*  getRec;
	char 	 key[16] = {0};
	Aggr_Res aggrErr = AGGR_SUCCESS;
	Aggregator*	aggr;
	int 	chID = -1, res = 0, i, aggrSize = 10;
	
	
	
	aggr = Aggregator_Create (aggrSize, isEqual);
	if (!aggr)
	{
		return FAIL;
	}
	
	chID = ChannelCDR_Open (FILE_NAME);
	if (chID < 0)
	{
		perror("channel open");
		return FAIL;
	}
	
	for (i = 0; i < 2; ++i)
	{
		res = ChannelCDR_Receive (chID,  (void*)&rcvMsg, sizeof(CDR_Rec) );
		if (res < 0)
		{
			perror("channel receive");
			ChannelCDR_Close (chID);
			return FAIL;
		}
		printf("brand: %s\n", rcvMsg.m_brandName);
		printf ("IMSI: %s\n", rcvMsg.m_IMSI);
		
		aggrErr = Aggregator_Remove (aggr, &rcvMsg.m_IMSI, (void**)&getRec->m_IMSI, (void**)&getRec);
		if ( (aggrErr != AGGR_NO_SUCH_ENTRY) && (aggrErr == AGGR_SUCCESS) )
		{
			getRec->m_duration += rcvMsg.m_duration;
			getRec->m_upMB += rcvMsg.m_upMB;
			getRec->m_downMB += rcvMsg.m_downMB;
		}
		else if (aggrErr == AGGR_NO_SUCH_ENTRY)
		{
			aggrErr = Aggregator_Insert (aggr, &rcvMsg.m_IMSI, &rcvMsg);
		}
		
		aggrErr = Aggregator_Insert (aggr, getRec->m_IMSI, getRec);
		if ( aggrErr != AGGR_SUCCESS)
		{
			return FAIL;
		}
	}
		
	/*ChannelCDR_Close (chID); */
	
	return 0;
}


