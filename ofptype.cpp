#include <stdio.h>
enum ofp_type {
	/* Immutable messages. */
    OFPT_HELLO,               /* Symmetric message */
    OFPT_ERROR,               /* Symmetric message */
    OFPT_ECHO_REQUEST,        /* Symmetric message */
    OFPT_ECHO_REPLY,          /* Symmetric message */
    OFPT_VENDOR,              /* Symmetric message */

    /* Switch configuration messages. */
    OFPT_FEATURES_REQUEST,    /* Controller/switch message */
    OFPT_FEATURES_REPLY,      /* Controller/switch message */
    OFPT_GET_CONFIG_REQUEST,  /* Controller/switch message */
    OFPT_GET_CONFIG_REPLY,    /* Controller/switch message */
    OFPT_SET_CONFIG,          /* Controller/switch message */

    /* Asynchronous messages. */
    OFPT_PACKET_IN,           /* Async message */
    OFPT_FLOW_REMOVED,        /* Async message */
    OFPT_PORT_STATUS,         /* Async message */

    /* Controller command messages. */
    OFPT_PACKET_OUT,          /* Controller/switch message */
    OFPT_FLOW_MOD,            /* Controller/switch message */
    OFPT_PORT_MOD,            /* Controller/switch message */

    /* Statistics messages. */
    OFPT_STATS_REQUEST,       /* Controller/switch message */
    OFPT_STATS_REPLY,         /* Controller/switch message */

    /* Barrier messages. */
    OFPT_BARRIER_REQUEST,     /* Controller/switch message */
    OFPT_BARRIER_REPLY,       /* Controller/switch message */

    /* Queue Configuration messages. */
    OFPT_QUEUE_GET_CONFIG_REQUEST,  /* Controller/switch message */
    OFPT_QUEUE_GET_CONFIG_REPLY     /* Controller/switch message */
};

void getOFP_TYPE(unsigned char data){
	switch(data){
			
		case OFPT_HELLO: printf("[%02x] %s\r\n",OFPT_HELLO,"OFPT_HELLO");break;
		case OFPT_ERROR:printf("[%02x] %s\r\n",OFPT_ERROR,"OFPT_ERROR");break;
		case OFPT_ECHO_REQUEST:printf("[%02x] %s\r\n",OFPT_ECHO_REQUEST,"OFPT_ECHO_REQUEST");break;        /* Symmetric message */
		case OFPT_ECHO_REPLY:printf("[%02x] %s\r\n",OFPT_ECHO_REPLY,"OFPT_ECHO_REPLY");break;          /* Symmetric message */
		case OFPT_VENDOR:printf("[%02x] %s\r\n",OFPT_VENDOR,"OFPT_VENDOR");break;              /* Symmetric message */

		/* Switch configuration messages. */
		case OFPT_FEATURES_REQUEST:printf("[%02x] %s\r\n",OFPT_FEATURES_REQUEST,"OFPT_FEATURES_REQUEST");break;    /* Controller/switch message */
		case OFPT_FEATURES_REPLY:printf("[%02x] %s\r\n",OFPT_FEATURES_REPLY,"OFPT_FEATURES_REPLY");break;      /* Controller/switch message */
		case OFPT_GET_CONFIG_REQUEST:printf("[%02x] %s\r\n",OFPT_GET_CONFIG_REQUEST,"OFPT_GET_CONFIG_REQUEST");break;  /* Controller/switch message */
		case OFPT_GET_CONFIG_REPLY:printf("[%02x] %s\r\n",OFPT_GET_CONFIG_REPLY,"OFPT_GET_CONFIG_REPLY");break;    /* Controller/switch message */
		case OFPT_SET_CONFIG:printf("[%02x] %s\r\n",OFPT_SET_CONFIG,"OFPT_SET_CONFIG");break;          /* Controller/switch message */

		/* Asynchronous messages. */
		case OFPT_PACKET_IN:printf("[%02x] %s\r\n",OFPT_PACKET_IN,"OFPT_PACKET_IN");break;           /* Async message */
		case OFPT_FLOW_REMOVED:printf("[%02x] %s\r\n",OFPT_FLOW_REMOVED,"OFPT_FLOW_REMOVED");break;        /* Async message */
		case OFPT_PORT_STATUS:printf("[%02x] %s\r\n",OFPT_PORT_STATUS,"OFPT_PORT_STATUS");break;         /* Async message */

		/* Controller command messages. */
		case OFPT_PACKET_OUT:printf("[%02x] %s\r\n",OFPT_PACKET_OUT,"OFPT_PACKET_OUT");break;          /* Controller/switch message */
		case OFPT_FLOW_MOD:printf("[%02x] %s\r\n",OFPT_FLOW_MOD,"OFPT_FLOW_MOD");break;            /* Controller/switch message */
		case OFPT_PORT_MOD:printf("[%02x] %s\r\n",OFPT_PORT_MOD,"OFPT_PORT_MOD");break;            /* Controller/switch message */

		/* Statistics messages. */
		case OFPT_STATS_REQUEST:printf("[%02x] %s\r\n",OFPT_STATS_REQUEST,"OFPT_STATS_REQUEST");break;       /* Controller/switch message */
		case OFPT_STATS_REPLY:printf("[%02x] %s\r\n",OFPT_STATS_REPLY,"OFPT_STATS_REPLY");break;         /* Controller/switch message */
		
		/* Barrier messages. */
		case OFPT_BARRIER_REQUEST:printf("[%02x] %s\r\n",OFPT_BARRIER_REQUEST,"OFPT_BARRIER_REQUEST");break;     /* Controller/switch message */
		case OFPT_BARRIER_REPLY:printf("[%02x] %s\r\n",OFPT_BARRIER_REPLY,"OFPT_BARRIER_REPLY");break;       /* Controller/switch message */
		
		/* Queue Configuration messages. */
		case OFPT_QUEUE_GET_CONFIG_REQUEST:printf("[%02x] %s\r\n",OFPT_QUEUE_GET_CONFIG_REQUEST,"OFPT_QUEUE_GET_CONFIG_REQUEST");break;  /* Controller/switch message */
		case OFPT_QUEUE_GET_CONFIG_REPLY:printf("[%02x] %s\r\n",OFPT_QUEUE_GET_CONFIG_REPLY,"OFPT_QUEUE_GET_CONFIG_REPLY");break;     /* Controller/switch message */
		default: printf("[%02x] UNKNOWN MESSAGE\r\n",data);
	}
	return;
}
int main(){
	getOFP_TYPE(0x0a);
	return 0;
}