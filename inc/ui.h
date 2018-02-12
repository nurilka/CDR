#ifndef __UI_H__
#define __UI_H__


/** 
 *  @file ui.h
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */
 
 
#include "uich_protocol.h"


/** 
 * @brief prints user menu                
 * @return void
 */
void UI_PrintUserMenu ();


/** 
 * @brief gets message fro mstdin and transforms it into channel message 
 * @param[in] _option - user option                    
 * @return allocated _useropt  
 */
UserOpt* UI_UserOptionToMsg (int _option);


/** 
 * @brief gets message fro mstdin and transforms it into channel message 
 * @param[in] _option - user option                    
 * @return allocated _useropt  
 */
void UI_DetroyUsrOption (int _option);


/** 
 * @brief open comminucation channels with controller and with reporter               
 * @param[in] _chRepUI - channel ID: from reporter to UI                  
 * @param[in] _chUIctrl -channel ID: from UI to Controller                   
 * @return status
 */
int UI_OpenCommChannels (int* _chRepUI, int* _chUIctrl);

/** 
 * @brief close comminucation channels with controller and with reporter               
 * @param[in] _chRepUI - channel ID: from reporter to UI                  
 * @param[in] _chUIctrl -channel ID: from UI to Controller                   
 * @return status
 */
int UI_CloseCommChannels (int _chUIctrl, int _chRepUI);

/** 
 * @brief prints user menu                
 * @return void
 */
int UI_SendUserOpt (UserOpt* _uOpt, int _channelID);


/** 
 * @brief prints user menu                
 * @return void
 */
int UI_GetReport (void* _report, int _reportSize, int _channelID);

#endif /*__UI_H__*/
