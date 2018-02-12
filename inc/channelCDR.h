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
 * @param[in] _keyID - unique ID key for different channels
 * @return int channelID
 */ 
int ChannelCDR_Open (const char* _fileName, int _keyID);


/** 
 * @brief Close IPC channel  
 * @param[in] _channelID - id of the open channel
 * @return  void
 */ 
void ChannelCDR_Close (int _channelID);


/** 
 * @brief Send data to IPC channel 
 * @param[in] _channelID - id of the open channel
 * @param[in] _msgPtr - pointer to data
 * @param[in] _msgSize - size of data
 * @return status XXX
 */ 
int ChannelCDR_Send (int _channelID,  void* _msgPtr, size_t _msgSize );


/** 
 * @brief Receive data from IPC channel 
 * @param[in] _channelID - 
 * @param[in] _rcvMsgPtr - pointer to data
 * @param[in] _msgSize - size of data
 * @return status XXX
 */ 
int ChannelCDR_Receive (int _channelID,  void* _rcvMsgPtr, size_t _msgSize );



#endif /* __CHANNEL_CDR_H__*/

