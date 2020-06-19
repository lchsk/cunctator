#include "net.h"

#ifdef ENABLE_NET

void net_init() {
    if (SDLNet_Init() == -1) {
        LOGFMT("Error initializing SDL_Net: %s\n", SDLNet_GetError());
        return;
    }

    LOGFMT("%s\n", "SDL_Net init ok");
}

void net_close() {
    SDLNet_Quit();
    LOGFMT("%s\n", "SDL_Net closed");
}

Udp* udp_new(int packet_size, char *host, int port) {
    Udp* udp = calloc(1, sizeof(Udp));

    udp->socket = SDLNet_UDP_Open(0);

    if(!udp->socket) {
        LOGFMT("Error SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        return 0;
    }

    SDLNet_ResolveHost(&udp->ip, host, port);
    udp->packet_size = packet_size;

    udp->recv_packet = SDLNet_AllocPacket(udp->packet_size);

    return udp;
}

void udp_free(Udp *udp) {
    SDLNet_FreePacket(udp->recv_packet);
    udp->recv_packet = NULL;

    SDLNet_UDP_Close(udp->socket);
    LOGFMT("%s\n", "SDL_Net UDP socket closed");
}

void udp_send_packet(Udp *udp, Uint8* data) {
    UDPpacket *packet = SDLNet_AllocPacket(udp->packet_size);
    packet->address = udp->ip;

    packet->data = data;
    packet->len = strlen((char *)packet->data) + 1;

    SDLNet_UDP_Send(udp->socket, -1, packet);

    SDLNet_FreePacket(packet);
}

int udp_recv_packet(Udp *udp) {
    int received = SDLNet_UDP_Recv(udp->socket, udp->recv_packet);

    udp->recv_len = udp->recv_packet->len;
    udp->recv_data = udp->recv_packet->data;

    return received;
}

#endif