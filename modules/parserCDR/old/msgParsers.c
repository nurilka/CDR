
/** 
 *  @file msgParsers.c
 *  @brief 
 *	
 *  @details  
 *
 *  @author 
 * 
 *  @bug No known bugs.
 *
 */

#include "msgParsers.h" 




/** Parse messages from the CDRStorage */

/*	read from Q -> put in buffer 
	malloc event struct 
	parse buffer with strtok 
	update event struct
	insert event into eventQ
	
	*/

/** create buffer to read the message */
CDRMsg* Parser_Setup (int _cdrLen);


/** Get message from the CDRStorage */
int GetFromStorage (int _storageID, CDRMsg* _buffer);

/** Parse messages from the CDRStorage */
Event* ParseMsgToEvent (CDRMsg* _cdr);

/** Insert item to the eventQ */
int InsertEvent (EventQ* _eventQ, Event* _item);


/** Destroy the tmp buffer */
int Parser_Cleanup (CDRMsg* _cdr);

/**
 * @brief ????
 * @param[in] 
 * @param[optional] 
 * @param[optional] 
 * @details 
 */
void Parsers_Pause ();






