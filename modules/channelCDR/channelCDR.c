
/** @file channel_CDR.c
 *  @brief 
 *
 *  @author Nurit (H-45)
 *
 *  @bug No known bugs.
 */

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500

#include "channelCDR.h"
#include "ch_protocol.h"

#include <stdlib.h> 	/* malloc */
#include <stdio.h>		/* printf */
#include <string.h> 	/* memcpy */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SR_CHAN 	7 



typedef struct  {
    long m_type;       /* message type, must be > 0 */
    char m_text[1];    /* message data */
}Rqst;

/*----------------------------------------------------------*/
static Rqst* InternMsg_Create (void* _msgPtr, int _msgSize )
{
	Rqst* 	newRqst;
     	
   	if( (newRqst = (Rqst*)malloc (sizeof(Rqst) + _msgSize )) == NULL )
   	{
		return NULL;
   	}
    newRqst->m_type = SR_CHAN; 
    
    if (_msgPtr )
    {  
   		memcpy (newRqst->m_text , _msgPtr, _msgSize );
   	} 

	return newRqst;
}

static void InternMsg_Destroy (Rqst* _rqst)
{
	if (_rqst)
	{
		free (_rqst); 
	}
}

/*----------------------- API Functions --------------------*/
/**  opent IPC channel to communicate with parsing process */ 
int ChannelCDR_Open (const char* _fileName, int _keyID)
{
	/* - ftok, msgget */
	key_t 	key;
	int 	channelID = -1, permission = PERMISSIONS | IPC_CREAT;
	
	if ((key = ftok(_fileName, _keyID)) == -1) 
	{  
	    return key;
	}
	channelID = msgget (key, permission);
    printf("channelID: %d\n",channelID);
    return channelID;
}

/**  close IPC channel   */ 
void ChannelCDR_Close (int _channelID)
{
	msgctl (_channelID, IPC_RMID, NULL);
}

/**  Send data to IPC channel  */ 
int ChannelCDR_Send (int _channelID, void* _msgPtr, size_t _msgSize )
{
	int res = 0;
	Rqst* internalMsg;
	
	if ( !_msgPtr || _channelID < 0)
	{
		return FAIL;
	}
	
	internalMsg = InternMsg_Create ( _msgPtr, _msgSize);
	res = msgsnd (_channelID, internalMsg, _msgSize, 0);

	InternMsg_Destroy (internalMsg);
	
	return res;
}


/**  Receive data from IPC channel  */ 
int ChannelCDR_Receive (int _channelID, void* _rcvMsgPtr, size_t _msgSize)
{
	int res = 0;
	Rqst* internalMsg;
	
	if ( !_rcvMsgPtr || _channelID < 0)
	{
		return FAIL;
	}
	
	internalMsg = InternMsg_Create ( NULL, _msgSize);
	res = msgrcv (_channelID, internalMsg, _msgSize, SR_CHAN, 0);

	memcpy (_rcvMsgPtr , internalMsg->m_text, _msgSize );
	InternMsg_Destroy (internalMsg);

	return res;
}

#endif  /*_XOPEN_SOURCE_ */

