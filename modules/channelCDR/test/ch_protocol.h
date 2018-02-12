#ifndef __CH_PROTOCOL_H__
#define __CH_PROTOCOL_H__


#define FILE_NAME 	"../../inc/ch_protocol.h"
#define KEY_ID 		'X'
#define PERMISSIONS 0644


#define SUCCESS 1
#define FAIL 	-1

typedef enum
{
	MOC,  		/* outgoing voice call */      
	MTC,  		/* incoming voice call */         
	SMS_MO,  	/* outgoing message */    
	SMS_MT,  	/* incoming message */    
	GPRS  		/* internet */
}Call_Type;

typedef struct CDR_Rec
{
	char m_IMSI[16];
	char m_MSISDN[16];
	char m_IMEI[16];		/* Subscriber	IMEI	*/
	char m_MCCMNC[6];
	char m_brandName[64];
	Call_Type m_cType;
	char m_date[11];
	char m_time[9];
	int  m_duration;
	int  m_upMB;
	int  m_downMB;

}CDR_Rec;


#endif /* __CH_PROTOCOL_H__*/
