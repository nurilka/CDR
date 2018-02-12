#ifndef __MSGPARSER_H__
#define __MSGPARSER_H__


#include "manager.h"

#include <stddef.h>  /* size_t */

/** 
 *  @file msgParsers.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author 
 * 
 *  @bug No known bugs.
 *
 */


typedef struct CDRMsg CDRMsg;
typedef struct Event Event;

/** 
 * @brief 		create buffer to read the message
 * @param[in] - cdr message length
 * @return status
 * @retval pointer to buffer
 */
CDRMsg* Parser_Setup (int _cdrLen);


/** 
 * @brief 		Get message from the CDRStorage
 * @param[in] - ID of the system V message Q to read input
 * @return status
 * @retval XXX
 */
int GetFromStorage (int _storageID, CDRMsg* _buffer);

/** 
 * @brief 		Parse messages from the CDRStorage
 * @param[in] - nParsers, num of parsesrs to run simultaneously on the input
 * @param[in] - pointer to EventQ 
 * @param[in] - ID of the system V message Q to read input
 * @return status
 * @retval XXX
 */
Event* ParseMsgToEvent (CDRMsg* _cdr);

/** 
 * @brief 		Insert item to the eventQ
 * @param[in] - pointer to EventQ 
 * @param[in] - pointer to event item
 * @return status
 * @retval XXX
 */
int InsertEvent (EventQ* _eventQ, Event* _item);


/** 
 * @brief 	Destroy the tmp buffer
 * @param[in] - pointer to tmp buffer
 * @return status
 * @retval XXX
 */
int Parser_Cleanup (CDRMsg* _cdr);

/**
 * @brief ????
 * @param[in] 
 * @param[optional] 
 * @param[optional] 
 * @details 
 */
void Parsers_Pause ();


#endif /* __MSGPARSER_H__ */





