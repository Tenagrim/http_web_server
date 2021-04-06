#pragma once

//#define DEBUG					1	// Define this for debug logs to stdout
	
//#define USER					"gshona"

#define DEBUG_REQ_PRINT 		1
#define DEBUG_RESP_PRINT 		1

#define UPDATE_DELAY 			1000

#define MAX_PATH_LEN			512
#define TMP_DIR					"trash"

#define DEFAULT_PORT			83
#define DEFAULT_HOST			"localhost"
#define DEFAULT_CONN_QUEUE		10
#define READ_BUFF_SIZE			2048
#define DEFAULT_CLIENT_DELAY	1000 * 1000 * 5
#define CHECK_SOCKET_DELAY		100
#define DEFAULT_SERVER_HEADER	"pst/1.1.0"

#define FM_RW_BUFF				1024
#define FM_DEFAULT_ROOT			"/Users/pcatrina/Desktop/workspace/webserv/webserv/resources/sites/particles"

#define DEFAULT_HTTPV			"HTTP/1.1"

//////// Varies from Delay ///////////////
#define READ_BODY_ONE_TIME		200000
//#define READ_BODY_ONE_TIME		20000
//////////////////////////////////////////

//#define CLIENT_TIMEOUT_MICROS	2000000  // 2 secs
//#define CLIENT_TIMEOUT_MICROS	60000000 // 60 secs
//#define CLIENT_TIMEOUT_MICROS	2000000  // 2 secs
//#define CLIENT_TIMEOUT_MICROS	60000000 // 60 secs
//#define CLIENT_TIMEOUT_MICROS	20000000 // 20 secs
#define CLIENT_TIMEOUT_MICROS	3600000000 // many secs
//#define CLIENT_TIMEOUT_MICROS	2000000		// 2	secs
//#define CLIENT_TIMEOUT_MICROS	20000000	// 20	secs
//#define CLIENT_TIMEOUT_MICROS	60000000	// 60	secs
//#define CLIENT_TIMEOUT_MICROS	3600000000	// many	secs

// Time checking
#define TIME_ZONE 3
#define TIME_BUFF_AUTOINDEX 18

#ifdef DEBUG // DON T TOUCH THIS !!
# define DISPATCHER_SLEEP_DELAY	(2 * 1000 * 1000)
# define DISPATCHER_WAKE_DELAY	(0.5 * 1000 * 1000)
#endif

#ifndef DEBUG
# define DISPATCHER_SLEEP_DELAY	200000
# define DISPATCHER_WAKE_DELAY	1000			// 1 ms
//# define DISPATCHER_WAKE_DELAY	10000		// 10 ms
//# define DISPATCHER_WAKE_DELAY	500000 // 500 ms
//# define DISPATCHER_WAKE_DELAY	200000 // 200 ms
#endif



//int __RESETS = 0; // FIXME REMOVE GLOBAL
