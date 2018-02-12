#ifndef __CHANNEL_CDR_H__
#define __CHANNEL_CDR_H__


/** @file channel_CDR.h
 *  @brief 
 *
 *  @author Nurit (H-45)
 *
 *  @bug No known bugs.
 */

#include <stddef.h>	/*size_t*/

/** 
 * @brief opent IPC channel to communicate with parsing process
 * @param[in] _fileName - 
 * @param[in] _id - 
 * @return int channelID;
 */ 
int ChannelCDR_Open (const char* _fileName, int _id);
/* - ftok, msgget */

/** 
 * @brief Close IPC channel  
 * @param[in] _channelID - id of the open channel
 * @return status XXX;
 */ 
void ChannelCDR_Close (int _channelID);
/* - msgctl: buf = NULL, IPC_RMID */


/** 
 * @brief Send data to IPC channel 
 * @param[in] _channelID - id of the open channel
 * @param[in] _msgPtr - pointer to data
 * @param[in] _msgSize - size of data
 * @return status XXX;
 */ 
int ChannelCDR_Send (int _channelID,  void* _msgPtr, size_t _msgSize );
/* - msgsnd: msgflg - consider flags to protect the Q */

/** 
 * @brief Receive data from IPC channel 
 * @param[in] _channelID - 
 * @param[in] _rcvMsgPtr - pointer to data
 * @param[in] _msgSize - size of data
 * @return status XXX;
 */ 
int ChannelCDR_Receive (int _channelID, void* _rcvMsgPtr, size_t _msgSize)
/* - msgrcv: consider flags inside, msg type */


#endif /* __TCHANNEL_CDR_H__*/

