#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

void print_family(struct addrinfo *ai) {
    printf(" family: ");
    switch(ai->ai_family) {
    case AF_INET:
        printf("inet");
        break;
    case AF_INET6:
        printf("inet6");
        break;
    case AF_UNIX:
        printf("unix");
        break;
    case AF_UNSPEC:
        printf("unspecified");
        break;
    default:
        printf("unknown");
    }
}

void print_type(struct addrinfo* ai) {
    printf(" type: ");
    switch(ai->ai_socktype) {
    case SOCK_STREAM:
        printf("stream");
        break;
    case SOCK_DGRAM:
        printf("datagram");
        break;
    case SOCK_SEQPACKET:
        printf("seqpacket");
        break;
    case SOCK_RAW:
        printf("raw");
        break;
    default:
        printf("unknown");
    }
}

void print_protocol(struct addrinfo* ai) {
    printf(" protocol ");
    switch (ai->ai_protocol) {
    case IPPROTO_TCP:
        printf("tcp");
        break;
    case IPPROTO_UDP:
        printf("udp");
        break;
    case IPPROTO_RAW:
        printf("raw");
        break;
    default:
        printf("unkonwn");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: %s hostname service\n", argv[0]);
        return 0;
    }

    struct addrinfo* ai_list;
    getaddrinfo(argv[1], argv[2], NULL, &ai_list);
    for(struct addrinfo* p = ai_list; p != NULL; p = p->ai_next) {
        printf("host: %s ", p->ai_canonname);
        print_family(p);
        print_type(p);
        print_protocol(p);
        printf("\n");
    }

    freeaddrinfo(ai_list);
    return 0;
}
