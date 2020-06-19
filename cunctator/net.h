#ifndef ENGINE212_NET_H
#define ENGINE212_NET_H

#include "config.h"

#ifdef ENABLE_NET

#include <SDL2/SDL_net.h>

typedef struct {
    UDPsocket socket;
    IPaddress ip;
    int packet_size;

    // Packet data that was recently received
    UDPpacket *recv_packet;

    Uint8 *recv_data;
    int recv_len;
} Udp;

void net_init();
void net_close();

Udp* udp_new(int packet_size, char *host, int port);
void udp_free(Udp* udp);

void udp_send_packet(Udp *udp, Uint8* data);

// Return 1 if packet was received
int udp_recv_packet(Udp *udp);

#endif

#endif //ENGINE212_NET_H
