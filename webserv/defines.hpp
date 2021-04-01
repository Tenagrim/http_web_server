

//#define DEBUG 1					// Define this for debug logs to stdout
#define UPDATE_DELAY 1000

#define DEFAULT_PORT			83
#define DEFAULT_HOST			"localhost"
#define DEFAULT_CONN_QUEUE		10
#define READ_BUFF_SIZE			2048
#define DEFAULT_CLIENT_DELAY	1000 * 1000 * 5
#define CHECK_SOCKET_DELAY		100


#define READ_BODY_ONE_TIME 200000

#ifdef DEBUG // DON T TOUCH THIS !!
# define	DISPATCHER_TICK_MICROS (0.5 * 1000 * 1000)
#endif

#ifndef DEBUG
	# define	DISPATCHER_TICK_MICROS (1000)
#endif