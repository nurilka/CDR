#ifndef __REPCH_PROTOCOL_H__
#define __REPCH_PROTOCOL_H__


#define FILE_NAME 	"../../inc/repch_protocol.h"
#define PERMISSIONS 0644

#define IMSI_SIZE 16
#define MCCMNC_SIZE 6
#define BRAND_NAME_MAX 64
#define DATE_SIZE 11
#define TIME_SIZE 9

#define SUCCESS 0
#define FAIL 	-1


typedef struct Subscr_Rec
{
	int m_internMOC;		/* outgoing voice within oper */
	int m_internMTC;		/* incoming voice within oper */
	int m_outsideMOC;		/* outgoing voice outside oper */
	int m_outsideMTC;		/* incoming voice outside oper */
	int m_internSMS_MO;		/* outgoing SMS within oper */
	int m_internSMS_MT;		/* incoming SMS within oper */
	int m_outsideSMS_MO;	/* outgoing SMS outside oper */
	int m_outsideSMS_MT;	/* incoming SMS outside oper */
	int  m_upMB;
	int  m_downMB;
	char m_IMSI[IMSI_SIZE];	/* unique SIM number */
	char m_date[DATE_SIZE];
	char m_time[TIME_SIZE];
}Subscr_Rec;

typedef struct Oper_Rec
{
	int  m_outTotalMOC;		/* total outgoing voice outside oper */
	int  m_outTotalMTC;		/* total incoming voice outside oper */
	int  m_outTotalSMS_MO;	/* outgoing SMS outside oper */
	int  m_outTotalSMS_MT;	/* incoming SMS outside oper */
	char m_MCCMNC[MCCMNC_SIZE];
	char m_brandName[BRAND_NAME_MAX];
	char m_date[DATE_SIZE];
	char m_time[TIME_SIZE];
}Oper_Rec;




#endif /* __REPCH_PROTOCOL_H__*/
