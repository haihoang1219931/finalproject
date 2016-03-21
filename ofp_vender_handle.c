#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/dump.h"
#include "openflow/openflow.h"
#include "openflow/ofptype.h"
unsigned char vendor_bandwidth  [24]={0x01, 0x0c, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 
                                      0x00, 0x00, 0x00, 0x00, 
                                      0x00, 
                                      0x01, 
                                      0x00, 0x05, 
                                      0x00, 0x00, 0x00, 0x10, 
                                      0x00, 0x00, 0x00, 0x40};
                                      
unsigned char vendor_port_status[14]={0x01, 0x0c, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 
                                      0x00, 0x00, 0x00, 0x00, 
                                      0x01, 
                                      0x02};
                                      
unsigned char vendor_port_modify[17]={0x01, 0x0c, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 
                                      0x00, 0x00, 0x00, 0x00, 
                                      0x02, 
                                      0x03,
                                      0x00, 0x05,
                                      0x01};
struct ofp_vendor_bandwidth{
    struct ofp_header header;
    ovs_be32 vendor;
    uint8_t type;
    uint8_t port_id;
    uint16_t queue_id;
    uint32_t min_rate;
    uint32_t max_rate;
};
//size = 24

struct ofp_vendor_port_modify{
    struct ofp_header header;
    ovs_be32 vendor;
    uint8_t type;
    uint8_t port_id;
    uint16_t queue_id;
    uint8_t status;
};
//size = 17

void handle_bandwidth(struct ofp_vendor_bandwidth * vendor_bandwitdh){
    printf("vendor_bandwitdh %04x %d bytes\r\n",vendor_bandwitdh->header.length,vendor_bandwitdh->header.length);
    getOFP_TYPE(vendor_bandwitdh->header.type);
    printf("type: %02x\r\n",vendor_bandwitdh->type);
    printf("port_id: %02x\r\n",vendor_bandwitdh->port_id);
    printf("queue_id: %d %04x\r\n",ntohs(vendor_bandwitdh->queue_id),htons(vendor_bandwitdh->queue_id));
    printf("min_rate: %d %08x\r\n",htonl(vendor_bandwitdh->min_rate),htonl(vendor_bandwitdh->min_rate));
    printf("max_rate: %d %08x\r\n",htonl(vendor_bandwitdh->max_rate),htonl(vendor_bandwitdh->max_rate));
     // dump()
}
void handle_port_status(unsigned char *buffer){

}
void handle_port_modify(struct ofp_vendor_port_modify * port_modify){
    printf("vendor_port_modify %04x %d bytes\r\n",port_modify->header.length,port_modify->header.length);
    printf("type: %02x\r\n",port_modify->type);
    printf("port_id: %02x\r\n",port_modify->port_id);
    printf("queue_id: %04x\r\n",htons(port_modify->queue_id));
    printf("status: %02x\r\n",port_modify->status);
}
void handle_vendor(unsigned char *buffer){
    struct ofp_header *oh = (struct ofp_header *)buffer;
    if(oh->type == 0x0c){
        printf("vendor_bandwidth[12] =  %d %d %d\r\n",buffer[11],buffer[12],buffer[13]);
        switch(buffer[12]){
            case 0x00:
                printf("bandwidth\r\n");
                struct ofp_vendor_bandwidth * bandwitdh = (struct ofp_vendor_bandwidth *)buffer; 
                handle_bandwidth(bandwitdh); 
                break;
            case 0x02:
                printf("modify port\r\n"); 
                struct ofp_vendor_port_modify * port_modify = (struct ofp_vendor_port_modify*)buffer; 
                handle_port_modify(port_modify); 
                break;
            }
    }
}
int main(){
    printf("Hello Master\r\n");
    handle_vendor(vendor_port_modify);
    return 0;
}
