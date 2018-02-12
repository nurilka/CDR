
#include "ch_protocol.h"
#include "channelCDR.h"



#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



static CDR_Rec* CDR_Rec_Create (char* _input, size_t _inpSize)
{
	CDR_Rec* msgPtr;
	
	
	msgPtr = (CDR_Rec*)malloc(sizeof(CDR_Rec));
	if ( !msgPtr )
	{
		return NULL;
	}
	strcpy(msgPtr->m_IMSI, "0523334479");
	strcpy(msgPtr->m_IMEI, "123344777777889");
	strcpy(msgPtr->m_date, "2017/13/07");
	strcpy(msgPtr->m_time, "09:18:32");
	msgPtr->m_cType = MTC;
	strcpy (msgPtr->m_MCCMNC, "44576");
	strcpy (msgPtr->m_brandName, "Golan Telecom");
	strcpy (msgPtr->m_MSISDN, "123123123123");
	msgPtr->m_duration = rand()%150 + 600;
	msgPtr->m_upMB = 0;
	msgPtr->m_downMB = rand()%100;
	
	return msgPtr;
}
/*------------------------ MAIN ------------------------------*/
int main (void)
{
	CDR_Rec  rcvMsg;
	CDR_Rec* sndMsg;
	int 	chID, res = 0;
	
	sndMsg = CDR_Rec_Create (NULL, 13);
	
	chID = ChannelCDR_Open (FILE_NAME, KEY_ID);
	if (chID < 0)
	{
		perror("channel open");
		free(sndMsg);
		return FAIL;
	}
	
	res = ChannelCDR_Send (chID,  (void*) sndMsg, sizeof(CDR_Rec) );
	if (res != 0)
	{
		perror("channel send");
		free(sndMsg);
		ChannelCDR_Close (chID);
		return FAIL;
	}
	res = ChannelCDR_Receive (chID,  (void*)&rcvMsg, sizeof(CDR_Rec) );
	if (res < 0)
	{
		perror("channel receive");
		free(sndMsg);
		ChannelCDR_Close (chID);
		return FAIL;
	}
	printf("brand: %s\n", rcvMsg.m_brandName);
	printf ("IMEI: %s\n", rcvMsg.m_IMEI);
		
	free(sndMsg);
	ChannelCDR_Close (chID);
	
	return 0;
}


