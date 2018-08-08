#include "avrlibtypes.h"
#include "enc424j600.h"

#define UIP_BUFSIZE     400
extern MAC_ADDR mac_addr;
extern u8 uip_buf[UIP_BUFSIZE + 2];
extern u16 uip_len;

unsigned int network_read(void) {
    uint16_t len;
    len = enc424j600PacketReceive(UIP_BUFSIZE, (u8 *) uip_buf);
    return len;
}

void network_send(void) {
    enc424j600PacketSend(uip_len, (u8 *) uip_buf);
}

void network_init(void) {
    //Initialise the device
    enc424j600Init();
}

void network_get_MAC(u08* macaddr) {
    // read MAC address registers
    // NOTE: MAC address in ENC28J60 is byte-backward
    *macaddr++ = mac_addr.v[0];
    *macaddr++ = mac_addr.v[1];
    *macaddr++ = mac_addr.v[2];
    *macaddr++ = mac_addr.v[3];
    *macaddr++ = mac_addr.v[4];
    *macaddr++ = mac_addr.v[5];
}

void network_set_MAC(u08* macaddr) {
    // write MAC address
    // NOTE: MAC address in ENC28J60 is byte-backward

}

