#ifndef __UICH_PROTOCOL_H__
#define __UICH_PROTOCOL_H__


#define FILE_NAME 	"../../inc/ch_protocol.h"
#define PERMISSIONS 0644

#define IMSI_SIZE 16
#define DATE_SIZE 11
#define TIME_SIZE 9

#define SUCCESS 0
#define FAIL 	-1

typedef enum 
{
	SHUT_DOWN = 1,  		     
	PAUSE,  		
	RESUME,
	SUBSCR_REPORT,
	OPER_REPORT
}Opt;

typedef struct UserOpt
{
	Opt m_uOpt;  	
	char m_ID[IMSI_SIZE];   
}UserOpt;



#endif /* __UICH_PROTOCOL_H__*/
