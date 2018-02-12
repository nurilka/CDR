
#include "ch_protocol.h"
#include "channelCDR.h"
#include "aggregator.h"


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define KEY_ID	'X'

static CDR_Rec* CDR_Rec_Create (int _fl)
{
	CDR_Rec* msgPtr;
	
	
	msgPtr = (CDR_Rec*)malloc(sizeof(CDR_Rec));
	if ( !msgPtr )
	{
		return NULL;
	}

	if (_fl)
	{
		strcpy(msgPtr->m_IMSI, "0523334479");
		strcpy(msgPtr->m_IMEI, "123344777777889");
		strcpy(msgPtr->m_date, "2017/13/07");
		strcpy(msgPtr->m_time, "09:18:32");
		msgPtr->m_cType = MTC;
		
	}
	else
	{
		strcpy (msgPtr->m_IMSI, "0526659870") ;
		strcpy (msgPtr->m_IMEI, "444444777777889");
		strcpy(msgPtr->m_date, "2016/06/10");
		strcpy(msgPtr->m_time, "13:57:18");
		msgPtr->m_cType = MOC;
	}
	
	strcpy (msgPtr->m_MCCMNC, "44576");
	strcpy (msgPtr->m_brandName, "Golan Telecom");
	strcpy (msgPtr->m_MSISDN, "123123123123");
		srand(time(NULL));
	msgPtr->m_duration = rand()%150 + 600;
	msgPtr->m_upMB = 20;
		srand(time(NULL));
	msgPtr->m_downMB = rand()%100+150;
	msgPtr->m_EOF = 0;
	
	return msgPtr;
}
/*------------------------ MAIN ------------------------------*/
int main (void)
{
	CDR_Rec* sndMsg;
	int 	chID, res = 0, fl = 0, i;
	
	
	chID = ChannelCDR_Open (FILE_NAME, KEY_ID);
	if (chID < 0)
	{
		perror("channel open");
		return FAIL;
	}
	
	for (i = 0; i < 3; ++i)
	{
		fl = i%2;
		sndMsg = CDR_Rec_Create (fl);
	
		res = ChannelCDR_Send (chID,  (void*) sndMsg, sizeof(CDR_Rec) );
		if (res != 0)
		{
			perror("channel send");
			free(sndMsg);
			ChannelCDR_Close (chID);
			return FAIL;
		}
		printf ("brand: %s\n", sndMsg->m_brandName);
		printf ("IMEI: %s\n", sndMsg->m_IMEI);
		printf ("IMSI: %s\n", sndMsg->m_IMSI);
		free(sndMsg);
	}
	
	/* send EOF */
	for (i = 0; i < 10; ++i)
	{
		sndMsg = (CDR_Rec*)malloc(sizeof(CDR_Rec));
		sndMsg->m_EOF = 1;
	
		res = ChannelCDR_Send (chID,  (void*) sndMsg, sizeof(CDR_Rec) );
		if (res != 0)
		{
			perror("channel send");
			free(sndMsg);
			ChannelCDR_Close (chID);
			return FAIL;
		}
		printf("End msg Out\n");
		free(sndMsg);
	}
	/*ChannelCDR_Close (chID); */
	
	return 0;
}


