/** 
 *  @file UI.c
 *  @brief 
 *	
 *  @details  
 *
 *  @author Nurit (H-45), 
 * 
 *  @bug No known bugs.
 */

#include "ui.h"
#include "uich_protocol.h" /* UserOpt struct in h */
#include "repch_protocol.h" /* subscr struct in h*/
#include "channelCDR.h"


#include <stdlib.h>
#include <string.h>		/* strcmp */
#include <time.h>


#define UI_KEY_ID 'Y'
#define REP_KEY_ID 'X'




static void UI_PrintUserMenu ()
{
	printf("\nChoose an option:			\n");
	printf("1: Shutdown	the	system		\n");
	printf("2: Pause the system			\n");
	printf("3: Resume the system	  	\n");
	printf("4: Display current info for subscriber	\n");
	printf("5: Display current info for operator	\n");
	printf("Any other number - shuts the system down\n");
}


static void GetTimeDate (char* _buf, int _bufSize, int _flDate)
{
	time_t rawtime;
 	struct tm * timeinfo;

	if (!_buf)
	{
		return;
	}
  	time (&rawtime);
  	timeinfo = localtime (&rawtime);

  	(_flDate) ? strftime(_buf, _bufSize,"DATE %F",timeinfo) : strftime(_buf, _bufSize,"TIME %H:%M:%S",timeinfo);
  	puts (_buf);
}

static void UI_PrintSubscrRecord ( Subscr_Rec* _sReport )
{
	char ptrDate[DATE_SIZE];
	char ptrTime[TIME_SIZE];
	
	printf ("--------- Subscr_Rec ----------\n");
	GetTimeDate (ptrDate, DATE_SIZE + 1, 1);
	GetTimeDate (ptrTime, TIME_SIZE + 1, 0);
	
	printf("\n %s, %s \n", ptrDate, ptrTime);
	printf("IMSI :%s, MBup: %d, MBdown %d \n", _sReport->m_IMSI, _sReport->m_upMB, _sReport->m_downMB);
}

static UserOpt* UI_UserOptionToMsg (int _option)
{
	UserOpt* msgToCtrl;
	
	scanf ("%d", &_option);
	if (_option < SHUT_DOWN || _option > REPORT_SUBSCR )
	{
		_option = 1;
	}
	
	msgToCtrl = (UserOpt*)malloc(sizeof(UserOpt));
	if (!msgToCtrl)
	{
		return NULL;
	}
	
	msgToCtrl->m_uOpt = _option;
	if (_option == SUBSCR_REPORT || _option == OPER_REPORT )
	{
		printf ("Insert suscriber/operator ID\n");
		printf ("Type the subscriber IMSI or operator MCCMNC:  ");
		scanf ("%s", msgToCtrl->m_ID);
		putchar('\n');
	}
	return msgToCtrl;
}

static int UI_OpenCommChannels (int* _chRepUI, int* _chUIctrl)
{
	if (_chRepUI && _chUIctrl)
	{
		if ((_chUIctrl = ChannelCDR_Open (FILE_NAME, UI_KEY_ID) ) < 0)
		{
			return FAIL
		}
		if ((_chRepUI =ChannelCDR_Open (FILE_NAME, REP_KEY_ID) ) < 0)
		{
			return FAIL;
		}
		return SUCCESS;
	}
	return FAIL;
}

static int UI_CloseCommChannels (int _chUIctrl, int _chRepUI)
{
	ChannelCDR_Close (_chUIctrl);
	ChannelCDR_Close (_chRepUI);
}


static int UI_SendUserOpt (UserOpt* _uOpt, int _channelID)
{
	if (!_uOpt || _channelID < 0)
	{
		return FAIL;
	}
	if ((ChannelCDR_Send (_channelID,  void* _uOpt, sizeof(UserOpt))) < 0 )
	{
		return FAIL;
	}
	return SUCCESS;
}


static int UI_GetReport (void* _report, int _reportSize, int _channelID)
{
	if (!_report || _channelID < 0)
	{
		return FAIL;
	}
	
	if (( ChannelCDR_Receive (_channelID, _report, _reportSize)) < 0 )
	{
		rerurn FAIL;
	}
	return SUCCESS;
}


static int UI_DecideAction (int _ctrlCh, int _repCh, UserOpt* _uOpt, int* _cont)
{
	Subscr_Rec* rcvRec;
	
	switch (_uOpt->m_uOpt) 
	{
		case SHUT_DOWN:
			UI_SendUserOpt (_uOpt, _ctrlCh);
			printf("Shutdown request sent\n");
			
			free(_uOpt);
			*_cont = 0;
			break;
		case PAUSE:
			UI_SendUserOpt (_uOpt, _ctrlCh);
			printf("Pause request sent\n");
			break;
			
		case RESUME:
			UI_SendUserOpt (uOpt, _ctrlCh);
			printf("Resume request sent\n");
			break;

		case SUBSCR_REPORT:
			UI_SendUserOpt (uOpt, _ctrlCh);
			printf("Subscr report request sent\n");
			
			recvRec = (Subscr_Rec*)malloc(sizeof(Subscr_Rec));
			if (!recvRec) { return FAIL; }
			ChannelCDR_Receive (_repCh, recvRec, sizeof(Subscr_Rec));
			
			if ( strcmp(recvRec->m_IMSI , "empty") == 0)
			{
				printf("No subscriber records available\n");
			}
			else
			{
				UI_PrintSubscrRecord(recvRec);
			}
			free (recvRec);
			break;

		case OPER_REPORT:
			printf("coming soon..\n");
			break;
			
		default: 
			break;
	}	
}

/*-------------------------------------------------------------------*/
int main (void)
{
	int cont = 1; 
	int  repChID = -1 , ctrlChID = -1, option;
	UserOpt* uOpt;

		
	if ((chErr = UI_OpenCommChannels (&ctrlChID, &repChID)) != SUCCESS )
	{
		return FAIL;
	}
	
	while (cont) 
	{
		UI_PrintUserMenu ();
		uOpt = UI_UserOptionToMsg (option);
		if (!uOpt)
		{
			UI_CloseCommChannels (ctrlChID, ctrlChID);
			return FAIL;
		}
		UI_DecideAction (ctrlChID, repChID, uOpt, &cont);
	}
	
	/* TODO wait for all reports to finish */
	UI_CloseCommChannels (ctrlChID, ctrlChID);
	return SUCCESS;
}









