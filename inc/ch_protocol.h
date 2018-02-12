#ifndef __CH_PROTOCOL_H__
#define __CH_PROTOCOL_H__


#define FILE_NAME 	"../../inc/ch_protocol.h"
#define PERMISSIONS 0644

#define IMSI_SIZE 16
#define MSISDN_SIZE 16
#define IMEI_SIZE 16
#define MCCMNC_SIZE 6
#define BRAND_NAME_MAX 64
#define DATE_SIZE 11
#define TIME_SIZE 9

#define SUCCESS 0
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
	char m_IMSI[IMSI_SIZE];
	char m_MSISDN[MSISDN_SIZE];
	char m_IMEI[IMEI_SIZE];			/* Subscriber	IMEI	*/
	char m_MCCMNC[MCCMNC_SIZE];
	char m_brandName[BRAND_NAME_MAX];
	Call_Type m_cType;
	char m_date[DATE_SIZE];
	char m_time[TIME_SIZE];
	int  m_duration;
	int  m_upMB;
	int  m_downMB;
	
	int  m_EOF;		/* set to 1 if EOF, 0 if not */

}CDR_Rec;


#endif /* __CH_PROTOCOL_H__*/
